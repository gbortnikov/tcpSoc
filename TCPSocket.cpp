#include "TCPSocket.hpp"
#include "boost/serialization/nvp.hpp"



TCPSocket::TCPSocket() {

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &this->wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
	}
	idclient = 0;

}

int TCPSocket::init(std::string port) {

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
}
int TCPSocket::creatSoc() {
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
}
int TCPSocket::bindSoc() {

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		freeaddrinfo(result);
		return 1;
	}
}

int TCPSocket::listenSoc() {
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
}

int TCPSocket::connectSoc() {
	SOCKET clientSocket;
	int id = idclient;
	clientSocket = INVALID_SOCKET;
	
	clientSocket = accept(ListenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 0;
	}
	printf("accept client  \n");
	ClientSocketArray.insert(std::pair<char, int>(id, clientSocket));
	idclient++;
	return id;
}

int TCPSocket::recSoc(int s) {
	char recvbuf[512];
	int iResult, iSendResult;
	int recvbuflen = 512;
	do {

		iResult = recv(ClientSocketArray[s], recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			recvbuf[iResult] = '\0';
			printf("Received msg: %s---%d\n", recvbuf, strlen(recvbuf));

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocketArray[s], recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(ClientSocketArray[s]);

				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0) {
			printf("Connection closing...\n");
			ClientSocketArray.erase(ClientSocketArray.erase(s));
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientSocketArray[s]);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);
}

int TCPSocket::handler(std::string str) {


	return 0;
}