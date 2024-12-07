#include <winsock2.h>
#include <iostream>
#include <chrono>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    fd_set readfds; // Множина сокетів для перевірки
    char buffer[1024] = { 0 };
    int clientSize = sizeof(clientAddr);

    // Ініціалізація Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Створення сокета
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Налаштування адреси сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Порт
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Прив'язка сокета
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Прослуховування
    listen(serverSocket, 3);
    std::cout << "Server waits..." << std::endl;

    while (true) {
        // Очищення множини сокетів
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);

        // Тайм-аут для select (5 секунд)
        timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // Перевірка наявності з'єднань чи даних
        int activity = select(0, &readfds, nullptr, nullptr, &timeout);

        if (activity == SOCKET_ERROR) {
            std::cerr << "Error select" << std::endl;
            break;
        }

        if (activity == 0) {
            // Якщо за 5 секунд нічого не відбулося
            std::cout << "Waiting for the client." << std::endl;
        }
        else if (FD_ISSET(serverSocket, &readfds)) {
            // Нове вхідне з'єднання
            clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
            if (clientSocket == INVALID_SOCKET) {
                std::cerr << "Error connection" << std::endl;
                continue;
            }

            std::cout << "Client connected!" << std::endl;

            // Обмін даними з клієнтом
            recv(clientSocket, buffer, sizeof(buffer), 0);
            std::cout << "Client said: " << buffer << std::endl;

            const char* response = "Hi client!";
            send(clientSocket, response, strlen(response), 0);

            // Закриття клієнтського сокета
            closesocket(clientSocket);
        }

        // Затримка для тестування (можна прибрати)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Закриття серверного сокета
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
