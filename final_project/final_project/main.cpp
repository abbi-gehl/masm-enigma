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

extern "C" void _getString(char * buffer, int num) {
	cin.getline(buffer, num);
	return;
}

extern "C" void _newLine() {
	cout << endl;
}

// main stub driver
int main() {
	_asmMain();
	return 0;
}