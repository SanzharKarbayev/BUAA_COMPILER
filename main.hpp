//
//  main.hpp
//  编译技术
//
//  Created by Sanzhar on 18.02.2021.
//

#ifndef main_hpp
#define main_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cctype>
#include <map>

using namespace std;

#include "lexicalAnalysis.hpp"
#include "syntaxAnalysis.hpp"

extern FILE *input_file;
extern FILE *output_file;
extern vector<char> token;
extern vector<string> inputArray;


#endif /* main_hpp */
