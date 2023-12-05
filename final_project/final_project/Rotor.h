#pragma once
#include <map>

class Rotor {
	public:
		//Functions
		void incremeantIndex();
		void initRotor();
		void _getRotorValue(char * index);
	private:
		//Member Data
		std::map<char, char> rotorValue;
		int rotorIndex = 0;
};

char normalAlphabet[26] =	{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char firstRotorArray[26] =	{'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'};
