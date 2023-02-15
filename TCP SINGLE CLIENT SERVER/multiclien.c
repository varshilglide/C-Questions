#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_MESSAGE_LENGTH 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char message[MAX_MESSAGE_LENGTH];

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating client socket");
        exit(1);
    }

    // Connect to server
    memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8888);
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Read message from user and send to server
    printf("Enter message: ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    if (send(client_socket, message, strlen(message), 0) < 0) {
        perror("Error sending message to server");
        exit(1);
    }

    // Receive response from server
        int received_bytes = recv(client_socket, message, MAX_MESSAGE_LENGTH, 0);
    if (received_bytes < 0) {
        perror("Error receiving message from server");
        exit(1);
    }
    message[received_bytes] = '\0';

    // Print response from server
    printf("Received message: %s\n", message);

    // Close socket
    close(client_socket);

    return 0;
}


