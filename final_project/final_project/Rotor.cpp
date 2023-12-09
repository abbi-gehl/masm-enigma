#include "Rotor.h"

void Rotor::increment() {
	if (rotorIndex < 25) {
		rotorIndex++;
	}
	else {
		rotorIndex = 0;
	}
}

int Rotor::getRotorIndex() {
	return rotorIndex;
}

void Rotor::setRotorIndex(char index, char value) {
	rotor[index] = value;
	return;
}

int Rotor::getNotchIndex() {
	return notchMinecraft;
}

void Rotor::setNotchIndex(int notch) {
	notchMinecraft = notch;
}