#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>

std::string readContents(char* file_name);

std::vector<std::string> splitToInstructions(const std::string &contents);

#endif
