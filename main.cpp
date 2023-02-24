#include "parser.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

bool input_handler(int argc, char* argv[]) {

    if (argc < 1 || argc > 4) {
        cout << "Usage: ./main.exe input.asm -o output.hack" << endl;
        exit(-1);
    }

    if (strcmp(argv[2], "-o") != 0) {
        cout << "Usage: ./main.exe input.asm -o output.hack" << endl;
        cout << argv[2] << endl;
        exit(-1);
    }

    string file_name = argv[1];
    size_t file_name_len = file_name.length(); 

    if (file_name.empty() || file_name_len <= 4) {
        cout << "Filename Invalid: " << argv[1] << endl;
        exit(-1);
    }

    string file_ext = file_name.substr (file_name_len - 4, file_name_len);

    if (file_ext != ".asm") {
        cout << "File Extension Invalid (Must be .asm): " << file_ext  << endl; 
        exit(-1);
    }

    string output_file_name = argv[3];
    size_t output_file_name_len = output_file_name.length();

 
    if (output_file_name.empty() || output_file_name_len <= 5) {
        cout << "Output Filename Invalid: " << argv[3] << endl;
        exit(-1);
    }

    string output_file_ext = output_file_name.substr (output_file_name_len - 5, output_file_name_len);

    if (output_file_ext != ".hack") {
        cout << "Output File Extension Invalid (Must be .hack): " << output_file_ext  << endl; 
        exit(-1);
    }    
    
    return true;
}

int main(int argc, char *argv[]) {
    
    if (!input_handler(argc, argv)) {
        cout << "Runtime Error" << endl;
        exit(-1);
    }
    cout << "Input Valid" << endl;

    string contents = readContents(argv[1]);

    vector<string> instructions = splitToInstructions(contents);
    
    cout << "The number of instructions is: " << instructions.size() << endl;
    for (int i = 0; i < instructions.size(); i++) {
        cout << "Instruction " << i << ": " << instructions[i];
        if (isspace(instructions[i][0])) { cout << "Theres a space!" << endl; }
        cout << '\n';
    }

    cout << "Done" << endl;
    return 0;
}
