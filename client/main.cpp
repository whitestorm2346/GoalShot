#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

int main()
{
    // set up the dll

    SOCKET clientSocket, acceptSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);

    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if(wsaerr) {
        std::cout<< "The Winsock dll not found.\n\n";
        return 0;
    }
    else {
        std::cout<< "The Winsock dll found.\n";
        std::cout<< "The status: " << wsaData.szSystemStatus << "\n\n";
    }

    // set up the client socket

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(clientSocket == INVALID_SOCKET) {
        std::cout<< "Error at socket(): " << WSAGetLastError() << "\n\n";
        WSACleanup();
        return 0;
    }
    else {
        std::cout<< "socket() works well.\n\n";
    }

    // connect with the server socket

    sockaddr_in clientService;

    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(port);

    if(connect(clientSocket,
            reinterpret_cast<SOCKADDR*>(&clientService),
            sizeof(clientService)) == SOCKET_ERROR) {
        std::cout<< "connect() failed: " << WSAGetLastError() << "\n\n";
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }
    else {
        std::cout<< "connect() works well.\n\n";
    }

    // chat to the server

    char buffer[200];

    std::cout<< "Enter something to show on server:\n";
    std::cin.getline(buffer, 200);

    int byteCount = send(clientSocket, buffer, 200, 0);

    if(byteCount > 0) {
        std::cout<< "Message sent: " << buffer << "\n\n";
    }
    else {
        WSACleanup();
    }

    system("pause");
    WSACleanup();

    return 0;
}
