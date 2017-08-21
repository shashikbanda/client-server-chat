import socket               # Import socket module
import sys

BUFFER_SIZE = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)         # Create a socket object
host = "127.0.0.1"			 # Get local machine name
#host = socket.gethostname()
port = int(sys.argv[1])      # Reserve a port for your service.

s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.

msg = ""
data = ""
username = "Jarvis"

while True:
	c, addr = s.accept()     # Establish connection with client.
	#print 'Got connection from', addr
	data = c.recv(BUFFER_SIZE)
	print data
	while data != "\quit":
		data = c.recv(BUFFER_SIZE)
		print data
		if data != "\quit":
			msg = raw_input(username + '> ')
			while (len(msg) > 500):
				print "Message too long. Keep message under 500 characters."
				msg = raw_input(username + '> ')
			if msg != "\quit":
				c.send( username + "> " + msg)
			else:
				c.send("\quit")
		else:
			c.close()                			# Close client connection
			print "Client Connection Closed."
	
	