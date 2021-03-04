//
//  syntax analysis.cpp
//  编译技术
//
//  Created by Sanzhar on 18.02.2021.
//

#include "syntaxAnalysis.hpp"

int i = 0;
map<string, string> functionMap;
vector<string> answerVector;

void pushToAnswerVector() {
    string str = outputArray.at(i++).c_str();
    str += " ";
    str += outputArray.at(i++).c_str();
    answerVector.push_back(str);
}

void popFromAnswerVector() {
    answerVector.pop_back();
    i -= 2;
}

void pushAnswer(string answer) {
    answerVector.push_back(answer);
}

//＜字符串＞   ::=  "｛y十进制编码为32,33,35-126的ASCII字符｝"
void charString() {
    if (outputArray.at(i) == "STRCON") {
        pushToAnswerVector();
        pushAnswer("<字符串>");
    }
}

//＜程序＞   ::=  ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
void program() {
    if (outputArray.at(i) == "CONSTTK") {
        constantDescription();
    }
    if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
            //        i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) != "LPARENT") {
//                i -= 4;
                popFromAnswerVector();
                popFromAnswerVector();
                variableDescription();
            } else {
//                i -= 4;
                popFromAnswerVector();
                popFromAnswerVector();
            }
        }
    }
    while (outputArray.at(i) == "CHARTK" || outputArray.at(i) == "INTTK" || outputArray.at(i) == "VOIDTK") {
        if (outputArray.at(i) == "CHARTK" || outputArray.at(i) == "INTTK") {
            functionDefinitionWithReturn();
        }
        if (outputArray.at(i) == "VOIDTK") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "MAINTK") {
//                i -= 2;
                popFromAnswerVector();
                mainFunction();
                break;
            }
            else {
//                i -= 2;
                popFromAnswerVector();
                functionDefinitionWithoutReturn();
            }
        }
    }
    pushAnswer("<程序>");
}

//＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
void constantDescription() {
    if (outputArray.at(i) == "CONSTTK") {
//        i += 2;
        pushToAnswerVector();
        constantDefinition();
//        i += 2;
        pushToAnswerVector();
        while (outputArray.at(i) == "CONSTTK") {
//            i += 2;
            pushToAnswerVector();
            constantDefinition();
//            i += 2;
            pushToAnswerVector();
        }
//        outputArray.insert(outputArray.begin() + i, "<常量说明>");
//        i++;
        pushAnswer("<常量说明>");
    }
}

//＜常量定义＞   ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
//                | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
void constantDefinition() {
    if (outputArray.at(i) == "INTTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "ASSIGN") {
//                i += 2;
                pushToAnswerVector();
                integer();
                while (outputArray.at(i) == "COMMA") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "IDENFR") {
//                        i += 2;
                        pushToAnswerVector();
                        if (outputArray.at(i) == "ASSIGN") {
//                            i += 2;
                            pushToAnswerVector();
                            integer();
                        }
                    }
                }
//                    outputArray.insert(outputArray.begin() + i, "<常量定义>");
//                    i++;
                pushAnswer("<常量定义>");
//                } else {
//                    outputArray.insert(outputArray.begin() + i, "<常量定义>");
//                    i++;
//                }
            }
        }
    }
    else if (outputArray.at(i) == "CHARTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "ASSIGN") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "CHARCON") {
//                    i += 2;
                    pushToAnswerVector();
                    while (outputArray.at(i) == "COMMA") {
                        pushToAnswerVector();
                        if (outputArray.at(i) == "IDENFR") {
//                            i += 2;
                            pushToAnswerVector();
                            if (outputArray.at(i) == "ASSIGN") {
//                                i += 2;
                                pushToAnswerVector();
                                if (outputArray.at(i) == "CHARCON") {
//                                    i += 2;
                                    pushToAnswerVector();
                                }
                            }
                        }
                    }
//                    outputArray.insert(outputArray.begin() + i, "<常量定义>");
//                    i++;
                    pushAnswer("<常量定义>");
                }
            }
        }
    }
}

//＜无符号整数＞  ::= ＜数字＞｛＜数字＞｝
void unsignedInteger() {
//    outputArray.insert(outputArray.begin() + i, "<无符号整数>");
//    i++;
    pushAnswer("<无符号整数>");
}

