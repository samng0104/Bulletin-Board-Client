BulletinBoardClient

BulletinBoardClient is a command-line application written in C++ which stores and retrieve text and connects to a server.
This BulletinBoardClient has 3 commands, POST, READ and QUIT.

===============================

Requirements:
This BulletinBoardClient is developed under Windows 10 64-bit and designed for Windows 10 64-bit.

===============================

Usage:

To Build Connection:

BulletinBoardClient will first prompt user for IP address with message "Input the IP address:".
Once the IP address is correct(eg. 127.0.0.1), BulletinBoardClient will return the IP address and Port Number(16000) as well as the connection status which will be success or fail if the IP address is incorrect.

Now, the connection between BulletinBoardClient and BulletinBoardServer is built, that is, BulletinBoardClient and BulletinBoardServer can communicate with each other.

-------------------------------

To send text to server:

Type "POST".

Then type the text, BulletinBoardClient will repeat your text with prefix "client: ".

eg.
POST
client: POST
test1
client: test1
test2
client: test2
test3
client: test3

Note that maximum number of messages is 100.
All messages are accumulated in BulletinBoardServer.
Type "." to stop sending message to server.

eg.
.
client: .
server: OK

Then POST function is finished.

-------------------------------

To require server to repeat the accumulated  messages:

Type "READ".

BulletinBoardServer will send back all messages during the POST function, followed by a "." at the end representing this is the end of all messages.

eg.
READ
client: READ
server: test1
server: test2
server: test3
server: .

Note that all messages sent to server will also be repeated in BulletinBoardServer, namely server side.

-------------------------------

To disconnect from server:
Type "QUIT"

A message "OK" from server will be received representing that this connection is closed.

eg.
QUIT
client: QUIT
server: OK

-------------------------------

Handling invalid commands:

Any message typed and not during POST command will be considered as invalid command, except READ, POST and QUIT.
eg.
CS3201
client: CS3201
server: ERROR - Command not understood

===============================
