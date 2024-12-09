#include "ClientForm.h"

#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>

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

bool checkDir(std::string& input) {
    const char forbiddenChars[] = {'<', '>', '|', '?', '*'};

    // Check each character in the string
    for (char ch : input) {
        for (char forbidden : forbiddenChars) {
            if (ch == forbidden) {
                return false; // If a forbidden character is found, return false
            }
        }
    }

    return true; // No forbidden characters found
}

bool hasOnlyAlphanumeric(const std::string& extensions) {
    for (char ch : extensions) {
        if (!std::isalnum(static_cast<unsigned char>(ch))&&ch!=' ') {
            return false; // Non-alphanumeric character found
        }
    }
    return true; // All characters are alphanumeric
}

std::string convertDirInput(std::string& input) {
    input.erase(std::remove(input.begin(), input.end(), '\"'), input.end());
    // Step 1: Remove leading and trailing whitespace
    auto start = input.find_first_not_of(" \t\n\r");
    auto end = input.find_last_not_of(" \t\n\r");
    std::string trimmed = (start == std::string::npos) ? "" : input.substr(start, end - start + 1);

    // Step 2: Replace all whitespace sequences with a comma
    std::regex whitespaceRegex("\\s+");
    std::string result = std::regex_replace(trimmed, whitespaceRegex, ",");

    return result;
}

std::string convertExtInput(const std::string& input) {
    // Step 1: Remove leading and trailing whitespace
    auto start = input.find_first_not_of(" \t\n\r");
    auto end = input.find_last_not_of(" \t\n\r");
    std::string trimmed = (start == std::string::npos) ? "" : input.substr(start, end - start + 1);

    // Step 2: Replace multiple spaces with a single comma
    std::regex whitespaceRegex("\\s+");
    std::string result = std::regex_replace(trimmed, whitespaceRegex, ",");

    return result;
}

System::Void Client::ClientForm::showButton_Click(System::Object^ sender, System::EventArgs^ e) {
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

    std::string inputDir = msclr::interop::marshal_as<std::string>(textBoxDir->Text);
    if (!checkDir(inputDir)) {
        MessageBox::Show("Path is invalid. Can't use '<', '>', '|', '?', '*'", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        closesocket(clientSocket);
        WSACleanup();
        return;
    }
    std::string directories = convertDirInput(inputDir);
    if (directories.empty()) {
        MessageBox::Show("Please enter the path.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    //std::string extensions = "txt,pdf";
    std::string inputExt = msclr::interop::marshal_as<std::string>(textBoxExtension->Text);
    if (!hasOnlyAlphanumeric(inputExt)) {
        MessageBox::Show("Extensions are invalid. Only Latin characters and numbers are allowed", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        closesocket(clientSocket);
        WSACleanup();
        return;
    }
    std::string extensions = convertDirInput(inputExt);
  
    std::string request = directories + ";" + extensions;

    // Sending a request
    send(clientSocket, request.c_str(), request.size(), 0);

    // Getting a response
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::string response(buffer);
    auto rows = split(response, '\n');

    fileTable->Rows->Clear();
    int rowIndex;

    for (const auto& row : rows) {
        auto fields = split(row, '|');
        if (fields.size() == 3) {
            std::cout << "Filename: " << fields[0]
                << ", Size: " << fields[1]
                << ", Creation Date: " << fields[2] << std::endl;
            if (fields[1] == " ")
            {
                rowIndex = fileTable->Rows->Add(
                    gcnew System::String(fields[0].c_str()),
                    gcnew System::String(fields[1].c_str()),
                    gcnew System::String(fields[2].c_str())
                );

                fileTable->Rows[rowIndex]->DefaultCellStyle->Font = gcnew System::Drawing::Font(fileTable->Font, System::Drawing::FontStyle::Bold);
                fileTable->Rows[rowIndex]->DefaultCellStyle->BackColor = System::Drawing::Color::LightBlue;
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
