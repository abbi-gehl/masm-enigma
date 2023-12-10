#pragma once
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char normalAlphabet[26] =		{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
const char firstRotorArray[26] =	{ 'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J' };
const char secondRotorArray[26] =	{ 'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E' };
const char thirdRotorArray[26] =	{ 'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O' };
const char reflectorArray[26] =		{ 'Y','R','U','H','Q','S','L','D','P','X','N','G','O','K','M','I','E','B','F','Z','C','W','V','J','A','T' };

class Rotor {
public:

	int increment();

	int getRotorIndex();
	void setRotorIndex(int index);

	void setRotorMap(char index, char value);

	void setReverseRotorIndex(char index, char value);

	map<char, char> getRotor();
	map<char, char> getRotorReverse();

	int getNotchIndex();
	void setNotchIndex(int notch);

	char encrypt(char text, int offset);
	char secondEncrypt(char text, int offset);

private:
	std::map<char, char> rotor{ };
	std::map<char, char> rotorReverse{ };
	int rotorIndex = 0;
	int notchMinecraft = 0;
};

class Enigma {
public:
	Enigma();

	void initRotors();
	void incrementRotors();

	string encrpyt(string word);

private:
	Rotor rotors[3];
	std::map<char, char> reflector{ };
};