//＜整数＞ ::= ［＋｜－］＜无符号整数＞
void integer() {
    if (outputArray.at(i) == "PLUS" || outputArray.at(i) == "MINU") {
//        i += 2;
        pushToAnswerVector();
    }
//    i += 2;
    pushToAnswerVector();
    unsignedInteger();
//    outputArray.insert(outputArray.begin() + i, "<整数>");
//    i++;
    pushAnswer("<整数>");
}

//＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
void variableDescription() {
    if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
        variableDefinition();
        if (outputArray.at(i) == "SEMICN") {
//            i += 2;
            pushToAnswerVector();
            while (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "IDENFR") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "LPARENT") {
//                        i -= 4;
                        popFromAnswerVector();
                        popFromAnswerVector();
                        break;
                    }
                    else {
//                        i -= 4;
                        popFromAnswerVector();
                        popFromAnswerVector();
                        variableDefinition();
                        if (outputArray.at(i) == "SEMICN") {
//                            i += 2;
                            pushToAnswerVector();
                        }
                    }
                }
            }
//            outputArray.insert(outputArray.begin() + i, "<变量说明>");
//            i++;
            pushAnswer("<变量说明>");
        }
    }
}

//＜变量定义＞ ::= ＜变量定义无初始化＞|＜变量定义及初始化＞
void variableDefinition() {
    variableDefinitionWithInit();
//    outputArray.insert(outputArray.begin() + i, "<变量定义>");
//    i++;
    pushAnswer("<变量定义>");
}
        
/*＜变量定义及初始化＞  ::=
 ＜类型标识符＞＜标识符＞=＜常量＞
|＜类型标识符＞＜标识符＞'['＜无符号整数＞']'='{'＜常量＞{,＜常量＞}'}'
|＜类型标识符＞＜标识符＞'['＜无符号整数＞']''['＜无符号整数＞']'='{''{'＜常量＞{,＜常量＞}'}'{, '{'＜常量＞{,＜常量＞}'}'}'}'*/
void variableDefinitionWithInit() {
    if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "ASSIGN") {
//                i += 2;
                pushToAnswerVector();
                constant();
//                outputArray.insert(outputArray.begin() + i, "<变量定义及初始化>");
//                i++;
                pushAnswer("<变量定义及初始化>");
            }
            else if (outputArray.at(i) == "LBRACK") {
//                i += 4;
                pushToAnswerVector();
                pushToAnswerVector();
                unsignedInteger();
                if (outputArray.at(i) == "RBRACK") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "ASSIGN") {
//                        i += 2;
                        pushToAnswerVector();
                        if (outputArray.at(i) == "LBRACE") {
//                            i += 2;
                            pushToAnswerVector();
                            constant();
                            while (outputArray.at(i) == "COMMA") {
//                                i += 2;
                                pushToAnswerVector();
                                constant();
                            }
                            if (outputArray.at(i) == "RBRACE") {
//                                i += 2;
                                pushToAnswerVector();
//                                outputArray.insert(outputArray.begin() + i, "<变量定义及初始化>");
//                                i++;
                                pushAnswer("<变量定义及初始化>");
                            }
                        }
                    }
                    else if (outputArray.at(i) == "LBRACK") {
//                        i += 4;
                        pushToAnswerVector();
                        pushToAnswerVector();
                        unsignedInteger();
                        if (outputArray.at(i) == "RBRACK") {
//                            i += 2;
                            pushToAnswerVector();
                            if (outputArray.at(i) == "ASSIGN") {
//                                i += 2;
                                pushToAnswerVector();
                                if (outputArray.at(i) == "LBRACE") {
//                                    i += 2;
                                    pushToAnswerVector();
                                    while (outputArray.at(i) == "LBRACE") {
//                                        i += 2;
                                        pushToAnswerVector();
                                        constant();
                                        while (outputArray.at(i) == "COMMA") {
//                                            i += 2;
                                            pushToAnswerVector();
                                            constant();
                                        }
                                        if (outputArray.at(i) == "RBRACE") {
//                                            i += 2;
                                            pushToAnswerVector();
                                            if (outputArray.at(i) == "COMMA") {
//                                                i += 2;
                                                pushToAnswerVector();
                                                continue;
                                            }
                                            else if (outputArray.at(i) == "RBRACE") {
//                                                i += 2;
                                                pushToAnswerVector();
//                                                outputArray.insert(outputArray.begin() + i, "<变量定义及初始化>");
//                                                i++;
                                                pushAnswer("<变量定义及初始化>");
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                variableDefinitionWithoutInit();
                            }
                        }
                    }
                    else {
                        variableDefinitionWithoutInit();
                    }
                }
            }
            else {
                variableDefinitionWithoutInit();
            }
        }
    }
}

