#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib") //DLL

using namespace std;

int main()
{
	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result < 0)
	{
		cout << "Winsock init Error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "make socket error.  " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN)); 
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(12345); // host to network short

	int Status = connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Status == SOCKET_ERROR)
	{
		cout << "bind error.  " << GetLastError() << endl;
		exit(-1);
	}

	char Buffer[1024] = { 0, };

	int RecvBytes = recv(ServerSocket, Buffer, 1024, 0);
	if (RecvBytes <= 0)
	{
		cout << "recv error.  " << GetLastError() << endl;
		exit(-1);
	}

	cout << Buffer << endl;

	int SendBytes = send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);
	if (SendBytes <= 0)
	{
		cout << "send error.  " << GetLastError() << endl;
		exit(-1);
	}

	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}