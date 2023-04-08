#include "parser.h"
#include "symbolTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
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

    int line_number = 0; 
    while (getline(ss, instruction, '\n')) {
        // || instruction.find('(') != string::npos
        trimInstruction(instruction);
        if (instruction[0] == '/' || instruction.size() < 2) {
	    cout << instruction << " ------------ ERROR" << endl;
            continue;
        } else if (instruction.find('(') != string::npos) {
            string label = instruction.substr(1, instruction.size() - 2);
            addSymbol(label, line_number);
            cout << "Label: " << label << " at " << line_number << endl;
            continue;
        } else {
            instructions.push_back(instruction);
            line_number++;
        }
    }
    return instructions;
}
