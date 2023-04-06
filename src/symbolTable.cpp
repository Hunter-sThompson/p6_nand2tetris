#include "symbolTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

template<typename K, typename V>
void print_map(unordered_map<K, V> const &m)
{
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
}
void newSymbolHandler(int &address, string &symbol) {
    if (symbolTable.find(symbol) != symbolTable.end()) {
        address = symbolTable[symbol];
	//cout << "Symbol found: " << symbol << " at address " << address << endl;
        return;
    } else {
        int nextAddress = symbolTable.size();
	//cout << "Symbol added: " << symbol << " to address " << nextAddress << endl;
        addSymbol(symbol, nextAddress);
        address = nextAddress;
        return;
    }
    cout << "newSymbleHandler error" << endl;
    exit(-1);
}

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
