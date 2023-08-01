#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
	// Create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1)
	{
		cerr << "Can't create a socket!";
		return -1;
	}

	// Bind thesockt to a IP / port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000); // host to network short
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); // convert IP address from text to binary form 127.0.0.1

	if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
	{
		cerr << "Can't bind to IP/port";
		return -2;
	}

	// Mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1)
	{
		cerr << "Can't listen!";
		return -3;
	}

	// Accept a call
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];

	int clientSocket = accept(listening,
							(sockaddr *)&client,
							&clientSize);

	if (clientSocket == -1)
	{
		cerr << "Problem with client connecting!";
		return -4;
	}

	// Close the listening socket
	close(listening);

	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr *)&client,
							sizeof(client),
							host,
							NI_MAXHOST,
							svc,
							NI_MAXSERV,
							0);
	
	if (result)
	{
		cout << host << " connected on " << svc << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on " << ntohs(client.sin_port) << endl;
	}

	// While loop: accept and echo message back to client
	char buf[4096];
	while (true)
	{
		// Clear the buffer
		memset(buf, 0, 4096);
		// Wait for a message
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == -1)
		{
			cerr << "There was a connection issue" << endl;
			break;
		}
		if (bytesReceived == 0)
		{
			cout << "The client disconnected" << endl;
			break;
		}

		// Display message
		cout << "Received: " << string(buf, 0, bytesReceived) << endl;

		// Resend message
		send(clientSocket, buf, bytesReceived + 1, 0);
	}

	// Close the socket
	close(clientSocket);

	return 0;
}