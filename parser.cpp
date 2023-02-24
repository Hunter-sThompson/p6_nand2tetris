#include "parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

string readContents(char* file_name) {
    ifstream t(file_name);
    string contents((istreambuf_iterator<char>(t)),
                     istreambuf_iterator<char>());
    return contents;
}

vector<string> splitToInstructions(const string &contents) {

    vector<string> instructions;
    stringstream ss(contents);
    string instruction;
    
    // I presume this getline is interfering with isspace?
    // Since white space gets to the vector, although i check it.
    while (getline(ss, instruction, '\n')) {
        if (instruction[0] == '/' || isspace(instruction[0])) {
            continue;
        } else {
            instructions.push_back(instruction);
        }
    }

    return instructions;
}
