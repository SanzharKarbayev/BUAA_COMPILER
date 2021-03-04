//
//  main.cpp
//  编译技术
//
//  Created by Sanzhar on 18.02.2021.
//

#include "main.hpp"

// /Users/sanzhar/XcodeProjects/Beihang/Compiler/CompilerProject/CompilerProject/Testfiles
FILE *inputFile = fopen("/Users/sanzhar/XcodeProjects/Beihang/Compiler/CompilerProject/CompilerProject/Testfiles/testfile.txt", "r");
FILE *outputFile = fopen("/Users/sanzhar/XcodeProjects/Beihang/Compiler/CompilerProject/CompilerProject/Testfiles/output.txt", "w");

vector<char> token;
vector<string> inputArray;

void pushToInputArray() {
    char tmpCharArray[token.size()];
    for (int i = 0; i < token.size(); i++) {
        tmpCharArray[i] = token.at(i);
    }
    tmpCharArray[token.size()] = '\0';
    string tmpString = tmpCharArray;
    inputArray.push_back(tmpString);
    token.clear();
}

void retract (int n) {
    fseek(inputFile, n, SEEK_CUR);
}

void inputProcess() {
    if (inputFile == 0) {
        perror("fopen");
        exit(1);
    }
    
    char ch;
    
    do {
        ch = fgetc(inputFile);
        if (isspace(ch)) {
            continue;
        }
        
        if (isdigit(ch)) {
            while (isdigit(ch)) {
                token.push_back(ch);
                ch = fgetc(inputFile);
            }
            retract(-1);
            pushToInputArray();
        }
        else if (isalpha(ch) || ch == '_') {
            while (isalpha(ch) || isdigit(ch) || ch == '_') {
                token.push_back(ch);
                ch = fgetc(inputFile);
            }
            retract(-1);
            pushToInputArray();
        }
        else if (ch == '+') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '-') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '*') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '/') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '<') {
            ch = fgetc(inputFile);
            if (ch == '=') {
                token.push_back('<');
            } else {
                retract(-1);
                ch = '<';
            }
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '>') {
            ch = fgetc(inputFile);
            if (ch == '=') {
                token.push_back('>');
            } else {
                retract(-1);
                ch = '>';
            }
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '=') {
            ch = fgetc(inputFile);
            if (ch == '=') {
                token.push_back('=');
            } else {
                retract(-1);
                ch = '=';
            }
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '!') {
            ch = fgetc(inputFile);
            if (ch == '=') {
                token.push_back('!');
            } else {
                retract(-1);
                ch = '!';
            }
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == ';') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == ':') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == ',') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '(') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == ')') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '[') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == ']') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '{') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '}') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '\'') {
            token.push_back(ch);
            pushToInputArray();
        }
        else if (ch == '\"') {
            token.push_back(ch);
            pushToInputArray();
            while ((ch = fgetc(inputFile)) != '\"') {
                token.push_back(ch);
            }
            pushToInputArray();
            token.push_back(ch);
            pushToInputArray();
        }
        
    } while (ch != EOF);
    fclose(inputFile);
}

void outputProcess() {
    for (int i = 0; i < answerVector.size(); i++) {
        fprintf(outputFile, "%s\n", answerVector.at(i).c_str());
    }
}

int main() {
    inputProcess();
    lexicalAnalysis();
    program();
    outputProcess();
    fclose(outputFile);
}
