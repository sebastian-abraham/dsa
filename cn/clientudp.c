#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
int main() 
{
    int sockfd;
    char buffer[1024] = {0};
    char *hello = "Hello from UDP client";
    struct sockaddr_in serv_addr;
    socklen_t addr_len;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    addr_len = sizeof(serv_addr);

    // Send message to server
    sendto(sockfd, hello, strlen(hello), 0,
           (struct sockaddr *)&serv_addr, addr_len);
    printf("Hello message sent\n");

    // Receive response from server
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&serv_addr, &addr_len);
    printf("%s\n", buffer);
    close(sockfd);
    return 0;
}
