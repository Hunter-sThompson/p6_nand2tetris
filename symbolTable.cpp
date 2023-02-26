#include "symbolTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

void initSymbolTable() {
	symbolTable["SP"] = 0;
    symbolTable["LCL"] = 1;
    symbolTable["ARG"] = 2;
    symbolTable["THIS"] = 3;
    symbolTable["THAT"] = 4;
    symbolTable["SCREEN"] = 16384;
    symbolTable["KBD"] = 24576;
    for (int i = 0; i <= 15; i++) {
        string symbol = "R" + to_string(i);
        symbolTable[symbol] = i;
    }
}

void addSymbol(string symbol, int address) {
	symbolTable[symbol] = address;
}

string decToBinary(int dec, int len) {
    string binary = "";
    while (dec > 0) {
        binary = to_string(dec % 2) + binary;
        dec /= 2;
    }
    int zerosToAdd = len - binary.length();
    while (zerosToAdd--) {
        binary = "0" + binary;
    }
    return binary;
}
