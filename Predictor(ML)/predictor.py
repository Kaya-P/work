import math
import pandas_datareader as web
import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense, LSTM
import matplotlib.pyplot as plt
pd.options.mode.chained_assignment = None
plt.style.use('fivethirtyeight')

df = web.DataReader('AAPL', data_source='yahoo',
                    start='2012-01-01', end='2019-12-17')
# print(df)
# size of table
# print(df.shape)
# graph of closing price history
plt.figure(figsize=(16, 8))
plt.title('Close Price History')
plt.plot(df['Close'])
plt.xlabel('Date', fontsize=18)
plt.ylabel('Close Price USD $', fontsize=18)
# plt.show()
# Cretae new Dataframe w/ only close col
data = df.filter(['Close'])
# convert df to numpy array
dataset = data.values
# get rows to train models
training_data_len = math.ceil(len(dataset) * 0.8)
# print(training_data_len)
# scale the data
scaler = MinMaxScaler(feature_range=(0, 1))
scaled_data = scaler.fit_transform(dataset)
# print(scaled_data)
# create training data set
train_data = scaled_data[0:training_data_len, :]
# split into x and y train data sets
x_train = []
y_train = []

for i in range(60, len(train_data)):
    x_train.append(train_data[i - 60:i, 0])
    y_train.append(train_data[i, 0])
    # if (i <= 61):
    #     print(x_train)
    #     print(y_train)
    #     print('\n')
# convert training data to numpy arrays
x_train, y_train = np.array(x_train), np.array(y_train)
# reshape data
x_train = np.reshape(x_train, (x_train.shape[0], x_train.shape[1], 1))

model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(x_train.shape[1], 1)))
model.add(LSTM(50, return_sequences=False))
model.add(Dense(25))
model.add(Dense(1))
# compile
model.compile(optimizer='adam', loss='mean_squared_error')
# train
model.fit(x_train, y_train, batch_size=1, epochs=1)

test_data = scaled_data[training_data_len - 60:, :]
x_test = []
y_test = dataset[training_data_len:, :]
for i in range(60, len(test_data)):
    x_test.append(test_data[i - 60:i, 0])
# convert data to numpy array
x_test = np.array(x_test)
x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))
# get models predictions
predictions = model.predict(x_test)
predictions = scaler.inverse_transform(predictions)
# get RMSE
rmse = np.sqrt(np.mean(predictions - y_test)**2)
print(rmse)
train = data[:training_data_len]
valid = data[training_data_len:]
valid['Predictions'] = predictions
plt.figure(figsize=(16, 8))
plt.title('Model')
plt.xlabel('Date', fontsize=18)
plt.ylabel('Close Price USD $', fontsize=18)
plt.plot(train["Close"])
plt.plot(valid[['Close', 'Predictions']])
plt.legend(['Train', 'Val', 'Predictions'], loc='lower right')
plt.show()
# show actual and predicted prices
print(valid)
# get qutoe
appl_quote = web.DataReader('AAPL', data_source='yahoo',
                            start='2012-01-01', end='2019-12-17')
new_df = appl_quote.filter(['Close'])
last_60days = new_df[-60:].values
last_60days_scaled = scaler.transform(last_60days)
X_test = []
X_test.append(last_60days_scaled)
X_test = np.array(X_test)
X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], 1))
pred_pr = model.predict(X_test)
pred_pr = scaler.inverse_transform(pred_pr)
print(pred_pr)
appl_quote2 = web.DataReader('AAPL', data_source='yahoo',
                             start='2019-12-18', end='2019-12-18')
print(appl_quote2['Close'])
