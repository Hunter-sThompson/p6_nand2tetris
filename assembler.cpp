#include <iostream>
#include <string>
using namespace std;
string assemble(string instruction) {
    string binary = "";
    if (instruction[0] == '@') { // A-instruction
        int address;
        if (isdigit(instruction[1])) {
            address = stoi(instruction.substr(1));
        } else {
            string symbol = instruction.substr(1);
            if (symbolTable.find(symbol) != symbolTable.end()) { // Symbol already in symbol table
                address = symbolTable[symbol];
            } else { // New symbol, add to symbol table
                int nextAddress = symbolTable.size();
                addSymbol(symbol, nextAddress);
                address = nextAddress;
            }
        }
        binary = "0" + decToBinary(address, 15);
    } else { // C-instruction
        string dest, comp, jump;
        size_t equalPos = instruction.find('=');
        size_t semicolonPos = instruction.find(';');
        if (equalPos == string::npos) { // No dest
            dest = "000";
            comp = instruction.substr(0, semicolonPos);
        } else if (semicolonPos == string::npos) { // No jump
            dest = instruction.substr(0, equalPos);
            comp = instruction.substr(equalPos + 1);
            jump = "000";
        } else { // Both dest and jump
            dest = instruction.substr(0, equalPos);
            comp = instruction.substr(equalPos + 1, semicolonPos - equalPos - 1);
            jump = instruction.substr(semicolonPos + 1);
        }
        binary = "111" + compTable[comp] + destTable[dest] + jumpTable[jump];
    }
    return binary;
}
