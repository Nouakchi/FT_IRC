#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "8080"

int main() {
    struct addrinfo hints, *ai, *p;

    // Get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int rv = getaddrinfo(NULL, PORT, &hints, &ai);
    if (rv != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // Loop through the results and print IP addresses
    for (p = ai; p != NULL; p = p->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];

        // Get the pointer to the address itself
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // Convert the IP address to a string
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);

        // Print the IP address
        printf("IP Address: %s\n", ipstr);
    }

    freeaddrinfo(ai);

    return 0;
}
