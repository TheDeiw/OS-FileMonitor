#include <winsock2.h>
#include <iostream>
#include <chrono>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    fd_set readfds; // ������� ������ ��� ��������
    char buffer[1024] = { 0 };
    int clientSize = sizeof(clientAddr);

    // ����������� Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // ��������� ������
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // ������������ ������ �������
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // ����
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // ����'���� ������
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // ���������������
    listen(serverSocket, 3);
    std::cout << "Server waits..." << std::endl;

    while (true) {
        // �������� ������� ������
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);

        // ����-��� ��� select (5 ������)
        timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // �������� �������� �'������ �� �����
        int activity = select(0, &readfds, nullptr, nullptr, &timeout);

        if (activity == SOCKET_ERROR) {
            std::cerr << "Error select" << std::endl;
            break;
        }

        if (activity == 0) {
            // ���� �� 5 ������ ����� �� ��������
            std::cout << "Waiting for the client." << std::endl;
        }
        else if (FD_ISSET(serverSocket, &readfds)) {
            // ���� ������ �'�������
            clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
            if (clientSocket == INVALID_SOCKET) {
                std::cerr << "Error connection" << std::endl;
                continue;
            }

            std::cout << "Client connected!" << std::endl;

            // ���� ������ � �볺����
            recv(clientSocket, buffer, sizeof(buffer), 0);
            std::cout << "Client said: " << buffer << std::endl;

            const char* response = "Hi client!";
            send(clientSocket, response, strlen(response), 0);

            // �������� �볺�������� ������
            closesocket(clientSocket);
        }

        // �������� ��� ���������� (����� ��������)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // �������� ���������� ������
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
