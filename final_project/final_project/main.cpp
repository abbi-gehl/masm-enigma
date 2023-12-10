#include "Rotor.h"

using namespace std;

extern "C" void _asmMain();

extern "C" void _printString(char* s) {
	std::cout << s;
	return;
}

extern "C" void _getString(char * buffer, int bufferSize) {
	string s;
	cin >> s;
	strcpy_s(buffer, bufferSize, s.c_str());
	return;
}

/*File I/O by Abbi Gehlbach */
extern "C" void _writeFile(string input, int mode) {
	ofstream file;

	if (mode == 0) {
		file.open("input.txt", ios::out);
	}

	if (mode != 0) {
		file.open("output.txt", ios::out);
	}

	file << input;

	file.close();

}

extern "C" void _readFile(int mode, char * buffer, int bufferSize) {
	string line;
	ifstream file;
	const char* charArr = {};

	if (mode == 0) {
		file.open("input.txt", ios::in);
	}
	if (mode != 0) {
		file.open("output.txt", ios::in);
	}

	if (file.is_open()) {
		while (!file.eof()) {
			file >> buffer;
		}
	}

	strcpy_s(buffer, bufferSize, line.c_str());
	file.close();
	return;
}

// Harrison B - Clears file depending on the mode of use (input or output)
extern "C" void _clearFile(int mode) {
	ofstream file;

	if (mode == 0) {
		file.open("input.txt", ios::trunc);
	}
	if (mode != 0) {
		file.open("output.txt", ios::trunc);
	}

	if (file.is_open()) {
		if (file.good())
		{
			cout << "\nFile Cleared!\n";
		}
		else
		{
			cout << "\nFile Unable to be cleared!\n";
		}
	}
	else
	{
		cout << "\nFile Unable to be cleared!\n";
	}
	file.close();
	return;
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