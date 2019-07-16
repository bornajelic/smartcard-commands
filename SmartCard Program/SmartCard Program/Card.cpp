#include "card_Functionality.h"
#include "helpers.h"
/*
Constructor implementation, defining establishContext function to establish the scope within some database operations are preformed
function returnes long value, and reference to handler witch can be used by database query for management functions.
It also stores readers into a vector


NOTE: IF READER IS NOT PLUGGED IN, ASSERT ERROR WILL BE SHOWN
*/
Card::Card() {

		
		LPTSTR readers_MultiString;
		lReturn = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &this->handler);
		if (SCARD_S_SUCCESS != lReturn) {
			//make a gui popup window
			throw MyException("Failed SCardEstablishContext\n");
		}
		else {
			//get readers
			readers_MultiString = NULL; //WINDOWS multiString

			DWORD cch = SCARD_AUTOALLOCATE;

			lReturn = SCardListReaders(this->handler, NULL, (LPTSTR)&readers_MultiString, &cch);

			switch (lReturn) {

			case SCARD_E_NO_READERS_AVAILABLE:
			{
				throw MyException("No readers available!");
				break;
			}

			case SCARD_S_SUCCESS: //collect multistring
			{
				std::string tmpReader;
				LPTSTR pReader = readers_MultiString;
				while (*pReader != '\0' )
				{
					readersVector.push_back(std::string(pReader));
					pReader += strlen((LPSTR)pReader) + 1;
				} 
				lReturn = SCardFreeMemory(handler, readers_MultiString);
				if (SCARD_S_SUCCESS != lReturn) {
					throw MyException("Failed SCardFreeMemory!\n");
				}
				break;
			}

			default:
				throw MyException("READERS ERROR!");
				break;
			}

			
			
			lReturn = SCardConnectA(handler, (LPCSTR)readersVector.at(0).c_str(), SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &(this->cardHandler), &activeProtocols);
			
			if (SCARD_S_SUCCESS != lReturn)
			{
				throw MyException("Failed SCardConnect\n");
			}
			else {
				 	bufferPointer = NULL;
				    attributeLenght = SCARD_AUTOALLOCATE;

				lReturn = SCardGetAttrib(this->cardHandler,
					SCARD_ATTR_ATR_STRING,
					(LPBYTE)&bufferPointer,
					&attributeLenght);
			}
		}

		
	
	
}


//function returns ATR value
std::string Card::getATR() {
	
	if (SCARD_S_SUCCESS != lReturn) {
		if (ERROR_NOT_SUPPORTED == lReturn) {
			ATR = "ERROR!";
		}
		else {
			throw MyException("Failed ATR");
		}
	}
	else {
		ATR = helpers::HexToString(bufferPointer, attributeLenght);
		
	}
	return ATR;
}

std::string Card::getReader() {

	this->READER = readersVector.at(0);
	return READER;
}
std::string Card::getCommand(const std::string command) {
	
	BYTE sendBuffer[256] = {0};
	int bufferLenght = command.length();
	helpers::hexToByte(command, sendBuffer, bufferLenght); //bufferLenght is accepted as a reference
	
	BYTE recieveBuffer[256] = { 0 };
	DWORD SBLenght = bufferLenght;
	DWORD RBLenght = 256;

	SCARD_IO_REQUEST IORequest;
	IORequest.cbPciLength = sizeof(IORequest);
	IORequest.dwProtocol = SCARD_PROTOCOL_T1;

	
	lReturn = SCardTransmit(this->cardHandler, &IORequest, sendBuffer, SBLenght, NULL, recieveBuffer, &RBLenght);

	if (SCARD_S_SUCCESS != lReturn) {
		throw MyException("Failed SCardTransmit, getChallenge ERROR\n");
	}
	else {
		COMMAND = helpers::HexToString(recieveBuffer, RBLenght);
		return COMMAND;
	}
}