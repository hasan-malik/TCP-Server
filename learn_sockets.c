#include <sys/socket.h>
// #include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h> // this contains read() and write()


int main() {

	// CREATE A SOCKET

	int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	// first param is: domain. AF_INET6 (import <sys/socket.h>)
	// second param is: type. SOCK_STREAM, or the other option is SOCK_DGRM (import <sys/socket.h>)
	// third param is: protocol. 0 means: default of your default
	// returns a file descriptor (or -1 in case of an error)

	if (sockfd == -1) {
		perror("Socket creation did not work.\n");
		return 1;
	}

	printf("Socket created. fd: %d\n", sockfd);

	// BIND

	// bind connects my socket to an IP address and a port number

	// i used AF_INET6 i.e. IPv6, so I should use: struct sockaddr_in6
	struct sockaddr_in6 my_server_address;
	// this struct has three important attributes:
	my_server_address.sin6_family = AF_INET6; // what kind of IP address are you using? IPv6
	my_server_address.sin6_port = htons(5000); // what port are you using? Port 5000.
	// the htons function, i.e. the host-to-network-short function, is what we always wrap the port number in.
	my_server_address.sin6_addr = in6addr_any; // what IP address are you using? Any IP addresss. 
	// The constant in6addr_any is defined in <netinet/in.h>
	// Now, this means: every single IP address of my laptop is now connected to this port.

	// sin6 stands for: sockaddr internet version 6


	int b = bind(sockfd,
	 (struct sockaddr *) &my_server_address, // type casting
	 sizeof(my_server_address));

	// bind only returns 0 (all good) or -1 (error occurred).

	if (b == -1) {
		perror("Bind failed.\n");
		return 1;
	}

	// LISTEN

	int listening = listen(sockfd, 3);
	// the second argument: the number of pending requests that can wait at a time
	// returns 0 for success, -1 for error

	if (listening == -1) {
		perror("Listen failed.\n");
		return 1;
	}

	// ACCEPT

	struct sockaddr_in6 my_client_address;

	while (1) {

		int clientfd = accept(sockfd, 
		(struct sockaddr *) &my_client_address, // type casting, just like bind
		sizeof(my_client_address)
		);

		// returns a file descriptor for the client socket (or -1 in case of an error)

		if (clientfd == -1) {
			// perror("Accept failed.\n");
			// return 1;
			continue; // go to the next loop iteration
		}

		// Now, we learnt read() and write() in learn_io.c. Let's use that knowledge.

		char buffer[128];

		while (1) { // as long as the program is running
			ssize_t bytesRead = read(clientfd, buffer, 128);

			if (bytesRead == -1) { // error
				perror("Client reading failed.\n");
				break;
			}

			if (bytesRead == 0) { // this means that the client closed the connection. this isn't an error: it's normal.
				printf("The client closed the connection.");
				break; // terminate the loop
			}

			write(clientfd, buffer, bytesRead);
			// Note: we read from clientfd, and we write to clientfd.
			// clientfd represents the client we are connected to.

		}

		close(clientfd);
	}


	return 0;
}
