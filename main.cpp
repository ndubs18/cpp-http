#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

const std::string FILE_PATH = "./messages.txt"; 
const size_t CHUNK_WIDTH = 8;
const int CHUNK_WIDTH_INT = static_cast<int>(CHUNK_WIDTH);

int hasNewline(const char* str);
void parseNewlineChunk(const char* chunk, std::string& line, size_t len);

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
	
	std::string message = {};
	char chunk[CHUNK_WIDTH + 1] {};

	while (stream.read(chunk, CHUNK_WIDTH)) {
		chunk[CHUNK_WIDTH] = '\0';
		parseNewlineChunk(chunk, message, CHUNK_WIDTH)	;
	}

	int gc = stream.gcount();

	if (gc) {	
		chunk[gc] = '\0';
		parseNewlineChunk(chunk, message, gc);
	} else {
		message.append(chunk, gc);
	}
	
	stream.close();
	return 0;
}

void parseNewlineChunk(const char* chunk, std::string& message, size_t len) {
	int nl = hasNewline(chunk);

	if (nl>=0) {
		message.append(chunk, nl+1);	
		std::cout << message;
		message.clear();
		
		if (nl+1 < static_cast<int>(len)) {
			message.append(chunk+nl+1, len-(nl+1));
		}
	} else {
		message.append(chunk, len);
	}
}

int hasNewline(const char* str) {
	for(int i=0; i<CHUNK_WIDTH_INT; ++i) {
		if (str[i] == '\n') {
			return i;
		}
	}
	return -1;
}

