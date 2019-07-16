#pragma once

#ifndef CARD_FUNCTIONALITY_H
#define CARD_FUNCTIONALITY_H



#include <Windows.h>
#include <winscard.h>
#include <iostream>
#include <iostream>
#include <vector>
#include <string>




class MyException : public std::exception {

protected: 

	std::string message;

public:

	//constructor for C string
	explicit MyException(const char* message)
		:message(message) 
		{}
	
	//constructor for std::string
	explicit MyException(const std::string &message)
		:message(message) {}

	//returns pointer on error description

	virtual const char* what() const throw() {
		return message.c_str();
	}

	
};


class Card {
	
private:

	

	SCARDCONTEXT handler; //unsigned long pointer
	LONG		 lReturn; //32bit signed integer
	SCARDHANDLE  cardHandler; 
	LPBYTE 		 bufferPointer;
	DWORD		 attributeLenght;
	DWORD		 activeProtocols;


	/*
	First information sended by the card to the reader.
	It's a simple row of parameter, in which the card is telling the reader, how to communicate with it.
		*/
	 std::string ATR; 


	//contains error message from myException
	static const std::string errorMessage;


	/*
	CARD provides a random number(challenge) for use in security related procedure
	*/
	std::string CHALLENGE;


	///*
	//UID is a alphanumeric string that is associated with a single entity within a given system. (system = multiple cards in vicinity of field)
	//UID makes it possible to address that entity, so that can be accesed and interacted with
	//typical sizes 4,7 or 10byte UID
	//UID is used to uniquely adress each card during anti collision. Since there is no anti collision with contact cards(there is only one connected to the reader) there
	//is no nedd for UID in contact cards
	//*/
	//static const std::string UID;


	///*
	//AID identifies an application in a smartCard.
	//*/
	//static const std::string AID;


	/*
	generic command
	*/
	std::string COMMAND;

	/*
	stores the name of the reader
	*/
	std::string READER;


public:


	//constructor
	Card();

	std::vector<std::string> readersVector; //contains a vector of readers plugged in PC

	std::string getATR(); //function returnes card ATR value

	/*
	function request a string type command in hex, command gets converted to BYTE
	*/
	std::string getCommand(const std::string); 

	std::string getReader();
};
#endif

