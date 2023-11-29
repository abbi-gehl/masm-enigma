#include <iostream>
#include <string>
#include <fstream>
#include <string>


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

extern "C" string _readFile(int mode) {
	ifstream file;
	string output = "";
	string line;

	if (mode == 0) {
		file.open("input.txt", ios::in);
	}
	if (mode != 0) {
		file.open("output.txt", ios::in);
	}

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
		}
	}
	file.close();
	return line;
}

// main stub driver
int main() {
	_asmMain();
	return 0;
}