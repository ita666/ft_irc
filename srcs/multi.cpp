
#include "includes.hpp"

int main() {
	// Create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1) {
		cerr << "Can't create a socket!";
		return -1;
	}

	// Bind thesockt to a IP / port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);				   // host to network short
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); // convert IP address from text to binary form 127.0.0.1

	if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1) {
		cerr << "Can't bind to IP/port";
		return -2;
	}

	// Mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1) {
		cerr << "Can't listen!";
		return -3;
	}

	fd_set master;

	FD_ZERO(&master); // Initilize the master set to 0
	FD_SET(listening, &master);

	string password = "1234";
	while (true) {
		fd_set copy = master;

		if (select(FD_SETSIZE, &copy, NULL, NULL, NULL) < 0) {
			perror("select error");
			exit(0);
		}
	int client_socket;
		for (int i = 0; i < FD_SETSIZE; i++) {
			if (FD_ISSET(i, &copy)) {
				if (i == listening) {
					// this is a new connection
					client_socket = accept(listening, NULL, NULL);
					char password_request[] = "Enter password: ";
					send(client_socket, password_request, sizeof(password_request), 0);
					FD_SET(client_socket, &master);
				} else {
					char client_password[256];
					if (recv(client_socket, &client_password, sizeof(client_password), 0) < 0) {
						perror("recv error");
						exit(0);
					}
					else {
						if (password != client_password)
							FD_CLR(i, &master);
					}
					// do whatever we do with connections
				}
			}
		}
	}
	return 0;
}