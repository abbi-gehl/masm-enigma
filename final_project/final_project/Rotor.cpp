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

void Rotor::setRotorIndex(char index, char value) {
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

// Class function definitions for Enigma - Written by Harrison Blair
// Initializes the forwards and backwards rotors for each one in the Enigma machine
void Enigma::initRotors() {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 26; i++)
		{
			switch (j)
			{
			case 0:
				rotors[j].setRotorIndex(normalAlphabet[i], firstRotorArray[i]);
				rotors[j].setReverseRotorIndex(firstRotorArray[i], normalAlphabet[i]);
				rotors[j].setNotchIndex(17);
				break;
			case 1:
				rotors[j].setRotorIndex(normalAlphabet[i], secondRotorArray[i]);
				rotors[j].setReverseRotorIndex(secondRotorArray[i], normalAlphabet[i]);
				rotors[j].setNotchIndex(6); 
				break;
			case 2:
				rotors[j].setRotorIndex(normalAlphabet[i], thirdRotorArray[i]);
				rotors[j].setReverseRotorIndex(thirdRotorArray[i], normalAlphabet[i]);
				rotors[j].setNotchIndex(-1); // Doesn't have a notch, since it is the last rotor
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
