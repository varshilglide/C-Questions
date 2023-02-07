#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<string>
#include<sys/time.h>
#define TRUE 1

using namespace std;

int main(int argc, char *argv[])
{
    int clientsocket[30];
    int PORT;
    int max_clients = 30;
    int sd;
    int activity;
    int newSocket;
    int valread;
    int i;
    int addrlen;
    int opt = TRUE;

    fd_set readfds;
    char buffer[8192];
    char *message = "You have connected to server !! You can receive messages now !!\n";
    cin >> PORT;

    for(int i = 0; i<max_clients; i++)
    {
        clientsocket[i] = 0;
    }

}


int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
if(serverSocket == -1)
{
    cerr << "Could not create a socket !" << endl;
}
if(setsockopt(serverSocket, SQL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
{
    cerr << "setsockopt"<< endl;
    exit(EXIT_FAILURE);
}
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(PORT);
inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);

if(bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) < 0)
{
    cerr << "Bind Failed" << endl;
    exit(EXIT_FAILURE);
}

if(listen(serverSocket, 3) == 0)
{
    cout << "[+]Server is ready for clients to connect on port number" << PORT << endl;
}
addrlen = sizeof(addr);
while(TRUE)
{
    //clear the socket set
    FD_ZERO(&readfds);

    //add master socket to set
    FD_SET(serverSocket, &readfds);
    max_sd = serverSocket;

    //add child sockets to set
    for(i = 0; i<max_clients; i++)
    {
        sd = clientSocket[i];
    }

    //if valid socket descriptor then add to read list
    if(sd>0)
    {
        FD_SET(sd, &readfds);
    }

    //highest file descrtiptor number, need it for the select function
    if(sd>max_sd)
    {
        max_sd = sd;
    }
}

activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
if((activity < 0) && (errno!=EINTR))
{
    cout << "select error" << endl;
}
if(FD_ISSET(serverSocket, &readfds))
{
    if((newSocket = accept(serverSocket, (struct sockaddr*)&addr, (socklen_t*)&addrlen)) < 0)
    {
        cerr << "Accept" << endl;
    }

    cout << "New Connection, socket fd : " << newSocket << "Ip is : " << inet_ntoa(addr.sin_addr) << "Port : " << ntons(addr.sin_port) << endl;
    
    if(send(newSocket, message, strlen(message) , 0) != strlen(message))
    {
        cerr << "Send Error";
    }
    for(i = 0; i<max_clients; i++)
    {
        if(clientSocket[i] == 0)
        {
            clientSocket[i] = newSocket;
            break;
        }
    }
}

for(i = 0; i<max_clients; i++)
{
    sd = clientSocket[i];
    if(FD_ISSET(sd, &readfds))
    {
        memset(buffer, 0 , 8192);
        int bytesReceived = recv(sd, buffer, 8192, 0);
        if(bytesReceieved == -1)
        {
            cerr << "Error in recv(). Quitting " << endl;
            break;
        }
        if(bytesRecieved == 0)
        {
            close(sd);
            clientSocket[i] = 0;
            cout << "Client disconnected " << endl;
            break;
        }
        else
        {
            if(bytesReceived > 0)
            {
                cout << "Client [ " << "]:" << string(buffer, 0, bytesRecieved) << endl;
            }
            for(i=0; i<max_clients; i++)
            {
                sd=clientSocket[i];
                if(sd!=0)
                {
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }
    return 0;
}



