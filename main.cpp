#include<fstream>
#include<iostream>

const std::string FILE_PATH = "./messages.txt"; 
	const size_t CHUNK_WIDTH = 8;

int main(int argc, char** argv) {
	std::ifstream stream {std::ifstream(FILE_PATH)};

	//If we couldn't open the file	
	if(!stream.is_open()) {
		std::cout << "File " << FILE_PATH << " could not be opened\n";
		return 1;
	}

	//If there is no text in the file
	if (stream.peek() == EOF) {
		std::cout << "No text in the file\n";
		return 0;
	};

	char chunk[CHUNK_WIDTH + 1] {};

	while (stream.read(chunk, CHUNK_WIDTH)) {
		std::cout << stream.gcount() << " ";
		chunk[CHUNK_WIDTH] = '\0';
		std::cout << "read: " << chunk << "\n";
	}

	if (stream.gcount()) {	
		chunk[stream.gcount()] = '\0';
		std::cout << "read: " << chunk << "\n";

	}

	stream.close();
	return 0;
}
