#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[MAX_MSG_SIZE];

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with server IP
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Send messages to the server
    while (1) {
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
    }

    // Close the socket
    close(client_socket);

    return 0;
}

