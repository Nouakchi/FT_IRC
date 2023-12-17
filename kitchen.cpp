// #include <iostream>
// #include <stdlib.h>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netdb.h>
// #include <arpa/inet.h>

// int main(int ac, char *av[]) {

// 	const char 	*addres;
// 	char	ipstr[INET_ADDRSTRLEN];
// 	struct addrinfo hints, *res, *p;
// 	struct sockaddr_in *ipv4;
	
//     int status;
// 	void *addr ;

//     memset(&hints, 0, sizeof(hints));
//     hints.ai_family = AF_INET; // AF_INET or AF_INET6 to force version
//     hints.ai_socktype = SOCK_STREAM;
// 	// hints.ai_flags = AI_PASSIVE;

//     status = getaddrinfo(av[1], NULL, &hints, &res);
// 	if (!res)
// 		std::cout << "dadass\n";
// 	for (p = res; p != NULL; p = p->ai_next)
// 	{
// 		ipv4 = (struct sockaddr_in *)p->ai_addr;
// 		addr = &(ipv4->sin_addr);
// 		addres = inet_ntop(p->ai_family, addr,ipstr, 100);
// 		printf("\t%s\n", ipstr);
// 	}
// 	freeaddrinfo(res);
// 	return 0;
// }
#include <iostream>
void f()
{
	std::cout << "dd";
}
int main()
{
	int f;
	f();
}