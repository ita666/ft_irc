#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    
    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Connect to server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // Close socket
    close(client_socket);
    
    return 0;
}
