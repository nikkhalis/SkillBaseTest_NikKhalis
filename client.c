#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    int random_number;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1;
    }

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        return 1;
    }

    // Set up the server structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server IP if it's on a different machine
    server.sin_port = htons(8443);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Failed to connect to the server.\n");
        closesocket(client_socket);
        return 1;
    }

    // Receive the random number from the server
    recv(client_socket, (char*)&random_number, sizeof(int), 0);
    printf("Random number received from the server: %d\n", random_number);

    // Close the socket and cleanup Winsock
    closesocket(client_socket);
    WSACleanup();

    return 0;
}

