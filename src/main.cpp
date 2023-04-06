#include "parser.h"
#include "symbolTable.h"
#include "assembler.h"
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

void writeFile(string contents, char* file_name) {
    ofstream out(file_name);
    out << contents;  
    out.close();
}

int main(int argc, char *argv[]) {
    
    string opaque_blob;

    if (!input_handler(argc, argv)) {
        cout << "Runtime Error" << endl;
        exit(-1);
    }
    cout << "Input Valid" << endl;

    string contents = readContents(argv[1]);
    vector<string> instructions = splitToInstructions(contents);

    initSymbolTable();
    
    opaque_blob = assemble(instructions[0]);
    for (int i = 1; i < instructions.size(); i++) {
        cout << i << ". Assembling instruction: " << instructions[i] << endl;
        cout << "Assmbled Instruction: " << assemble(instructions[i]) << endl;
        opaque_blob = opaque_blob + "\n" + assemble(instructions[i]);
    }

    writeFile(opaque_blob, argv[3]);
    
    cout << argv[1] << " successfully assembled to machine code to file " << argv[3] << endl;
    return 0;
}
