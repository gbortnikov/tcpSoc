#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//
#include "TCPSocket.hpp"

#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/rapidjson/stringbuffer.h"
#include "../../rapidjson/writer.h"


int main() {

	TCPSocket soc;
	soc.init("9999");
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