//＜常量＞   ::=  ＜整数＞|＜字符＞
void constant() {
    if (outputArray.at(i) == "INTCON" || outputArray.at(i) == "PLUS" || outputArray.at(i) == "MINU") {
        integer();
//        outputArray.insert(outputArray.begin() + i, "<常量>");
//        i++;
        pushAnswer("<常量>");
    }
    else {
//        i += 2;
        pushToAnswerVector();
//        outputArray.insert(outputArray.begin() + i, "<常量>");
//        i++;
        pushAnswer("<常量>");
    }
}

/*＜变量定义无初始化＞::=＜类型标识符＞(
 ＜标识符＞|
 ＜标识符＞'['＜无符号整数＞']'
 |＜标识符＞'['＜无符号整数＞']''['＜无符号整数＞']')
 {,(＜标识符＞
 |＜标识符＞'['＜无符号整数＞']'
 |＜标识符＞'['＜无符号整数＞']''['＜无符号整数＞']' )}*/
void variableDefinitionWithoutInit() {
    while (outputArray.at(i) == "COMMA") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "LBRACK") {
//                i += 4;
                pushToAnswerVector();
                pushToAnswerVector();
                unsignedInteger();
                if (outputArray.at(i) == "RBRACK") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "LBRACK") {
//                        i += 4;
                        pushToAnswerVector();
                        pushToAnswerVector();
                        unsignedInteger();
                        if (outputArray.at(i) == "RBRACK") {
//                            i += 2;
                            pushToAnswerVector();
                        }
                    }
                }
            }
        }
    }
//    outputArray.insert(outputArray.begin() + i, "<变量定义无初始化>");
//    i++;
    pushAnswer("<变量定义无初始化>");
}

//＜有返回值函数定义＞  ::=  ＜声明头部＞'('＜参数表＞')' '{'＜复合语句＞'}'
void functionDefinitionWithReturn() {
    declarationHeader();
    if (outputArray.at(i) == "LPARENT") {
//        i += 2;
        pushToAnswerVector();
        parameterList();
        if (outputArray.at(i) == "RPARENT") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "LBRACE") {
//                i += 2;
                pushToAnswerVector();
                compoundSentence();
                if (outputArray.at(i) == "RBRACE") {
//                    i += 2;
                    pushToAnswerVector();
//                    outputArray.insert(outputArray.begin() + i, "<有返回值函数定义>");
//                    i++;
                    pushAnswer("<有返回值函数定义>");
                }
            }
        }
    }
}

//＜声明头部＞   ::=  int＜标识符＞ |char＜标识符＞
void declarationHeader() {
    if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
            string functionName = outputArray.at(i + 1).c_str();
            string functionType = "returnType";
            functionMap.insert(make_pair(functionName, functionType));
//            i += 2;
            pushToAnswerVector();
//            outputArray.insert(outputArray.begin() + i, "<声明头部>");
//            i++;
            pushAnswer("<声明头部>");
        }
    }
}

//＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
void parameterList() {
    if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
//            i += 2;
            pushToAnswerVector();
            while (outputArray.at(i) == "COMMA") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "IDENFR") {
//                        i += 2;
                        pushToAnswerVector();
                    }
                }
            }
//            outputArray.insert(outputArray.begin() + i, "<参数表>");
//            i++;
            pushAnswer("<参数表>");
        }
    }
    else {
//        outputArray.insert(outputArray.begin() + i, "<参数表>");
//        i++;
        pushAnswer("<参数表>");
    }
}

//＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
void compoundSentence() {
    if (outputArray.at(i) == "CONSTTK") {
        constantDescription();
    }
    if (outputArray.at(i) == "INTTK" || outputArray.at(i) == "CHARTK") {
        variableDescription();
    }
    sentenceList();
//    outputArray.insert(outputArray.begin() + i, "<复合语句>");
//    i++;
    pushAnswer("<复合语句>");
}

