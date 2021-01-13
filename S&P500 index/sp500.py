import numpy as np
import pandas as pd
import requests
import xlsxwriter
import math
# usinf sandbox IEX API token
IEX_CLOUD_API_TOKEN = 'Tpk_059b97af715d417d9f49f50b51b1c448'
stocks = pd.read_csv('sp_500_stocks.csv')

cols = ['Ticker', 'Stock Price',
        'Market Capitalization', 'Number of Shares to Buy']


def split_list(lst, n):
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


ticker_groups = list(split_list(stocks['Ticker'], 100))
final_df = pd.DataFrame(columns=cols)
ticker_str = []
for i in range(0, len(ticker_groups)):
    ticker_str.append(','.join(ticker_groups[i]))
    # print(ticker_str)
for ticker in ticker_str:
    batch_api_call_url = f'https://sandbox.iexapis.com/stable/stock/market/batch?symbols={ticker}&types=quote&token={IEX_CLOUD_API_TOKEN}'
    # print(batch_api_call_url)
    data = requests.get(batch_api_call_url).json()
    # print(data.status_code)
    for t in ticker.split(','):
        final_df = final_df.append(
            pd.Series(
                [
                    t,
                    data[t]['quote']['latestPrice'],
                    data[t]['quote']['marketCap'],
                    'N/A'

                ],
                index=cols
            ),
            ignore_index=True
        )
portfolio_size = input('Enter Value of Portfolio: ')
try:
    val = float(portfolio_size)
except ValueError:
    print('That is not a number \n Please try again')
    portfolio_size = input('Enter Value of Portfolio: ')
    val = float(portfolio_size)
pos_size = val / len(final_df.index)
for i in range(0, len(final_df.index)):
    price = final_df.loc[i, 'Stock Price']
    final_df.loc[i, 'Number of Shares to Buy'] = math.floor(pos_size / price)

# print(final_df)
# save it as an xl file
writer = pd.ExcelWriter('recommended trades.xlsx', engine='xlsxwriter')
final_df.to_excel(writer, 'Recommended Trades', index=False)
bckgrnd_colour = '#0a0a23'
font_colour = '#fffff'
string_format = writer.book.add_format(
    {
        'font_color': font_colour,
        'bg_color': bckgrnd_colour,
        'border': 1
    })

dollar_format = writer.book.add_format(
    {
        'num_format': '$0.00',
        'font_color': font_colour,
        'bg_color': bckgrnd_colour,
        'border': 1
    })

integer_format = writer.book.add_format(
    {
        'num_format': '$0',
        'font_color': font_colour,
        'bg_color': bckgrnd_colour,
        'border': 1
    })
writer.sheets['Recommended Trades'].write('A1', 'Ticker', string_format)
writer.sheets['Recommended Trades'].write('B1', 'Stock Price', string_format)
writer.sheets['Recommended Trades'].write(
    'C1', 'Market Capitalization', string_format)
writer.sheets['Recommended Trades'].write(
    'D1', 'Number of Shares to Buy', string_format)


col_format = {
    'A': ['Ticker', string_format],
    'B': ['Stock Price', dollar_format],
    'C': ['Market Capitalization', dollar_format],
    'D': ['Number of Shares to Buy', integer_format],
}

for col in col_format.keys():
    writer.sheets['Recommended Trades'].set_column(
        f'{col}:{col}', 18, col_format[col][1])
    writer.sheets['Recommended Trades'].write(
        f'{col}1', col_format[col][0], col_format[col][1])

writer.save()
