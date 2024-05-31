#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <thread>
#include <vector>
#include "InputOutput.h"

#define PORT 5000
#define MAX_CLIENTS 30

using namespace std;

/**
 * Function to handle each client connection.
 * @param clientSocket - the client socket descriptor
 */
void handleClient(int clientSocket)
{
    InputOutput ioHandler;
    ioHandler.run(clientSocket);
}

/**
 * Function to create and set up the server socket.
 * @return the master socket descriptor
 */
int createSocket()
{
    int opt = 1;
    int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (master_socket == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    return master_socket;
}

int main(int argc, char *argv[])
{
    int master_socket = createSocket();
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(master_socket, 3) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    // Vector to keep track of client threads
    std::vector<std::thread> clientThreads;

    while (true)
    {
        int clientSocket = accept(master_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (clientSocket < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Create a new thread for each client connection
        clientThreads.emplace_back(handleClient, clientSocket);
    }

    // Join all client threads
    for (auto &thread : clientThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    return 0;
}
