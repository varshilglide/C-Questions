#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CLIENTS 10
#define MAX_MESSAGE_LENGTH 1024

// Structure for client data
typedef struct {
    int socket;
    sem_t semaphore;
} client_queue_t;

client_queue_t client_queue[MAX_CLIENTS];
int client_id = 0;

void *handle_client(void *client_id_ptr) {
    int client_id = *((int *)client_id_ptr);
    int client_socket = client_queue[client_id].socket;
    char message[MAX_MESSAGE_LENGTH];

    while (1) {
        // Read message from client
        int bytes_received = read(client_socket, message, MAX_MESSAGE_LENGTH);
        if (bytes_received <= 0) {
            // Client disconnected
            break;
        }
        // Broadcast message to all clients
        for (int i = 0; i < client_id; i++) {
            sem_wait(&client_queue[i].semaphore);
            write(client_queue[i].socket, message, bytes_received);
            sem_post(&client_queue[i].semaphore);
        }
    }

    // Clean up client data
    sem_wait(&client_queue[client_id].semaphore);
    close(client_queue[client_id].socket);
    sem_post(&client_queue[client_id].semaphore);

    pthread_exit(NULL);
}

int main() {
    int server_socket;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int client_address_length = sizeof(client_address);
    pthread_t client_thread;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating server socket");
        exit(1);
    }

    // Bind server socket to address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(5555);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket to address");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Error listening for incoming connections");
        exit(1);
    }

    // Initialize client queues
        for (int i = 0; i < MAX_CLIENTS; i++) {
        sem_init(&client_queue[i].semaphore, 0, 1);
    }

    // Main loop to accept incoming connections and create client threads
    while (1) {
        // Accept incoming connection
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_length);
        if (client_socket < 0) {
            perror("Error accepting incoming connection");
            continue;
        }

        // Store client data in queue
        sem_wait(&client_queue[client_id].semaphore);
        client_queue[client_id].socket = client_socket;
        sem_post(&client_queue[client_id].semaphore);

        // Create thread to handle client
        int *client_id_ptr = malloc(sizeof(int));
        *client_id_ptr = client_id;
        if (pthread_create(&client_thread, NULL, handle_client, (void *)client_id_ptr) != 0) {
            perror("Error creating client thread");
            continue;
        }

        // Increment client ID
        client_id = (client_id + 1) % MAX_CLIENTS;
    }

    // Clean up server socket
    close(server_socket);

    return 0;
}