//＜语句列＞   ::= ｛＜语句＞｝
void sentenceList() {
    while (outputArray.at(i) != "RBRACE") {
        statement();
    }
//    outputArray.insert(outputArray.begin() + i, "<语句列>");
//    i++;
    pushAnswer("<语句列>");
}

//＜语句＞    ::= ＜循环语句＞｜＜条件语句＞| ＜有返回值函数调用语句＞;  |＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜情况语句＞｜＜空＞;|＜返回语句＞; | '{'＜语句列＞'}'
void statement() {
    if (outputArray.at(i) == "WHILETK" || outputArray.at(i) == "FORTK") {
        loopStatement();
    }
    else if (outputArray.at(i) == "IFTK") {
        conditionalStatement();
    }
    else if (outputArray.at(i) == "IDENFR") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i -= 2;
            popFromAnswerVector();
            functionCall();
        }
        else {
//            i -= 2;
            popFromAnswerVector();
            assignmentStatement();
        }
        if (outputArray.at(i) == "SEMICN") {
//            i += 2;
            pushToAnswerVector();
//            outputArray.insert(outputArray.begin() + i, "");
//            i++;
        }
    }
    else if (outputArray.at(i) == "SCANFTK") {
        readingSentence();
        if (outputArray.at(i) == "SEMICN") {
//            i += 2;
            pushToAnswerVector();
        }
    }
    else if (outputArray.at(i) == "PRINTFTK") {
        writeSentence();
        if (outputArray.at(i) == "SEMICN") {
//            i += 2;
            pushToAnswerVector();
        }
    }
    else if (outputArray.at(i) == "SWITCHTK") {
        situationStatement();
    }
    else if (outputArray.at(i) == "SEMICN") {
//        i += 2;
        pushToAnswerVector();
    }
    else if (outputArray.at(i) == "RETURNTK"){
        returnStatement();
        if (outputArray.at(i) == "SEMICN") {
//            i += 2;
            pushToAnswerVector();
        }
    }
    else if (outputArray.at(i) == "LBRACE") {
//        i += 2;
        pushToAnswerVector();
        sentenceList();
        if (outputArray.at(i) == "RBRACE") {
//            i += 2;
            pushToAnswerVector();
        }
    }
//    outputArray.insert(outputArray.begin() + i, "<语句>");
//    i++;
    pushAnswer("<语句>");
}

