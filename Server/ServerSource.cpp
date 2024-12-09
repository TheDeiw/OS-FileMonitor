#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <map>
#include <chrono>
#include <thread>


#pragma comment(lib, "ws2_32.lib")
namespace fs = std::filesystem;

// Function to split a string
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to search for files
std::string searchFiles(const std::vector<std::string>& directories, const std::vector<std::string>& extensions) {
    std::ostringstream result;

    // Search in each directory
    for (const auto& dir : directories) {

        // Make file iterator
        for (const auto& entry : fs::directory_iterator(dir)) {

            // Check for being a file
            if (entry.is_regular_file()) {
                auto ext = entry.path().extension().string();
                ext = ext.substr(1); //remove the dot before the expansion

                // Searching
                if (std::find(extensions.begin(), extensions.end(), ext) != extensions.end()) {

                    // Forming a line with file data
                    result << entry.path().filename().string() << "|"
                        << fs::file_size(entry.path()) << "|a\n";

                    // TIME DOESN`T WORK
                    //auto ftime = fs::last_write_time(entry.path());
                    //auto sys_time = decltype(ftime)::clock::to_sys(ftime); // Перетворення в system_clock
                    //std::time_t cftime = std::chrono::system_clock::to_time_t(sys_time); // Перетворення на time_t
                    //result << std::ctime(&cftime); // Форматування часу як рядка
                }
            }
        }
    }

    return result.str();
}

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientSize = sizeof(clientAddr);
    char buffer[4096] = { 0 };


    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Setting the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Binding and listening
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 3);

    std::cout << "Server waits..." << std::endl;

    while (true) {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error connection!" << std::endl;
            continue;
        }

        // Receiving the request
        std::fill(std::begin(buffer), std::end(buffer), 0);
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::string request(buffer);
        std::cout << "Received request: " << request << std::endl;

        // Request processing
        auto parts = split(request, ';');
        if (parts.size() == 2) {
            auto directories = split(parts[0], ',');
            auto extensions = split(parts[1], ',');

            // Search files
            std::string searchResult = searchFiles(directories, extensions);

            // Send result
            send(clientSocket, searchResult.c_str(), searchResult.size(), 0);
        }

        // Close clint socket
        closesocket(clientSocket);
    }

    // Close server socket
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
