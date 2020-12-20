#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//
#include "TCPSocket.hpp"


int main() {

	TCPSocket soc;
	soc.init("7777");
	soc.creatSoc();
	soc.bindSoc();
	soc.listenSoc();
	while (true)
	{
		int s = soc.connectSoc();
		printf("s=%d",s);
		soc.threads.push_back(std::thread(&TCPSocket::recSoc, &soc, s));

	}
}