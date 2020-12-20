#pragma once



#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h> 
#include <string>
#include <vector>
#include <thread>
#include <map>
//
#pragma comment(lib, "Ws2_32.lib")

class TCPSocket
{
private:
	WSADATA wsaData;
	int iResult;
	SOCKET ListenSocket = INVALID_SOCKET;
	std::map <int, SOCKET> ClientSocketArray;
	int idclient;



public:
	std::vector<std::thread>threads;

	TCPSocket();
	int init(std::string port = "8888");
	int creatSoc();
	int bindSoc();
	int listenSoc();
	int connectSoc();
	int recSoc(int s);
};

