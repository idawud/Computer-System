#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1025

int main() {
	int bytes = 0, words = 0, lines = 0;
	int fd = open("wcreport", O_RDWR | O_CREAT, 0644);

	if ( fd < 0 ) {
		perror("Result");
		exit(1);
	}

	char buffer[BUFSIZE];
	ssize_t length;
	while (((length = read(0, buffer, BUFSIZE)) > 0)  && (bytes < BUFSIZE)) {
	 	// write(1, buffer, length); 
		bytes  += length;
		
		for( char ch : buffer){
			if ( ch == ' ') {
				words += 1;
			}else if (ch == '\n'){
				// words += 1;
				lines += 1;
			}
		}
		
		std::string report = "bytes: " + std::to_string(bytes);
		report += "\nwords: " + std::to_string(words);
		report += "\nlines: " + std::to_string(lines) + "\n";
 
		write(fd, report.c_str(), std::strlen(report.c_str()));
		close(fd);
	 
	}
}
