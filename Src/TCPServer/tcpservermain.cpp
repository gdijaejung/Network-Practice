
#include <iostream>
#include "../Common/Common/common.h"
#include "../Common/Network/network.h"

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace network;

void main(char argc, char *argv[])
{
	if (argc < 2)
	{
		//cout << "Command Line <bind port> <udp=1 or tcp=0>" << endl;
		cout << "Command Line <bind port>" << endl;
		cout << "press enter key to exit program" << endl;
		getchar();
		return;
	}

	const int packetSize = 512;
	const int port = atoi(argv[1]);
	//const bool udp = atoi(argv[2]) ? true : false;
	//cout << "TCPServer " << port << endl;

	cTCPServer server;
	if (!server.Init(port))
	{
		cout << "server bind error" << endl;
		cout << "press enter key to exit program" << endl;
		getchar();
	}

	cout << "Server Start.." << endl;

	BYTE *recvBuffer = new BYTE[packetSize];

	int sessionCount = 0;
	while (1)
	{
		if (sessionCount != server.m_sessions.size())
		{
			cout << "session count = " << server.m_sessions.size() << endl;
			sessionCount = server.m_sessions.size();
		}

		if (!server.m_recvQueue.m_queue.empty())
		{
			network::sPacket packet;
			if (server.m_recvQueue.Front(packet))
			{
				memcpy(recvBuffer, packet.buffer, packet.actualLen);
				server.m_recvQueue.Pop();

				cout << "recv -> " << (char*)recvBuffer << endl;
			}
		}
	}

	SAFE_DELETEA(recvBuffer);
}
