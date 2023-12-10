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
		char charSrc = word[i];
		it = rotors[0].getRotor().find(charSrc);
		incrementRotors();

		// First Rotor
		for (int j = 0; j < rotors[0].getRotorIndex(); j++) {
			if (next(it) == rotors[0].getRotor().end()) {
				it = rotors[0].getRotor().begin();
			}
			else {
				advance(it, 1);
			}
		}
		char charDst = it->second;

		// Second Rotor
		int index = int(charDst) - 65 - rotors[0].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = rotors[1].getRotor().begin();
		advance(it, index);
		charDst = it->first;
		it = rotors[1].getRotor().find(charDst);
		for (int j = 0; j < rotors[1].getRotorIndex(); j++) {
			if (next(it) == rotors[1].getRotor().end()) {
				it = rotors[1].getRotor().begin();
			}
			else {
				advance(it, 1);
			}
		}
		charDst = it->second;

		// Third Rotor
		index = int(charDst) - 65 - rotors[1].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = rotors[2].getRotor().begin();
		advance(it, index);
		charDst = it->first;
		it = rotors[2].getRotor().find(charDst);
		for (int j = 0; j < rotors[2].getRotorIndex(); j++) {
			if (next(it) == rotors[2].getRotor().end()) {
				it = rotors[2].getRotor().begin();
			}
			else {
				advance(it, 1);
			}
		}
		charDst = it->second;

		// Reflector
		index = int(charDst) - 65 - rotors[2].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = reflector.begin();
		advance(it, index);
		charDst = it->first;
		charDst = reflector.find(charDst)->second;

		// Thrid Rotor Reverse
		index = int(charDst) - 65;
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = rotors[2].getRotorReverse().begin();
		advance(it, index);
		charDst = it->first;
		it = rotors[2].getRotorReverse().find(charDst);
		for (int j = 0; j < rotors[2].getRotorIndex(); j++) {
			if (next(it) == rotors[2].getRotorReverse().end()) {
				it = rotors[2].getRotorReverse().begin();
			}
			else {
				advance(it, 1);
			}
		}
		charDst = it->second;

		// Second Rotor Reverse
		index = int(charDst) - 65 - rotors[2].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = rotors[1].getRotorReverse().begin();
		advance(it, index);
		charDst = it->first;
		it = rotors[1].getRotorReverse().find(charDst);
		for (int j = 0; j < rotors[1].getRotorIndex(); j++) {
			if (next(it) == rotors[1].getRotorReverse().end()) {
				it = rotors[1].getRotorReverse().begin();
			}
			else {
				advance(it, 1);
			}
		}
		charDst = it->second;

		// First Rotor Reverse
		index = int(charDst) - 65 - rotors[1].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		it = rotors[0].getRotorReverse().begin();
		advance(it, index);
		charDst = it->first;
		it = rotors[0].getRotorReverse().find(charDst);
		for (int j = 0; j < rotors[0].getRotorIndex(); j++) {
			if (next(it) == rotors[0].getRotorReverse().end()) {
				it = rotors[0].getRotorReverse().begin();
			}
			else {
				advance(it, 1);
			}
		}
		charDst = it->second;

		index = int(charDst) - 65 - rotors[0].getRotorIndex();
		if (index < 0) {
			index = 26 - abs(index);
		}
		
		charDst = normalAlphabet[index];

		encrypted += charDst;
	}

	return encrypted;
}