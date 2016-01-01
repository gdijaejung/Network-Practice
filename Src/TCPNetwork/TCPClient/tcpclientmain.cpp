//
// 2016.01.01, jjuiddong
// TCP Client 프로그램
//
//
#include <iostream>
#include "../../Common/Common/common.h"
#include "../../Common/Network/network.h"

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace network;

void main(char argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "command line <ip> <port>" << endl;
		cout << "press enter to exit program" << endl;
		getchar();
		return;
	}

	const int packetSize = 512;
	const string ip = argv[1];
	const int port = atoi(argv[2]);

	network::cTCPClient client;
	if (!client.Init(ip, port, packetSize))
	{
		cout << "error connect client" << endl;
		cout << "press enter to exit program" << endl;
		getchar();
		return;
	}

	cout << "client start" << endl;

	char *data = new char[packetSize];
	while (1)
	{
		if (!client.IsConnect())
			continue;

		string str;
		cin >> str;
		ZeroMemory(data, packetSize);
		strcpy_s(data, packetSize, str.c_str());

		client.Send((BYTE*)data, str.length()+1);
	}

	delete[] data;
}
