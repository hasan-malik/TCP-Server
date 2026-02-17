// this file is a practice file to learn the read() and write() functions,
// which will be used in our server

#include <fcntl.h> // file control. this is what contains constants like O_RDONLY
#include <unistd.h>
#include <stdio.h>


int main() {


	int fd = open("file.txt", O_RDONLY);	 
	// when you use high-level file-handling fns like fopen(), they are actually 
	// calling open() under the hood
	// open returns an int, which is the identifier of the file

	printf("fd: %d\n", fd);

	char buffer[256];
	ssize_t bytesRead = read(fd, buffer, 256);
	// read from the file whose identifier is fd.
	// read upto 256 bytes. store them in buffer.
	// we define buffer to be an array of chars because sizeof(char) = 1 byte.
	// the func returns the number of bytes that were read (which should really be 256).
	// if bytesRead == 0, then that means: the end of the file has been reached
	// if bytesRead == 1, then that means: error occurred

	printf("bytesRead: %zd\n", bytesRead);

	close(fd);

	fd = open("file.txt", O_WRONLY);

	ssize_t bytesWritten = write(fd, buffer, 4);
	printf("bytesWritten: %zd\n", bytesWritten);

	close(fd);

	return 0;
}

