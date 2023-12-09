#include "Rotor.h"

void Enigma::incrementRotor() {
	rotors[0].increment();
	for (int i = 0; i < 3; i++)
	{
		if (rotors[i].getRotorIndex() == rotors[i].getNotchIndex() && i < 2)
			rotors[i + 1].increment();
	}
}

void Enigma::initRotors() {
	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 25; i++) {
			switch (j)
			{
			case 0:
				rotors[0].setRotorIndex(normalAlphabet[i], firstRotorArray[i]);
			case 1:
				rotors[1].setRotorIndex(normalAlphabet[i], secondRotorArray[i]);
			case 2:
				rotors[2].setRotorIndex(normalAlphabet[i], thirdRotorArray[i]);
			}
		}
}