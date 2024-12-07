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

    // Ініціалізація Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Створення сокета
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Налаштування адреси сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Порт
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Локальний сервер

    // Підключення до сервера
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Надсилання повідомлення серверу
    send(clientSocket, message, strlen(message), 0);

    // Отримання відповіді від сервера
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Server answer: " << buffer << std::endl;

    // Закриття сокета
    closesocket(clientSocket);
    WSACleanup();

    //return 0;
}
