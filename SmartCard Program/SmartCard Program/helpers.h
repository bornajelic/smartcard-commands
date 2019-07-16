#pragma once
#include <string>


namespace helpers {

	std::string HexToString(unsigned char* buffer, unsigned int lenght);

	void hexToByte(std::string hex, unsigned char *val, int& lenght);
}