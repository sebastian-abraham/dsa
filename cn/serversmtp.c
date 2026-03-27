#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{   int serversocket, clientsocket;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    char request[100], from[50], to[50], mail[100];
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0)
    {  perror("Socket creation failed");
        return 1;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2525);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(serversocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {  perror("Bind failed");
        return 1;
    }
    if (listen(serversocket, 5) < 0)
    {   perror("Listen failed");
        return 1;
    }
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddr, &len);

    if (clientsocket < 0)
    {  perror("Accept failed");
        return 1;
    }
 recv(clientsocket, request, sizeof(request), 0);
    printf("Client: %s\n", request);
    send(clientsocket, "220 SERVICE READY", 18, 0);

 recv(clientsocket, request, sizeof(request), 0);
    strcpy(from, request);
    send(clientsocket, "250 OK", 6, 0);

 recv(clientsocket, request, sizeof(request), 0);
    strcpy(to, request);
    send(clientsocket, "250 OK", 6, 0);

 recv(clientsocket, request, sizeof(request), 0);
    send(clientsocket, "354 Start mail input", 21, 0);

    recv(clientsocket, mail, sizeof(mail), 0);

 printf("Email from: %s\nEmail to:   %s\nMessage: %s\n",  from, to, mail);

    send(clientsocket, "250 Message received", 21, 0);

 recv(clientsocket, request, sizeof(request), 0);
   send(clientsocket, "221 Service closing", 20, 0);
    printf("Server shutting down\n");
    close(clientsocket);
    close(serversocket);
    return 0;
