#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <map>

using namespace std;

extern "C" void _asmMain();

extern "C" void _printString(char* s) {
	std::cout << s;
	return;
}

extern "C" string _getString() {
	string s;
	cin >> s;
	return s;
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

extern "C" void _readFile(char* buffer,int mode) {
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
	_asmMain();
	return 0;
}