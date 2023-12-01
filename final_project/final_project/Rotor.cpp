#include "Rotor.h"

extern "C" void _initRotors() {
	for (int i = 0; i < 26; i++)
	{
		firstRotor[normalAlphabet[i]] = firstRotorArray[i];
	}
}