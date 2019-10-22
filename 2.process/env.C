#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if ( argc != 2 ) {
		std::cout << "Usage Error: [progName] [color]" <<std::endl;
		exit(1);
	}
	int ret = setenv("COLOR", argv[1], 1);
	if ( ret == 0){
		std::cout << "COLOR set successful" << std::endl;
	}
	
	std::cout << "The current env COLOR is: " << getenv("COLOR") << std::endl;
}
