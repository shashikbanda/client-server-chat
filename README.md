### Program Description

- This repo contains code for a server (which is always on) and a client (which connects to the server). 
- The server code was written in C. The client code was written in Python. 
- The server-client communication is over a TCP connection, implemented using the Sockets API. 

### Instructions for running client/server code:

There are two files, clientserve.py and clientchat.c.

Both client and server must be running on same server (or localhost).
On Terminal A:
- start the server first: python clientserve.py <PORT NUM>


On Terminal B:
- compile the C, client code: gcc chatclient.c -o chatclient
- run the chat client: ./chatclient 172.0.0.1 <PORT NUM>


A message will appear on both the client and server terminals saying “Successfully connected on port <PORT NUM>”


The chatclient will have command of input. He/She can send a message of up to 500 characters. Once they hit enter, the message is sent to server and server will have command.


The server will receive the message and will be allowed to type something in as well. 


This process repeats until either host A or B types \quit.


Once \quit is hit, the client program is terminated but the server code lives on, waiting for the next client connection.
