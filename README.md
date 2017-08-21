Instructions for running client/server code:


There are two files, clientserve.py and clientchat.c.


Testing on flip1.engr.oregonstate.edu… make sure both terminal A and B are running on flip1.
On Terminal A:
- start the server first: python clientserve.py 43341


On Terminal B:
- compile the C, client code: gcc chatclient.c -o chatclient
- run the chat client: ./chatclient 172.0.0.1 43341


A message will appear on both the client and server terminals saying “Successfully connected on port 43341”


The chatclient will have command of input. He/She can send a message of up to 500 characters. Once they hit enter, the message is sent to server and server will have command.


The server will receive the message and will be allowed to type something in as well. 


This process repeats until either host A or B types \quit.


Once \quit is hit, the client program is terminated but the server code lives on, waiting for the next client connection.


References:
http://www.thegeekstuff.com/2011/12/c-socket-programming/?utm_source=feedburner
https://www.tutorialspoint.com/python/python_networking.htm