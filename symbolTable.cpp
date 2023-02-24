#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, int> symbol_table;

unordered_map<string, string> compTable = {
    {"0", "0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"M", "1110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"!M", "1110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"-M", "1110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"M+1", "1110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"M-1", "1110010"},
    {"D+A", "0000010"},
    {"D+M", "1000010"},
    {"D-A", "0010011"},
    {"D-M", "1010011"},
    {"A-D", "0000111"},
    {"M-D", "1000111"},
    {"D&A", "0000000"},
    {"D&M", "1000000"},
    {"D|A", "0010101"},
    {"D|M", "1010101"}
};

unordered_map<string, string> destTable = {
    {"", "000"},
    {"M", "001"},
    {"D", "010"},
    {"MD", "011"},
    {"A", "100"},
    {"AM", "101"},
    {"AD", "110"},
    {"AMD", "111"}
};

unordered_map<string, string> jumpTable = {
    {"", "000"},
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"}
};

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

