TwitterStockAnalysis
====================

Using Tweets to predict the Best and Worst Stock Investment Ideas

Every single day, stock investors – expert and novice – send out millions of tweets on various stocks. In the US, a certain protocol is followed to name the stock(s) within the tweets. For example, “$GOOG expected to top analyst forecast #buy”. The $ sign followed by the unique symbol used for the stock on stock exchanges helps to related tweets to stocks. Tweets can be positive, negative or neutral about a stock. There are multiple challenges involved in analyzing the sentiment for a stock within tweets:
Enormous number of tweets, running into millions a day
A tweet may mention more than one stock and the associated sentiment may be cryptic
A tweet may use double negatives
However, a good sentiment analysis for all available tweets aggregated for individual stocks can reveal future trends in stock prices before most of the players in the markets.
This project attempts to tackle this challenge on a small scale basis by using the following approach:
 
Use a small sample of tweets covering around 140 stocks
Use two collections of words to describe sentiment associated with a stock and a tweet             
1) Positive words indicating positive sentiment
2) Negative words indicating negative sentiment
Analyze each tweet for two sets of data:Sentiment of the tweetStocks associated with the tweet
Arrange the tweets in a hash-map of a double linked list, with the stock symbols (e.g. $GOOG, $AAL, $C, etc.) serving as indices. All tweets (data elements) containing a particular stock will be tagged to the stock (index of a data slot)
Aggregate the positive, negative and neutral tweets for a stock into a single score by assigning a value of +1 to a positive tweet, 0 to a neutral tweet and -1 to a negative tweet.
Stocks with the highest scores present the best stock investment ideas (BUY Recommendation)
Stocks with the lowest scores present the worst stock investment ideas (SELL Recommendation)
 
Source Code Description:
I have used two files to run this project, which can be found at the

1)TwitterStockAnalysis.cpp
2)Tweets.txt
 
The TwitterStockAnalysis.cpp file contains the following classes:
 
1)Data
Stores 3 values – key (stock symbol), value (tweet), sentiment (1, 0 or -1)
 
2)Element
Node that contains Data object, and pointers to linked next and previous such nodes
 
3)Data Slot
Stores 5 values – index (stock symbol), size (# of tweets for that stock), number of positive, neutral and negative tweets for that stock
 
4)Slot
Stores a Data Slot object , and pointers to linked next and previous slots
Functions:
i.insert (to insert an element) into the linked list of the stock; it also updates the size, and # of positive, negative and neutral          tweets based on the element
ii.delete (to delete an element) from the linked list of the stock; it also updates the size, and # of positive, negative and                  neutral tweets based on the element
 
5)HashMap
This class represents the entire map of stocks and their tweets
An object of this class has a set of linked objects of the class Slot, which together comprise of the entire map of tweets across various stocks
Functions:
i.Insert a slot
ii.Insert an element in a slot
iii.Delete a slot
iv.Delete an element from a slot
v.Find a slot: allows the program to locate a slot associated with a stock
vi.Display: displays the entire map of tweets by stock, along with # of tweets, # of positive, neutral and negative tweets
vii.Display Table: displays a table with stocks in the first column, and the associated positive, neutral and negative tweets in        the subsequent columns
 
6)SentimentAnalysis
This class is used to conduct sentiment analysis on a tweet.
It has two predefined strings: positive and negative, which contain comma separated strings indicating positive and negative sentiment.
Functions:
i.Provide Sentiment: it matches the tweets with the positive and negative strings described above and returns an integer:1 if a          positive word is found in the tweet0 is neither a positive nor a negative word is found in the tweet-1 if a negative word is found        in the tweet.
ii.Add Negative Word: allows to add negative words to the existing negative string.
iii.Add Positive Word: allows to add negative words to the existing positive string.
 
The main() function of this file reads the file “Tweets.txt” which contains a small sample of tweets covering 140 stocks.
 
For every line, it determines the stock symbols present in the tweet
For every stock, it creates a Data object containing the stock and the tweet, and then creates an Element object
It finds the Slot for the stock and then inserts the Element in the slot
If a Slot doesn’t already exist, it creates a new slot and inserts it in the hashmap
 
The code was successfully compiles and run on Amazon Web Services (AWS) with the following configuration:
EC2 Virtual ServerInstance
ID: i-de2887d7Instance
Type: t1.micro
 

Conclusions:
 
This project was able to produce a result demonstrating how tweets can be used to guide stock investment decisions. 
The program can be further developed into a sophisticated application with the following additions:
A direct interface with Twitter that can pull tweets in real time
A more sophisticated sentiment analysis algorithm that deals with various aspects of semantics
An ability to let a user enter a stock symbol and then provide all the available intelligence from the tweets to the user
