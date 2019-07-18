#include "helpers.h"



std::string helpers::HexToString(unsigned char *buffer, unsigned int lenght) {

	std::string tmp;
	char hex[256] = { 0 };
	char *pHex = hex;

	for (unsigned int i = 0; i < lenght; i++, pHex+=2) {
		sprintf(pHex, "%0.2x", *(buffer + i));
	}

	tmp = hex;
	return tmp;
}

void helpers::hexToByte(std::string hex, unsigned char *val, int& lenght) { //BYTE unsigned char
	std::string hexArray = "0123456789ABCDEF";
	

	for (int i = 0; i < hex.length()/2; ++i) {
		val[i] = hexArray.find(hex[i*2]) << 4;
		val[i] |= hexArray.find(hex[i * 2 + 1]);
	}
	lenght = hex.length() / 2;
	return;
}

