#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    std::string input;
    std::cout << "Enter the size of the Bloom filter array and hash functions (1 or 2): ";
    std::getline(std::cin, input);
    send(sock, input.c_str(), input.size(), 0);

    while (true)
    {
        std::cout << "Enter command and URL: ";
        std::getline(std::cin, input);
        send(sock, input.c_str(), input.size(), 0);

        valread = read(sock, buffer, BUFFER_SIZE);
        std::cout << "Server response: " << std::string(buffer, valread) << std::endl;
    }

    close(sock);
    return 0;
}
