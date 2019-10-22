#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

using namespace std;
int main() {
	int bytes = 0, words = 0, lines = 0;
	int fd = open("wcreport", O_RDWR | O_CREAT, 0644);

	if ( fd < 0 ) {
		perror("Result");
		exit(1);
	}
	
	string content, sentence;
	do{
		cout << ">>> ";
		getline(cin, sentence);
		if( !sentence.empty()){	
			content += sentence + "\n";
			++lines;
		}
	}while( !sentence.empty());
		
	std::string report = "bytes: " + std::to_string(content.length());
	report += "\nlines: " + std::to_string(lines);
	
	for( auto ch : content){
		if( ch == ' ' || ch == '\n'){
			++words;
		}
	}	
 	
	report += "\nwords: " + std::to_string(words) + "\n";

	write(fd, report.c_str(), std::strlen(report.c_str()));
	close(fd); 
}
