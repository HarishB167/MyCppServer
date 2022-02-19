#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <csignal>

#include "server.h"
#include "utils.h"

using namespace std;

Server server;

void exitHandler(int signal)
{
    server.closeListeningSocket();
    server.closeClientConnection();
    exit(0);
}

int main()
{
    string defaultMessage = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    signal(SIGINT, exitHandler);
    server.createSocket();
    server.bindSocket();
    server.markListening();
    while (true)
    {
        if (server.acceptCall() < 0)
        {
            cout << "Continuing acceptCall." << endl;
            continue;
        }
        server.printConnectionInfo();
        server.handleRequest(defaultMessage);
        server.closeClientConnection();
    }
    server.closeListeningSocket();
    server.closeClientConnection();
}