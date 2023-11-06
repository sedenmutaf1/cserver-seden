#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 8080;
const std::string ROOT_DIR = "../site";

std::string GetContentType(const std::string& filePath) {
    if (filePath.find(".html") != std::string::npos) {
        return "text/html";
    } else if (filePath.find(".css") != std::string::npos) {
        return "text/css";
    } else {
        return "text/plain; charset=utf-8";
    }
}

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        std::cerr << "Error: Unable to create socket" << std::endl;
        return 1;
    }

    // Configure the server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Unable to bind to port " << PORT << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error: Unable to listen for connections" << std::endl;
        close(serverSocket);
        return 1;
    }

    while (true) {
        // Accept a connection from a client
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

        if (clientSocket == -1) {
            std::cerr << "Error: Unable to accept client connection" << std::endl;
            continue;
        }

        // Read the HTTP request from the client
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead == -1) {
            std::cerr << "Error: Unable to read data from client" << std::endl;
            close(clientSocket);
            continue;
        }

        // Parse the HTTP request to extract the requested file
        std::string request(buffer, bytesRead);
        std::string requestedFile;
        if (request.find("GET") != std::string::npos) {
            size_t start = request.find("GET") + 4;
            size_t end = request.find("HTTP") - 1;
            requestedFile = request.substr(start, end - start);
        }

        // Create a file path for the requested file
        std::string filePath = ROOT_DIR + requestedFile;

        // Open and read the file
        std::ifstream fileStream(filePath.c_str(), std::ios::in | std::ios::binary);
        std::stringstream responseStream;

        if (fileStream) {
            responseStream << "HTTP/1.1 200 OK\r\n";
            fileStream.seekg(0, std::ios::end);
            size_t fileSize = fileStream.tellg();
            fileStream.seekg(0, std::ios::beg);
            responseStream << "Content-Length: " << fileSize << "\r\n";
            responseStream << "Content-Type: " << GetContentType(requestedFile) << "\r\n\r\n";
            responseStream << fileStream.rdbuf();
        } else {
            responseStream << "HTTP/1.1 404 Not Found\r\n";
            responseStream << "Content-Length: 13\r\n";
            responseStream << "Content-Type: text/plain; charset=utf-8\r\n\r\n";
            responseStream << "File not found\r\n";
        }


        // Send the HTTP response to the client
        std::string response = responseStream.str();
        send(clientSocket, response.c_str(), response.size(), 0);

        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
