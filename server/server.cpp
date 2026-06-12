#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

int main() {
	// Step_0
	SOCKET serverSocket, acceptSocket;
	int port = 5555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The WinSock dll is not found" << endl;
		return 0;
	}
	else {
		cout << "WinSock.dll Found!!" << endl;
		cout << "The Status" << wsaData.szSystemStatus << endl;
	}
	
	// Step_1 Creating SOcket
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Error at Socket()" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Socket is OK!!" << endl;
	}

	// Step 2 Bindidng the Port + IP Address
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET,L"127.0.0.1", &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind () function failed!!" << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Bind Done Successfully!!!" << endl;
	}


	//Step 3 Listninggg
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		cout << "Listning(): Error" << WSAGetLastError() << endl;
	}
	else {
		cout << "Listning for Client...." << endl;
	}

	//Step 4 Accept / Connect
	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		cout << "Accept/Connection Failed!!" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Connection Accepted" << endl;

	// Step 5 CHat (Client/Server)
	char buffer[200]="";
	int byteCount = recv(acceptSocket, buffer, 200, 0);
	if (byteCount > 0) {
		cout << "Message_Recieved... " << buffer << endl;
		cout << byteCount << "bytes Recieved" << endl;
	}
	else {
		WSACleanup();
	}

	// confirmation
	char confirmation[30] = "Hey The Message Is Recieved!";
	byteCount = send(acceptSocket, confirmation, 30, 0);
	if (byteCount > 0) {
		cout << "Automatic_Message_Sent... " << endl;
	}
	else {
		WSACleanup();
	}

	// Step 5 Closer Block
	system("pause");
	WSACleanup();
}