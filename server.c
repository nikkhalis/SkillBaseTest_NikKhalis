#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_addr_size, random_number;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1;
    }

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        return 1;
    }

    // Set up the server structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8443);

    // Bind
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        closesocket(server_socket);
        return 1;
    }

    // Listen
    listen(server_socket, 1);

    // Accept an incoming connection
    printf("Waiting for a client to connect...\n");
    client_addr_size = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr*)&client, &client_addr_size);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(server_socket);
        return 1;
    }

    // Generate a random number and send it to the client
    random_number = rand() % 900 + 100;
    send(client_socket, (char*)&random_number, sizeof(int), 0);
    printf("Random number sent to the client: %d\n", random_number);

    // Close the sockets and cleanup Winsock
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
