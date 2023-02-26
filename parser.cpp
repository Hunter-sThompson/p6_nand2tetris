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

vector<string> splitToInstructions(const string &contents) {

    vector<string> instructions;
    stringstream ss(contents);
    string instruction;
    
    while (getline(ss, instruction, '\n')) {
        if (instruction[0] == '/' || instruction.size() < 2) {
            continue;
        } else {

            // Looks for first whitespace in instruction to avoid pushing comments to assembler
            // Ex: D=M  // Some comment
            // Goal is to exclude the comment
            size_t end_of_inst;
            for (int i = 0; i < instruction.size(); i++) {
                if (isspace(instruction[i])) {
                    end_of_inst = static_cast<size_t>(i);
                }
            }

            string cut_instruction = instruction.substr(0, end_of_inst);
            cout << "Parser.cpp: Cut Instruction: " << cut_instruction << endl;
            instructions.push_back(cut_instruction);
        }
    }

    return instructions;
}
