#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char message[MAX_MSG_SIZE];

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept a connection from a client
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Receive and print messages
    while (1) {
        memset(message, 0, sizeof(message));  // Clear the message buffer
        if (recv(client_socket, message, sizeof(message), 0) <= 0) {
            perror("Error receiving message");
            break;
        }
        printf("Client: %s", message);
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

