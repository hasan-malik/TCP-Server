#include <sys/socket.h>

int main() {

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

	return 0;
}