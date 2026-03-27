#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
  int clientsocket;
    struct sockaddr_in serveraddr;
    char request[100], from[50], to[50], mail[100];
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0)
    { perror("Socket creation failed");
        return 1;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2525);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    if (connect(clientsocket,
        (struct sockaddr *)&serveraddr,
        sizeof(serveraddr)) < 0)
    { perror("Connection failed");
        return 1;
    }
    printf("From: ");
    fgets(from, sizeof(from), stdin);
    printf("To: ");
    fgets(to, sizeof(to), stdin);
    printf("Mail: ");
    fgets(mail, sizeof(mail), stdin);
    strcpy(request, "SMTP REQUEST");
   send(clientsocket, request, sizeof(request), 0);
    recv(clientsocket, request, sizeof(request), 0);
    printf("Server: %s\n", request);
    sprintf(request, "MAIL FROM: %s", from);
   send(clientsocket, request, sizeof(request), 0);
    recv(clientsocket, request, sizeof(request), 0);
    sprintf(request, "RCPT TO: %s", to);
    send(clientsocket, request, sizeof(request), 0);
    recv(clientsocket, request, sizeof(request), 0);
    strcpy(request, "DATA");
    send(clientsocket, request, sizeof(request), 0);
    recv(clientsocket, request, sizeof(request), 0);
    send(clientsocket, mail, sizeof(mail), 0);
    recv(clientsocket, request, sizeof(request), 0);
    strcpy(request, "QUIT");
    send(clientsocket, request, sizeof(request), 0);
    recv(clientsocket, request, sizeof(request), 0);
    printf("Server: %s\n", request);
    printf("Client shutting down.\n");
    close(clientsocket);
    return 0;
}
