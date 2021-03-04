//
//  lexical analysis.cpp
//  编译技术
//
//  Created by Sanzhar on 18.02.2021.
//

#include "lexicalAnalysis.hpp"

vector<string> outputArray;

void lexicalAnalysis() {
    for (int i = 0; i < inputArray.size(); i++) {
        string str = inputArray.at(i);
        char toLowerCaseArray[str.size() + 1];
        for (int j = 0; j < str.size(); j++) {
            toLowerCaseArray[j] = tolower(str.at(j));
        }
        toLowerCaseArray[str.size()] = '\0';
        string tmp = toLowerCaseArray;
        if (tmp == "if") {
            outputArray.push_back("IFTK");
            outputArray.push_back(str);
        } else if (tmp == "do") {
            outputArray.push_back("DOTK");
            outputArray.push_back(str);
        } else if (tmp == "int") {
            outputArray.push_back("INTTK");
            outputArray.push_back(str);
        } else if(tmp == "for") {
            outputArray.push_back("FORTK");
            outputArray.push_back(str);
        } else if(tmp == "char") {
            outputArray.push_back("CHARTK");
            outputArray.push_back(str);
        } else if(tmp == "void") {
            outputArray.push_back("VOIDTK");
            outputArray.push_back(str);
        } else if (tmp == "main") {
            outputArray.push_back("MAINTK");
            outputArray.push_back(str);
        } else if (tmp == "else") {
            outputArray.push_back("ELSETK");
            outputArray.push_back(str);
        } else if (tmp == "const") {
            outputArray.push_back("CONSTTK");
            outputArray.push_back(str);
        } else if(tmp == "while") {
            outputArray.push_back("WHILETK");
            outputArray.push_back(str);
        } else if (tmp == "scanf") {
            outputArray.push_back("SCANFTK");
            outputArray.push_back(str);
        } else if (tmp == "printf") {
            outputArray.push_back("PRINTFTK");
            outputArray.push_back(str);
        } else if (tmp == "return") {
            outputArray.push_back("RETURNTK");
            outputArray.push_back(str);
        } else if (tmp == "switch") {
            outputArray.push_back("SWITCHTK");
            outputArray.push_back(str);
        } else if (tmp == "case") {
            outputArray.push_back("CASETK");
            outputArray.push_back(str);
        } else if (tmp == "default") {
            outputArray.push_back("DEFAULTTK");
            outputArray.push_back(str);
        } else if (tmp == "+") {
            outputArray.push_back("PLUS");
            outputArray.push_back(str);
        } else if (tmp == "-") {
            outputArray.push_back("MINU");
            outputArray.push_back(str);
        } else if (tmp == "*") {
            outputArray.push_back("MULT");
            outputArray.push_back(str);
        } else if (tmp == "/") {
            outputArray.push_back("DIV");
            outputArray.push_back(str);
        } else if (tmp == "<=") {
            outputArray.push_back("LEQ");
            outputArray.push_back(str);
        } else if (tmp == "<"){
            outputArray.push_back("LSS");
            outputArray.push_back(str);
        } else if (tmp == ">=") {
            outputArray.push_back("GEQ");
            outputArray.push_back(str);
        } else if (tmp == ">"){
            outputArray.push_back("GRE");
            outputArray.push_back(str);
        } else if (tmp == "==") {
            outputArray.push_back("EQL");
            outputArray.push_back(str);
        } else if (tmp == "="){
            outputArray.push_back("ASSIGN");
            outputArray.push_back(str);
        } else if (tmp == "!=") {
            outputArray.push_back("NEQ");
            outputArray.push_back(str);
        } else if (tmp == ";") {
            outputArray.push_back("SEMICN");
            outputArray.push_back(str);
        } else if (tmp == ":") {
            outputArray.push_back("COLON");
            outputArray.push_back(str);
        } else if (tmp == ",") {
            outputArray.push_back("COMMA");
            outputArray.push_back(str);
        } else if (tmp == "(") {
            outputArray.push_back("LPARENT");
            outputArray.push_back(str);
        } else if (tmp == ")") {
            outputArray.push_back("RPARENT");
            outputArray.push_back(str);
        } else if (tmp == "[") {
            outputArray.push_back("LBRACK");
            outputArray.push_back(str);
        } else if (tmp == "]") {
            outputArray.push_back("RBRACK");
            outputArray.push_back(str);
        } else if (tmp == "{") {
            outputArray.push_back("LBRACE");
            outputArray.push_back(str);
        } else if (tmp == "}") {
            outputArray.push_back("RBRACE");
            outputArray.push_back(str);
        } else if (tmp == "'") {
            i++;
            outputArray.push_back("CHARCON");
            outputArray.push_back(inputArray.at(i));
            i++;
        } else if (tmp == "\"") {
            i++;
            outputArray.push_back("STRCON");
            outputArray.push_back(inputArray.at(i));
            i++;
        } else if (isdigit(tmp.at(0))) {
            outputArray.push_back("INTCON");
            outputArray.push_back(tmp);
        }
        else {
            outputArray.push_back("IDENFR");
            outputArray.push_back(str);
        }
    }
}
