#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

int main() {

	// Setup 0 WSAStartup
	SOCKET clientSocket;
	int port = 5555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "WinSocket NotFound!!" << endl;
	}
	else {
		cout << "WinSocket Found (dll)!!" << endl;
		cout << wsaData.szSystemStatus << endl;
	}

	// Setup 1 Socket Creation
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at Socket()" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Socket is OK!!" << endl;
	}

	// Step 2 Bind the IP + Port  // Bind toa  struct for addr of port and IP
	sockaddr_in clientservice;
	clientservice.sin_family = AF_INET;
	InetPton(AF_INET, L"127.0.0.1", &clientservice.sin_addr.s_addr);
	clientservice.sin_port = htons(port);
	if (connect(clientSocket,(SOCKADDR*)&clientservice,sizeof(clientservice)) == SOCKET_ERROR) {
		cout << "Failed to connect" << WSAGetLastError() << endl;
		closesocket(clientSocket);
		return 0;
	}
	else {
		cout << "Connection Done Successfully!!!" << endl;
	}

	// Step 3 Chat (Server/Client)
	char buffer[200];
	cout << "Please Enter Your MEssage!!" << endl;
	cin.getline(buffer, 200);
	int byteCount = send(clientSocket, buffer, 200, 0);
	if (byteCount > 0) {
		cout << "Message_sent... " << buffer << endl;
		cout << byteCount << "bytes sent" << endl;
	}
	else {
		cout << "Message not sent......" << endl;
		WSACleanup();
	}

	// confirmation
	char confirmation[30] = "";
	byteCount = recv(clientSocket, confirmation, 30, 0);
	if (byteCount > 0) {
		cout << "Automated_Message_Confirmation_recieved... " << endl;
	}
	else {
		WSACleanup();
	}
	// Step 4 CLOSE SOCKETS
	system("pause");
	WSACleanup();
	return 0;
} 