//＜循环语句＞   ::=  while '('＜条件＞')'＜语句＞| for'('＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞')'＜语句＞
void loopStatement() {
    if (outputArray.at(i) == "WHILETK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            condition();
            if (outputArray.at(i) == "RPARENT") {
//                i += 2;
                pushToAnswerVector();
                statement();
//                outputArray.insert(outputArray.begin() + i, "<循环语句>");
//                i++;
                pushAnswer("<循环语句>");
            }
        }
    }
    else if (outputArray.at(i) == "FORTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "IDENFR") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "ASSIGN") {
//                    i += 2;
                    pushToAnswerVector();
                    expression();
                    if (outputArray.at(i) == "SEMICN") {
//                        i += 2;
                        pushToAnswerVector();
                        condition();
                        if (outputArray.at(i) == "SEMICN") {
//                            i += 2;
                            pushToAnswerVector();
                            if (outputArray.at(i) == "IDENFR") {
//                                i += 2;
                                pushToAnswerVector();
                                if (outputArray.at(i) == "ASSIGN") {
//                                    i += 2;
                                    pushToAnswerVector();
                                    if (outputArray.at(i) == "IDENFR") {
//                                        i += 2;
                                        pushToAnswerVector();
                                        if (outputArray.at(i) == "PLUS" || outputArray.at(i) == "MINU") {
//                                            i += 2;
                                            pushToAnswerVector();
                                            pushToAnswerVector();
                                            stepSize();
                                            if (outputArray.at(i) == "RPARENT") {
//                                                i += 2;
                                                pushToAnswerVector();
                                                statement();
//                                                outputArray.insert(outputArray.begin() + i, "<循环语句>");
//                                                i++;
                                                pushAnswer("<循环语句>");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞
void condition() {
    expression();
    if (outputArray.at(i) == "LSS" || outputArray.at(i) == "LEQ" || outputArray.at(i) == "GRE" || outputArray.at(i) == "GEQ" || outputArray.at(i) == "EQL" || outputArray.at(i) == "NEQ") {
//        i += 2;
        pushToAnswerVector();
        expression();
//        outputArray.insert(outputArray.begin() + i, "<条件>");
//        i++;
        pushAnswer("<条件>");
    }
}

//＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
void expression() {
    if (outputArray.at(i) == "PLUS" || outputArray.at(i) == "MINU") {
//        i += 2;
        pushToAnswerVector();
    }
    term();
    while (outputArray.at(i) == "PLUS" || outputArray.at(i) == "MINU") {
//        i += 2;
        pushToAnswerVector();
        term();
    }
//    outputArray.insert(outputArray.begin() + i, "<表达式>");
//    i++;
    pushAnswer("<表达式>");
}

//＜项＞     ::= ＜因子＞{＜乘法运算符＞＜因子＞}
void term() {
    factor();
    while (outputArray.at(i) == "MULT" || outputArray.at(i) == "DIV") {
//        i += 2;
        pushToAnswerVector();
        factor();
    }
//    outputArray.insert(outputArray.begin() + i, "<项>");
//    i++;
    pushAnswer("<项>");
}

//＜因子＞::=＜标识符＞｜＜标识符＞'['＜表达式＞']'｜＜标识符＞'['＜表达式＞']''['＜表达式＞']'｜'('＜表达式＞')'｜＜整数＞｜＜字符＞｜＜有返回值函数调用语句＞
void factor() {
    if (outputArray.at(i) == "IDENFR") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LBRACK") {
//            i += 2;
            pushToAnswerVector();
            expression();
            if (outputArray.at(i) == "RBRACK") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "LBRACK") {
//                    i += 2;
                    pushToAnswerVector();
                    expression();
                    if (outputArray.at(i) == "RBRACK") {
//                        i += 2;
                        pushToAnswerVector();
//                        outputArray.insert(outputArray.begin() + i, "<因子>");
//                        i++;
                        pushAnswer("<因子>");
                    }
                }
                else {
//                    outputArray.insert(outputArray.begin() + i, "<因子>");
//                    i++;
                    pushAnswer("<因子>");
                }
            }
        }
        else if (outputArray.at(i) == "LPARENT") {
//            i -= 2;
            popFromAnswerVector();
            functionCall();
//            outputArray.insert(outputArray.begin() + i, "<因子>");
//            i++;
            pushAnswer("<因子>");
        }
        else {
//            outputArray.insert(outputArray.begin() + i, "<因子>");
//            i++;
            pushAnswer("<因子>");
        }
    }
    else if (outputArray.at(i) == "LPARENT") {
//        i += 2;
        pushToAnswerVector();
        expression();
        if (outputArray.at(i) == "RPARENT") {
            pushToAnswerVector();
//            outputArray.insert(outputArray.begin() + i, "<因子>");
//            i++;
            pushAnswer("<因子>");
        }
    }
    else if (outputArray.at(i) == "INTCON" || outputArray.at(i) == "PLUS" || outputArray.at(i) == "MINU") {
        integer();
//        outputArray.insert(outputArray.begin() + i, "<因子>");
//        i++;
        pushAnswer("<因子>");
    }
    else if (outputArray.at(i) == "CHARCON") {
//        i += 2;
        pushToAnswerVector();
//        outputArray.insert(outputArray.begin() + i, "<因子>");
//        i++;
        pushAnswer("<因子>");
    }
}

//＜有返回值函数调用语句＞ ::= ＜标识符＞'('＜值参数表＞')' 和 ＜无返回值函数调用语句＞ ::= ＜标识符＞'('＜值参数表＞')'
void functionCall() {
    if (outputArray.at(i) == "IDENFR") {
        string functionName = outputArray.at(i + 1).c_str();
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "RPARENT") {
//                outputArray.insert(outputArray.begin() + i, "<值参数表>");
//                i++;
                pushAnswer("<值参数表>");
            }
            else {
                valueParameterTable();
            }
            if (outputArray.at(i) == "RPARENT") {
                map <string, string> :: iterator funcType;
                funcType = functionMap.find(functionName);
//                i += 2;
                pushToAnswerVector();
                if (funcType->second == "returnType") {
//                    outputArray.insert(outputArray.begin() + i, "<有返回值函数调用语句>");
//                    i++;
                    pushAnswer("<有返回值函数调用语句>");
                } else if (funcType->second == "voidType") {
//                    outputArray.insert(outputArray.begin() + i, "<无返回值函数调用语句");
//                    i++;
                    pushAnswer("<无返回值函数调用语句>");
                }
            }
        }
    }
}

//＜条件语句＞  ::= if '('＜条件＞')'＜语句＞［else＜语句＞］
void conditionalStatement() {
    if (outputArray.at(i) == "IFTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            condition();
            if (outputArray.at(i) == "RPARENT") {
//                i += 2;
                pushToAnswerVector();
                statement();
                if (outputArray.at(i) == "ELSETK") {
//                    i += 2;
                    pushToAnswerVector();
                    statement();
                }
//                outputArray.insert(outputArray.begin() + i, "<条件语句>");
//                i++;
                pushAnswer("<条件语句>");
            }
        }
    }
}

//＜赋值语句＞   ::=  ＜标识符＞＝＜表达式＞|＜标识符＞'['＜表达式＞']'=＜表达式＞|＜标识符＞'['＜表达式＞']''['＜表达式＞']' =＜表达式＞
void assignmentStatement() {
    if (outputArray.at(i) == "IDENFR") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "ASSIGN") {
//            i += 2;
            pushToAnswerVector();
            expression();
        }
        else if (outputArray.at(i) == "LBRACK") {
//            i += 2;
            pushToAnswerVector();
            expression();
            if (outputArray.at(i) == "RBRACK") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "ASSIGN") {
//                    i += 2;
                    pushToAnswerVector();
                    expression();
                }
                else if (outputArray.at(i) == "LBRACK") {
//                    i += 2;
                    pushToAnswerVector();
                    expression();
                    if (outputArray.at(i) == "RBRACK") {
                        pushToAnswerVector();
                        if (outputArray.at(i) == "ASSIGN") {
    //                        i += 2;
                            pushToAnswerVector();
                            expression();
                        }
                    }
                }
            }
        }
