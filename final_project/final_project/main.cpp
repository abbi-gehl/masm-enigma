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

// main stub driver
int main() {
	string str1 = "THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
	string str2 = "";
	string str3 = "";
	Enigma machine;

	cout << "Source:" << str1 << endl;

	str2 = machine.encrpyt(str1);

	cout << "Encrypted:" << str2 << endl;

	str3 = machine.encrpyt(str2);

	cout << "Decrypted:" << str3 << endl;

	_asmMain();
	return 0;
}