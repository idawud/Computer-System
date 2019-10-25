#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> 

using namespace std;
int main() {
	int words = 0, lines = 0;

	int fd;

	// first check if wcreports directory already exits
	struct stat buffer;
	if ( (stat("wcreports", &buffer) != -1) && (S_ISDIR(buffer.st_mode)) ){
		fd = open("wcreports/wcreport", O_RDWR | O_CREAT, 0644);
	}
	else{ // create one
		if ( mkdir("wcreports", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == 0){
			fd = open("wcreports/wcreport", O_RDWR | O_CREAT, 0644);
		}
		else{
			cerr << "Error :  wcreports directory not created" << endl; 
			exit(-1);
		}
	}
		

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

	for( auto ch : content){
		if( ch == ' ' || ch == '\n'){ ++words; }
	}

	std::string report = "bytes: " + std::to_string(content.length());
	report += "\nwords: " + std::to_string(words);
	report += "\nlines: " + std::to_string(lines); 

	write(fd, report.c_str(), std::strlen(report.c_str()));
	close(fd); 
}
