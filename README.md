# work
Here a few of the projects I have developed. 
## 1. Predictor(ML)
  This folder includes the documentation for the virtual enviroment I set up on my computer to develop it. And the main .py file that you can 
 run. My program used the keras library and more specifically a LSTM model to predict stock prices based on 60 days of historical data for stocks. 
 There are graphical representations of the 
 data and model outputs.

## 2.  S&P500 index
This project contains a csv of the S&P company codes (sp_500_stocks.csv), 2 example outputs of the program (momentum_strategy.xlsx and 
recommended trades.xlsx) and the main program sp500.py. To generate "Recommended trades.xlsx" takes a user input size fo portfolio and using 
an API sandbox and bacth calls, gets the closing price and market cap of each stock. It then calculates the amount of money the user should use 
to buy shares in the specfic company. 
Working On: developing the momentaum strategy for buying stock but I have included a previous output of the strategy to buy stocks. 

## 3.Twitter Analytics 
This project folder contains output.txt, tabulate.py, twiiterScrape.py, twitter_analytics.csv. The main program is twiiterScrape.py where using
a twitter users login details we extract their tweets, and tweet engagments. Yo do this we use Selenium to webscrape the data off their twitter
pages. The output is saves output.txt. Tabulate.py then take output.txt as an input and formalises the information into a table. 
Working On: inlcuding the tweets along with it's engagement and providing sentiment analysis and graphical representations of the information, i.e 
popularitu of tweets based on time it is posted, topic sentiment of tweets compared to the tweets engagement.

## 4. j_compiler
This is a hoemwork project I devloped when taking an Operating Systems class. The homewokr brief is included but to summarize, we had to create a complier for a fictional langauge J. To run my program you will need to run the makefile and to see the program work you can run 
> ./jc {test}.j

This program was developed in C. and compiles the lanaguge J that inclused loops, if statments, arithematic operations, comparisions (i.e greater than, equals to etc.), logical operations (AND, OR, NOT), stack operations (drop, rotate, duplicate etc.), functions(with return statements)  
 
 ## 5. Final Project - Beating the Odds
 note: when viewing the file sometimes it does not load, so I have provided this link to the original Google Colab
> https://colab.research.google.com/drive/17E4jAApImF-Pb034B_qWBOtgo_Ook71c?usp=sharing

This is a google colab I developed as my final project for my Big Data Analytics class. I found a dataset of soccer match information and repsective betting odds and developed my own ML models to predict thee outcomes of the matches using properties of the matches and the players of the matches. First I explored the dataset showing graphical illustrations of certain trends among players, matches and betting companies. I used heatmaps, pairplots, pie graphs and more to show interesting trends. Next I developed a series of ML models to see how well I coudl predict the winner of the macthes. I used a SVC, Linear SVC and SGDClassifer models along with a RandomForestClassifier and KNeighbourClassifier to try find the best model. I used PCA to reduce the dimensioanlity of my features while capturing variance and Grid Search to hypetune my parameters. I found the best model was the SVC() model. 

