#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "utils.h"
#include "request_processor.h"

#pragma once

using namespace std;

class Server
{
public:
    int listening;
    int clientSocket;
    string myString;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

public:
    int createSocket()
    {
        // Create a socket
        listening = socket(AF_INET, SOCK_STREAM, 0);
        if (listening == -1)
        {
            cerr << "Can't create a socket!";
            exit(EXIT_FAILURE);
            return -1;
        }

        cout << "New version : File descriptor of new socket is : " << listening << endl;
        return 0;
    }

    // Bind the socket to a IP / port
    int bindSocket()
    {
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(50000);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

        if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
        {
            cerr << "Can't bind to IP/port\n";
            exit(EXIT_FAILURE);
            return -2;
        }
        return 1;
    }

    // Mark the socket for listening in
    int markListening()
    {
        if (listen(listening, SOMAXCONN) == -1)
        {
            cerr << "Can't listen!\n";
            exit(EXIT_FAILURE);
            return -3;
        }
        return 1;
    }

    // Accept a call
    int acceptCall()
    {
        clientSocket = accept(listening,
                              (sockaddr *)&client,
                              &clientSize);
        if (clientSocket == -1)
        {
            cerr << "Problem with client connecting!\n";
            exit(EXIT_FAILURE);
            return -4;
        }

        cout << "File descriptor of CLIENT socket is : " << clientSocket << endl;
        return 1;
    }

    // Close the listening socket
    int closeListeningSocket()
    {
        close(listening);
        return 1;
    }

    // Print the connection info
    int printConnectionInfo()
    {
        memset(host, 0, NI_MAXHOST);
        memset(svc, 0, NI_MAXSERV);

        int result = getnameinfo((sockaddr *)&client,
                                 sizeof(client),
                                 host,
                                 NI_MAXHOST,
                                 svc,
                                 NI_MAXSERV,
                                 0);

        if (result)
        {
            cout << host << " connected on " << svc << endl;
            cout << "Result of getnameinfo : " << result << endl;
        }
        else
        {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on " << ntohs(client.sin_port) << endl;
            cout << "Result 2 of getnameinfo : " << result << endl;
        }
        return 1;
    }

    // While receiving display message, echo message
    int handleRequest(string message)
    {
        char buf[4096];

        while (true)
        {
            // Clear the buffer
            memset(buf, 0, 4096);

            // Wait for a message
            int bytesRecv = recv(clientSocket, buf, 4096, 0);
            if (bytesRecv == -1)
            {
                cerr << "There was a connection issue" << endl;
                break;
            }

            if (bytesRecv == 0)
            {
                cout << "The client disconnected" << endl;
                break;
            }

            // Display message
            print("------------------------------");
            cout << "Recieved: " << endl;
            printFirstNLines(4, buf);
            string response = processHTTPRequest(buf);
            print("------------------------------");

            // Resend message
            print("------------------------------");
            cout << "Resend message : " << endl;
            cout << message << endl;
            print("------------------------------");
            char *char_arr = &response[0];
            send(clientSocket, char_arr, bytesRecv + 1, 0);
        }
        return 1;
    }

    // Close socket
    int closeClientConnection()
    {
        close(clientSocket);
        return 1;
    }
};
