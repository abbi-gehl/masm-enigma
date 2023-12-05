#include "Rotor.h"

void Rotor::incremeantIndex()
{
	rotorIndex++;
}

void Rotor::initRotor()
{
	for (int i = 0; i < 26; i++)
	{
		rotorValue[normalAlphabet[i]] = firstRotorArray[i];
	}
}