//        outputArray.insert(outputArray.begin() + i, "<赋值语句>");
//        i++;
        pushAnswer("<赋值语句>");
    }
}

//＜读语句＞    ::=  scanf '('＜标识符＞')'
void readingSentence() {
    if (outputArray.at(i) == "SCANFTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "IDENFR") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "RPARENT") {
//                    i += 2;
                    pushToAnswerVector();
//                    outputArray.insert(outputArray.begin() + i, "<读语句>");
//                    i++;
                    pushAnswer("<读语句>");
                }
            }
        }
    }
}

//＜写语句＞    ::= printf '(' ＜字符串＞,＜表达式＞ ')'| printf '('＜字符串＞ ')'| printf '('＜表达式＞')'
void writeSentence() {
    if (outputArray.at(i) == "PRINTFTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "STRCON") {
                charString();
                if (outputArray.at(i) == "COMMA") {
//                    i += 2;
                    pushToAnswerVector();
                    expression();
                }
                if (outputArray.at(i) == "RPARENT") {
//                    i += 2;
                    pushToAnswerVector();
//                    outputArray.insert(outputArray.begin() + i, "<写语句>");
//                    i++;
                    pushAnswer("<写语句>");
                }
            }
            else {
                expression();
                if (outputArray.at(i) == "RPARENT") {
//                    i += 2;
                    pushToAnswerVector();
//                    outputArray.insert(outputArray.begin() + i, "<写语句>");
//                    i++;
                    pushAnswer("<写语句>");
                }
            }
        }
    }
}

//＜情况语句＞  ::=  switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞＜缺省＞‘}’
void situationStatement() {
    if (outputArray.at(i) == "SWITCHTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            expression();
            if (outputArray.at(i) == "RPARENT") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "LBRACE") {
//                    i += 2;
                    pushToAnswerVector();
                    caseTable();
                    defaultStatement();
                    if (outputArray.at(i) == "RBRACE") {
//                        i += 2;
                        pushToAnswerVector();
//                        outputArray.insert(outputArray.begin() + i, "<情况语句>");
//                        i++;
                        pushAnswer("<情况语句>");
                    }
                }
            }
        }
    }
}

