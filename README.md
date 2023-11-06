<div id="header" align="center">
  <img src="https://media.giphy.com/media/M9gbBd9nbDrOTu1Mqx/giphy.gif" width="100"/>
</div>

# Web Server 

## Introduction

Welcome to the Web Server! This software is a simple web server implemented in C++. It is designed to serve static web content, such as HTML and CSS files, to clients and handle HTTP requests. This README provides an overview of the software's purpose, how to use it, and potential safety concerns.

## Purpose

The purpose of this software is to demonstrate how a basic web server works and serve as a learning tool for those interested in web server development. It's a minimalistic web server that responds to GET requests and serves static web content, specifically HTML and CSS files.

## Usage

To use the web server, follow these steps:

1. Compile the source code:g++ server.cpp -o server
2. Run the web server:./server
3. Access the server in your web browser:
- Open your web browser.
- Navigate to http://localhost:8080/index.html (or the port you specified in the code).

4. The server will respond to GET requests for the "index.html" and "style.css" files located in the specified ROOT_DIR.

## Safety Concerns

While this software is intended for educational purposes, it is essential to be aware of potential safety concerns:

1. **Security**: This web server is minimalistic and does not include robust security features. It should not be used in production environments without extensive security enhancements.

2. **Concurrency**: The server handles one client at a time. If multiple clients connect simultaneously, the behavior may not be as expected.

3. **Resource Consumption**: The server does not have resource management and can consume significant resources if abused or if a large number of clients connect.

4. **File System Access**: The server reads files from the file system based on client requests. Ensure that the ROOT_DIR points to a safe directory and that unwanted access is restricted.
