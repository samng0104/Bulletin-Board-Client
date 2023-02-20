#include<iostream>
#include<string>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

string ip;						//ip of the server
int port = 16000;				//port number on the server
SOCKET clientSocket;			//Socket variable of client
char buffer[100];				//array fo the user inputs (in order to all inputs in one)
string input;					//variable for user input
int	textReceived;				//variable for the message received form server

void serverLinking() {				//to set up the linking with the server
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	int ws_Result = WSAStartup(MAKEWORD(2, 2), &data);
	if (ws_Result != 0) {
		exit(0);
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		closesocket(clientSocket);
		WSACleanup();
		exit(0);
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &address.sin_addr);

	int connect_status = connect(clientSocket, (sockaddr*)&address, sizeof(address));
	if (connect_status == SOCKET_ERROR) {
		cout << "Connect status: fail" << endl;
		closesocket(clientSocket);
		WSACleanup();
		system("pause");
		exit(0);
	}

	cout << "Connect status: success" << endl;
}

void convetWords() {				//to handle the input into buffer variable and + "\n" after the message
	strcat_s(buffer, input.c_str());
	strcat_s(buffer, "\n");
}

void POST() {						//function for post command
	do {
		cout << "client: ";
		getline(cin, input);
		convetWords();
	} while (strcmp(input.c_str(), ".") != 0);
	send(clientSocket, buffer, 100, 0);
	textReceived = recv(clientSocket, buffer, 100, 0);
	cout << "server: " << string(buffer, 0, textReceived) << endl;
}

void READ() {						//function for read command
	send(clientSocket, buffer, 100, 0);
	do {
		textReceived = recv(clientSocket, buffer, 100, 0);
		cout << "server: " << string(buffer, 0, textReceived) << endl;
	} while (string(buffer, 0, textReceived) != ".");
}

void QUIT() {						//function for quit command
	send(clientSocket, buffer, 100, 0);
	textReceived = recv(clientSocket, buffer, 100, 0);
	cout << "server: " << string(buffer, 0, textReceived) << endl;
	system("pause");
	closesocket(clientSocket);
	WSACleanup();
	exit(0);
}

void unknownCommand() {				//function for unknownCommand command
	send(clientSocket, buffer, 100, 0);
	textReceived = recv(clientSocket, buffer, 100, 0);
	cout << "server: " << string(buffer, 0, textReceived) << endl;
}

void main() {
	cout << "Input the IP address:" << endl;
	getline(cin, ip);
	cout << "IP Address: " << ip << "\t\tPort Number: " << 16000 << endl;

	serverLinking();


	while (true)
	{
		cout << "client: ";
		getline(cin, input);
		convetWords();

		if (strcmp(input.c_str(), "POST") == 0) {
			POST();
		}
		else if (strcmp(input.c_str(), "READ") == 0) {
			READ();
		}
		else if (strcmp(input.c_str(), "QUIT") == 0) {
			QUIT();
		}
		else {
			unknownCommand();
		}
		ZeroMemory(buffer, 100);				//to clear the buffer for prevent redundant message
	}
}

