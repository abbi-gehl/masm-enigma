#include <iostream>
using namespace std;
#include <bitset>
#include <string>
template<> struct hash<char>;

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


// main stub driver
int main() {
	_asmMain();
	return 0;
}