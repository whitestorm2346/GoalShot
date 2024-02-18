#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(){
    // set up the dll

    SOCKET serverSocket, acceptSocket;
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

    // set up the server socket

    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(serverSocket == INVALID_SOCKET) {
        std::cout<< "Error at socket(): " << WSAGetLastError() << "\n\n";
        WSACleanup();
        return 0;
    }
    else {
        std::cout<< "socket() works well.\n\n";
    }

    // bind socket

    sockaddr_in service;

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(port);

    if(bind(serverSocket,
            reinterpret_cast<SOCKADDR*>(&service),
            sizeof(service)) == SOCKET_ERROR) {
        std::cout<< "bind() failed: " << WSAGetLastError() << "\n\n";
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        std::cout<< "bind() works well.\n\n";
    }

    // initial listen

    if(listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cout<< "Error at listen(): " << WSAGetLastError() << "\n\n";
    }
    else {
        std::cout<< "listen() works well. Waiting for connections...\n\n";
    }

    // accept connection

    acceptSocket = accept(serverSocket, NULL, NULL);

    if(acceptSocket == INVALID_SOCKET) {
        std::cout<< "accept failed: " << WSAGetLastError() << "\n\n";
        WSACleanup();
        return -1;
    }
    else {
        std::cout<< "Accepted the connection.\n\n";
    }

    // chat to the client

    char buffer[200];

    int byteCount = recv(acceptSocket, buffer, 200, 0);

    if(byteCount > 0) {
        std::cout<< "Message receive: " << buffer << "\n\n";
    }
    else {
        WSACleanup();
    }

    system("pause");
    WSACleanup();

    return 0;
}
