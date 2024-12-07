#include "ClientForm.h"

#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

//Client::ClientForm::

System::Void Client::ClientForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
    WSADATA wsa;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    const char* message = "Hi, server!";
    char buffer[1024] = { 0 };

    // ����������� Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // ��������� ������
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // ������������ ������ �������
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // ����
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ��������� ������

    // ϳ��������� �� �������
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // ���������� ����������� �������
    send(clientSocket, message, strlen(message), 0);

    // ��������� ������ �� �������
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Server answer: " << buffer << std::endl;

    // �������� ������
    closesocket(clientSocket);
    WSACleanup();

    //return 0;
}
