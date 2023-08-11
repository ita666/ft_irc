#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    
    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Bind
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // Listen
    listen(server_socket, 5);
    
    // Accept incoming connections
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    
    // Close sockets
    close(client_socket);
    close(server_socket);
    
    return 0;
}



