#include "Rotor.h"

// Class function definitions for Rotor - Written by Harrison Blair
int Rotor::increment() {
	if (rotorIndex < 25) {
		rotorIndex++;
	}
	else {
		rotorIndex = 0;
	}
	return rotorIndex;
}

int Rotor::getRotorIndex() {
	return rotorIndex;
}

void Rotor::setRotorIndex(int index) {
	rotorIndex = index;
	return;
}

void Rotor::setRotorMap(char index, char value) {
	rotor[index] = value;
	return;
}

void Rotor::setReverseRotorIndex(char index, char value) {
	rotorReverse[index] = value;
	return;
}

int Rotor::getNotchIndex() {
	return notchMinecraft;
}

void Rotor::setNotchIndex(int notch) {
	notchMinecraft = notch;
}

map<char, char> Rotor::getRotor() {
	return rotor;
}

map<char, char> Rotor::getRotorReverse() {
	return rotorReverse;
}

char Rotor::encrypt(char text, int offset) {
	char output = text;
	int index;
	std::map<char, char>::iterator it;

	if (offset != -1)
	{
		index = int(text) - 65 - offset;
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = rotor.begin();
		advance(it, index);
		output = it->first;
	}
	it = rotor.find(output);
	// Rotor
	for (int j = 0; j < rotorIndex; j++) {
		if (next(it) == rotor.end()) {
			it = rotor.begin();
		}
		else {
			advance(it, 1);
		}
	}
	output = it->second;

	return output;
}

char Rotor::secondEncrypt(char text, int offset) {
	char output = text;
	std::map<char, char>::iterator it;

	int index = int(output) - 65 - offset;	
	if (index < 0) {
		index = 26 - abs(index);
	}
	it = rotorReverse.begin();
	advance(it, index);
	output = it->first;
	it = rotorReverse.find(output);
	for (int j = 0; j < rotorIndex; j++) {
		if (next(it) == rotorReverse.end()) {
			it = rotorReverse.begin();
		}
		else {
			advance(it, 1);
		}
	}
	output = it->second;

	return output;
}

// Class function definitions for Enigma - Written by Harrison Blair
// Initializes the forwards and backwards rotors for each one in the Enigma machine
Enigma::Enigma() {
	initRotors();
}

void Enigma::initRotors() {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 26; i++)
		{
			switch (j)
			{
			case 0:
				rotors[j].setRotorMap(normalAlphabet[i], firstRotorArray[i]);
				rotors[j].setReverseRotorIndex(firstRotorArray[i], normalAlphabet[i]);
				rotors[j].setNotchIndex(17);
				rotors[j].setRotorIndex(0); // Programmer defined pos for the first rotor
				break;
			case 1:
				rotors[j].setRotorMap(normalAlphabet[i], secondRotorArray[i]);
				rotors[j].setReverseRotorIndex(secondRotorArray[i], normalAlphabet[i]);
				rotors[j].setNotchIndex(6);
				rotors[j].setRotorIndex(0); // Programmer defined pos for the second rotor
				break;
			case 2:
				rotors[j].setRotorMap(normalAlphabet[i], thirdRotorArray[i]);
				rotors[j].setReverseRotorIndex(thirdRotorArray[i], normalAlphabet[i]);
				rotors[j].setNotchIndex(-1); // Doesn't have a notch, since it is the last rotor
				rotors[j].setRotorIndex(0); // Programmer defined pos for the third rotor
				break;
			default:
				break;
			}
		}
	}

	for (int i = 0; i < 26; i++)
	{
		reflector[normalAlphabet[i]] = reflectorArray[i];
	}
	return;
}

void Enigma::incrementRotors() {
	int temp = rotors[0].increment();
	if (temp == rotors[0].getNotchIndex())
		temp = rotors[1].increment();
	else
		return;
	if (temp == rotors[1].getNotchIndex())
		rotors[2].increment(); //Don't need to save the value here, since there isnt a notch on rotor 3
	return;
}

string Enigma::encrpyt(string word) { // Code originally created by Abbi, modified for use with the classes by Harrison
	string encrypted = "";
	initRotors();

	for (int i = 0; i < word.length(); i++) {
		char charDst = word[i];
		incrementRotors();

		charDst = rotors[0].encrypt(charDst, -1);
		charDst = rotors[1].encrypt(charDst, rotors[0].getRotorIndex());
		charDst = rotors[2].encrypt(charDst, rotors[1].getRotorIndex());

		// Reflector
		int index = int(charDst) - 65 - rotors[2].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		std::map<char, char>::iterator it = reflector.begin();
		advance(it, index);
		charDst = it->first;
		charDst = reflector.find(charDst)->second;

		charDst = rotors[2].secondEncrypt(charDst, 0);
		charDst = rotors[1].secondEncrypt(charDst, rotors[2].getRotorIndex());
		charDst = rotors[0].secondEncrypt(charDst, rotors[1].getRotorIndex());

		index = int(charDst) - 65 - rotors[0].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		charDst = normalAlphabet[index];

		encrypted += charDst;
	}

	return encrypted;
}