//＜情况表＞   ::=  ＜情况子语句＞{＜情况子语句＞}
void caseTable() {
    caseClause();
    while (outputArray.at(i) == "CASETK") {
        caseClause();
    }
//    outputArray.insert(outputArray.begin() + i, "<情况表>");
//    i++;
    pushAnswer("<情况表>");
}

//＜情况子语句＞  ::=  case＜常量＞：＜语句＞
void caseClause() {
    if (outputArray.at(i) == "CASETK") {
//        i += 2;
        pushToAnswerVector();
        constant();
        if (outputArray.at(i) == "COLON") {
//            i += 2;
            pushToAnswerVector();
            statement();
//            outputArray.insert(outputArray.begin() + i, "<情况子语句>");
//            i++;
            pushAnswer("<情况子语句>");
        }
    }
}

//＜缺省＞   ::=  default :＜语句＞
void defaultStatement() {
    if (outputArray.at(i) == "DEFAULTTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "COLON") {
//            i += 2;
            pushToAnswerVector();
            statement();
        }
    }
//    outputArray.insert(outputArray.begin() + i, "<缺省>");
//    i++;
    pushAnswer("<缺省>");
}

//＜返回语句＞   ::=  return['('＜表达式＞')']
void returnStatement() {
    if (outputArray.at(i) == "RETURNTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "LPARENT") {
//            i += 2;
            pushToAnswerVector();
            expression();
            if (outputArray.at(i) == "RPARENT") {
//                i += 2;
                pushToAnswerVector();
//                outputArray.insert(outputArray.begin() + i, "<返回语句>");
//                i++;
                pushAnswer("<返回语句>");
            }
        }
        else {
            if (outputArray.at(i) == "SEMICN") {
//                outputArray.insert(outputArray.begin() + i, "<返回语句>");
//                i++;
                pushAnswer("<返回语句>");
                return;
            }
        }
    }
}

//＜步长＞::= ＜无符号整数＞
void stepSize() {
    unsignedInteger();
//    outputArray.insert(outputArray.begin() + i, "<步长>");
//    i++;
    pushAnswer("<步长>");
}

//＜无返回值函数定义＞  ::= void＜标识符＞'('＜参数表＞')''{'＜复合语句＞'}'
void functionDefinitionWithoutReturn() {
    if (outputArray.at(i) == "VOIDTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "IDENFR") {
            string functionName = outputArray.at(i + 1).c_str();
            string functionType = "voidType";
            functionMap.insert(make_pair(functionName, functionType));
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "LPARENT") {
//                i += 2;
                pushToAnswerVector();
                parameterList();
                if (outputArray.at(i) == "RPARENT") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "LBRACE") {
//                        i += 2;
                        pushToAnswerVector();
                        compoundSentence();
                        if (outputArray.at(i) == "RBRACE") {
//                            i += 2;
                            pushToAnswerVector();
//                            outputArray.insert(outputArray.begin() + i, "<无返回值函数定义>");
//                            i++;
                            pushAnswer("<无返回值函数定义>");
                        }
                    }
                }
            }
        }
    }
}

//＜主函数＞    ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
void  mainFunction() {
    if (outputArray.at(i) == "VOIDTK") {
//        i += 2;
        pushToAnswerVector();
        if (outputArray.at(i) == "MAINTK") {
//            i += 2;
            pushToAnswerVector();
            if (outputArray.at(i) == "LPARENT") {
//                i += 2;
                pushToAnswerVector();
                if (outputArray.at(i) == "RPARENT") {
//                    i += 2;
                    pushToAnswerVector();
                    if (outputArray.at(i) == "LBRACE") {
//                        i += 2;
                        pushToAnswerVector();
                        compoundSentence();
                        if (outputArray.at(i) == "RBRACE") {
//                            i += 2;
                            pushToAnswerVector();
//                            outputArray.insert(outputArray.begin() + i, "<主函数>");
//                            i++;
                            pushAnswer("<主函数>");
                        }
                    }
                }
            }
        }
    }
}

//＜值参数表＞   ::= ＜表达式＞{,＜表达式＞}｜＜空＞
void valueParameterTable() {
    expression();
    while (outputArray.at(i) == "COMMA") {
//        i += 2;
        pushToAnswerVector();
        expression();
    }
//    outputArray.insert(outputArray.begin() + i, "<值参数表>");
//    i++;
    pushAnswer("<值参数表>");
}
