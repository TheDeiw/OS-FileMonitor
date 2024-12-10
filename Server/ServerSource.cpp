#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <array>
#include <sstream>
#include <filesystem>
#include <map>
#include <chrono>
#include <thread>
#include <system_error>

#pragma comment(lib, "ws2_32.lib")
namespace fs = std::filesystem;
static std::vector<std::array<std::string, 3>> cacheTable;

// Function to get creation data of file
std::string GetFileCreationTime(const std::wstring& filePath) {
    HANDLE fileHandle = CreateFile(
        filePath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (fileHandle == INVALID_HANDLE_VALUE) {
        return "Unknown";
    }

    FILE_BASIC_INFO fileInfo;
    if (GetFileInformationByHandleEx(fileHandle, FileBasicInfo, &fileInfo, sizeof(fileInfo))) {
        // Transforming CreationTime в FILETIME
        FILETIME fileTime;
        fileTime.dwLowDateTime = fileInfo.CreationTime.LowPart;
        fileTime.dwHighDateTime = fileInfo.CreationTime.HighPart;

        // Transforming FILETIME в SYSTEMTIME
        SYSTEMTIME creationTime;
        FileTimeToSystemTime(&fileTime, &creationTime);

        CloseHandle(fileHandle);

        // Data formating
        char buffer[20];
        sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
            creationTime.wYear,
            creationTime.wMonth,
            creationTime.wDay,
            creationTime.wHour,
            creationTime.wMinute,
            creationTime.wSecond);

        return std::string(buffer);
    }

    CloseHandle(fileHandle);
    return "Unknown";
}

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
        
        if (fs::exists(dir)) {
            if (fs::is_directory(dir)) {
                result << "OK" << dir << "| | \n";
            }
        }
        else {
            result << "ER" << dir << "| | \n";
        }
        bool isEmpty = true;

        try {
            // Make file iterator
            for (const auto& entry : fs::directory_iterator(dir)) {

                // Check for being a file
                if (entry.is_regular_file()) {
                    auto ext = entry.path().extension().string();
                    ext = ext.substr(1); //remove the dot before the expansion

                    // Searching
                    if (extensions.empty() || std::find(extensions.begin(), extensions.end(), ext) != extensions.end()) {

                        std::wstring wFilePath = entry.path().wstring();
                        std::string creationTime = GetFileCreationTime(wFilePath);

                        result << entry.path().filename().string() << "|"
                            << fs::file_size(entry.path()) / 1024 << " kb|" << creationTime << "\n";
                        isEmpty = false;
                    }
                }
            }
            if (isEmpty) {
                result << "-|-|- \n";
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return result.str();
}

std::string trimToLength(const std::string& str, size_t maxLength) {
    std::string result;
    for (char c : str) {
        if (c == '\n') {
            continue; // Пропустити символ нового рядка
        }
        result += c;
        if (result.size() >= maxLength) {
            break; // При досягненні maxLength завершуємо
        }
    }
    return result;
}


void printCacheTable() {
    size_t columnWidth = 70;
    size_t timeWidth = 6;
    size_t totalWidth = columnWidth * 2 + timeWidth + 7;

    while (true) {
        // Очищення консолі
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        std::cout << std::string(totalWidth + 3, '-') << std::endl;

        std::cout << "| "
            << std::setw(columnWidth) << std::left << "Client's request"
            << " | "
            << std::setw(columnWidth) << std::left << "Server's respond"
            << " | "
            << std::setw(timeWidth) << std::right << "Time"
            << " |" << std::endl;

        std::cout << std::string(totalWidth + 3, '-') << std::endl;

        for (const auto& row : cacheTable) {
            std::cout << "| "
                << std::setw(columnWidth) << std::left << trimToLength(row[0], columnWidth) << " | "
                << std::setw(columnWidth) << std::left << trimToLength(row[1], columnWidth) << " | "
                << std::setw(timeWidth) << std::right << row[2] << " |"
                << std::endl;
        }

        std::cout << std::string(totalWidth + 3, '-') << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
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

    // Binding and listeningg
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 3);

    std::cout << "Server waits..." << std::endl;
    std::thread textThread(printCacheTable);

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

        bool isContinue = false;
        // Buffer checking
        for (const auto& bufferRequest : cacheTable) {
            if (bufferRequest[0] == request) {
                std::string searchResult = bufferRequest[1];
                std::cout << "\n YEEEEEY \n";
                send(clientSocket, searchResult.c_str(), searchResult.size(), 0);
                closesocket(clientSocket);
                isContinue = true;
            }
        }

        if (isContinue) {
            continue;
        }

        // Request processing
        auto parts = split(request, ';');
        if (parts.size() == 2) {
            auto directories = split(parts[0], '|');
            auto extensions = split(parts[1], ',');

            // Search files
            std::string searchResult = searchFiles(directories, extensions);

            // Send result
            send(clientSocket, searchResult.c_str(), searchResult.size(), 0);

            cacheTable.push_back({ request, searchResult, "0"});
        }
        else if (parts.size() == 1) {

            auto directories = split(parts[0], '|');
            std::vector<std::string> extensions = {};

            // Search files
            std::string searchResult = searchFiles(directories, extensions);

            // Send result
            send(clientSocket, searchResult.c_str(), searchResult.size(), 0);

            cacheTable.push_back({ request, searchResult, "0"});
        }   

        // Close clint socket
        closesocket(clientSocket);
    }

    // Close server socket
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
