#include "parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

string readContents(char* file_name) {
    ifstream t(file_name);
    
    if (!t.good()) {
        cout << "parser.cpp: Error opening file" << endl;
        exit(-1);
    }
    string contents((istreambuf_iterator<char>(t)),
                     istreambuf_iterator<char>());
    return contents;
}

// Check for first occurance of ending whitespace, to second occurance (trim lines)
// Ex:      D=M  // Some comment
void trimInstruction(string &instruction) { 
    
    instruction.erase(0, instruction.find_first_not_of(" \t\n\r\f\v"));

    size_t pos = instruction.find_first_of(" \t\n\r\f\v");
        if (pos != string::npos) {
            instruction.erase(pos);
        }
}

vector<string> splitToInstructions(const string &contents) {

    vector<string> instructions;
    stringstream ss(contents);
    string instruction;
    
    while (getline(ss, instruction, '\n')) {
        if (instruction[0] == '/' || instruction.size() < 2) {
            continue;
        } else {

            trimInstruction(instruction);

            instructions.push_back(instruction);
        }
    }
    return instructions;
}
