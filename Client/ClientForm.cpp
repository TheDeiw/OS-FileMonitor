#include "ClientForm.h"

#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

//Client::ClientForm::
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

System::Void Client::ClientForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
    // TEMP Setting UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // TEMP

    WSADATA wsa;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[4096] = { 0 };

    // Winsock initialization
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Creating a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Setting the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connecting to the server
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Forming a request
    //std::string directories = "D:\\6. University\\2 Semestr\\Çâ³òè_2sem,D:\\6. University\\1 Semestr\\Çâ³òè";
    std::string directories = "D:\\Óí³âåðñèòåò\\2ÊÓÐÑ\\ÎÑ,D:\\Óí³âåðñèòåò\\Àíãë³éñüêà ìîâà";
    std::string extensions = "txt,pdf";
    std::string request = directories + ";" + extensions;

    // Sending a request
    send(clientSocket, request.c_str(), request.size(), 0);

    // Getting a response
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::string response(buffer);
    auto rows = split(response, '\n');

    fileTable->Rows->Clear();

    for (const auto& row : rows) {
        auto fields = split(row, '|');
        if (fields.size() == 3) {
            std::cout << "Filename: " << fields[0]
                << ", Size: " << fields[1]
                << ", Creation Date: " << fields[2] << std::endl;
            if (fields[1] == " ")
            {
                fileTable->Rows->Add(
                    gcnew System::String(fields[0].c_str()),
                    gcnew System::String(fields[1].c_str()),
                    gcnew System::String(fields[2].c_str())
                );
            }
            else
            {
                fileTable->Rows->Add(
                    gcnew System::String(fields[0].c_str()),
                    gcnew System::String((fields[1] + " kb").c_str()),
                    gcnew System::String(fields[2].c_str())
                );
            }
        }
    }
    std::cout << "Response from server: " << buffer << std::endl;

    // Closing the socket
    closesocket(clientSocket);
    WSACleanup();
}
