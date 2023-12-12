#include "Rotor.h"

using namespace std;

extern "C" void _asmMain();

extern "C" void _printString(char* s) {
	std::cout << s;
	return;
}

extern "C" void _getString(char * buffer, int num) {
	cin.getline(buffer, num);
	return;
}

extern "C" void _newLine() {
	cout << endl;
}

extern "C" void _encrypt(char* buffer, int size) {
	string str1 = "";
	string str2 = "";
	string str3 = "";
	int aSize = size;	//delcaring this locally because it was acting evil

	for (int i = 0; i < aSize; i++)
	{
		str1 = str1 + buffer[i];
	}

	Enigma machine;
	
	cout << "Source:		" << str1 << endl;

	str2 = machine.encrpyt(str1);

	cout << "Encrypted:	" << str2 << endl;

	char* charArray = new char[aSize];s
	strcpy_s(charArray, aSize+1, str2.c_str());
	for (int i = 0; i < aSize; i++)
	{
		buffer[i] = charArray[i];
	} 
	return;
}

// main stub driver
int main() {
	_asmMain();
	return 0;
}