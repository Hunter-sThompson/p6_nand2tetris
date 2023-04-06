#include "assembler.h"
#include "symbolTable.h"
#include <iostream>
#include <string>
using namespace std;

template<typename K, typename V>
void print_map(unordered_map<K, V> const &m)
{
    cout << "printing Map" << endl;
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
}
string assemble(string instruction) {
    string binary = "";
    // A Instruction
    if (instruction[0] == '@') { 
        int address;
        if (isdigit(instruction[1])) {
            address = stoi(instruction.substr(1));
        } else {
            string symbol = instruction.substr(1);
            
            newSymbolHandler(address, symbol);
        }
        binary = "0" + decToBinary(address, 15);

    // C-instruction
    } else { 
        string dest, comp, jump;
        size_t equalPos = instruction.find('=');
        size_t semicolonPos = instruction.find(';');
        if (equalPos != string::npos) { 
            dest = instruction.substr(0, equalPos);
            comp = instruction.substr(equalPos + 1);
            jump = "000";
            //dest = "000";
            //comp = instruction.substr(0, semicolonPos);
            //jump = instruction.substr(semicolonPos + 1);
        } else if (semicolonPos != string::npos) { 
            dest = "000";
            comp = instruction.substr(0, semicolonPos);
            jump = instruction.substr(semicolonPos + 1);
            //dest = instruction.substr(0, equalPos);
            //comp = instruction.substr(equalPos + 1);
            //jump = "000";
        } else { 
            dest = instruction.substr(0, equalPos);
            comp = instruction.substr(equalPos + 1, semicolonPos - equalPos - 1);
            jump = instruction.substr(semicolonPos + 1);
        }
        binary = "111" + compTable[comp] + destTable[dest] + jumpTable[jump];
        cout << "C inst, Dest: " << dest << " Comp: " << comp << " Jump: " << jump << endl;
    }
    return binary;
}
