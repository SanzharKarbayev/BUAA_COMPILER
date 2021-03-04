//
//  syntax analysis.hpp
//  编译技术
//
//  Created by Sanzhar on 18.02.2021.
//

#ifndef syntax_analysis_hpp
#define syntax_analysis_hpp

#include "main.hpp"

extern map<string, string> functionMap;
extern vector<string> answerVector;

//＜字符串＞   ::=  "｛十进制编码为32,33,35-126的ASCII字符｝"
void charString();                          //DONE

//＜程序＞   ::=  ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
void program();                             //TODO!!!!!

//＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
void constantDescription();                 //DONE

//＜常量定义＞   ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
//                | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
void constantDefinition();                  //DONE

//＜无符号整数＞  ::= ＜数字＞｛＜数字＞｝
void unsignedInteger();

//＜整数＞        ::= ［＋｜－］＜无符号整数＞
void integer();

//＜声明头部＞   ::=  int＜标识符＞ |char＜标识符＞
void declarationHeader();

//＜常量＞   ::=  ＜整数＞|＜字符＞
void constant();

//＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
void variableDescription();

//＜变量定义＞ ::= ＜变量定义无初始化＞|＜变量定义及初始化＞
void variableDefinition();

//＜变量定义无初始化＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞'['＜无符号整数＞']'|＜标识符＞'['＜无符号整数＞']''['＜无符号整数＞']'){,(＜标识符＞|＜标识符＞'['＜无符号整数＞']'|＜标识符＞'['＜无符号整数＞']''['＜无符号整数＞']' )}
void variableDefinitionWithoutInit();
        
/*＜变量定义及初始化＞  ::=
 ＜类型标识符＞＜标识符＞=＜常量＞
|＜类型标识符＞＜标识符＞'['＜无符号整数＞']'='{'＜常量＞{,＜常量＞}'}'
|＜类型标识符＞＜标识符＞'['＜无符号整数＞']''['＜无符号整数＞']'='{''{'＜常量＞{,＜常量＞}'}'{, '{'＜常量＞{,＜常量＞}'}'}'}'*/
void variableDefinitionWithInit();

//＜有返回值函数定义＞  ::=  ＜声明头部＞'('＜参数表＞')' '{'＜复合语句＞'}'
void functionDefinitionWithReturn();

//＜无返回值函数定义＞  ::= void＜标识符＞'('＜参数表＞')''{'＜复合语句＞'}'
void functionDefinitionWithoutReturn();

//＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
void compoundSentence();

//＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
void parameterList();

//＜主函数＞    ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
void  mainFunction();

//＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
void expression();

//＜项＞     ::= ＜因子＞{＜乘法运算符＞＜因子＞}
void term();

//＜因子＞    ::= ＜标识符＞｜＜标识符＞'['＜表达式＞']'|＜标识符＞'['＜表达式＞']''['＜表达式＞']'|'('＜表达式＞')'｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞
void factor();

//＜语句＞    ::= ＜循环语句＞｜＜条件语句＞| ＜有返回值函数调用语句＞;  |＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜情况语句＞｜＜空＞;|＜返回语句＞; | '{'＜语句列＞'}'
void statement();

//＜赋值语句＞   ::=  ＜标识符＞＝＜表达式＞|＜标识符＞'['＜表达式＞']'=＜表达式＞|＜标识符＞'['＜表达式＞']''['＜表达式＞']' =＜表达式＞
void assignmentStatement();

//＜条件语句＞  ::= if '('＜条件＞')'＜语句＞［else＜语句＞］
void conditionalStatement();

//＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞
void condition();

//＜循环语句＞   ::=  while '('＜条件＞')'＜语句＞| for'('＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞')'＜语句＞
void loopStatement();

//＜步长＞::= ＜无符号整数＞
void stepSize();

//＜情况语句＞  ::=  switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞＜缺省＞‘}’
void situationStatement();

//＜情况表＞   ::=  ＜情况子语句＞{＜情况子语句＞}
void caseTable();

//＜情况子语句＞  ::=  case＜常量＞：＜语句＞
void caseClause();

//＜缺省＞   ::=  default :＜语句＞
void defaultStatement();

//＜有返回值函数调用语句＞ ::= ＜标识符＞'('＜值参数表＞')' 和 ＜无返回值函数调用语句＞ ::= ＜标识符＞'('＜值参数表＞')'
void functionCall();

//＜值参数表＞   ::= ＜表达式＞{,＜表达式＞}｜＜空＞
void valueParameterTable();

//＜语句列＞   ::= ｛＜语句＞｝
void sentenceList();

//＜读语句＞    ::=  scanf '('＜标识符＞')'
void readingSentence();

//＜写语句＞    ::= printf '(' ＜字符串＞,＜表达式＞ ')'| printf '('＜字符串＞ ')'| printf '('＜表达式＞')'
void writeSentence();

//＜返回语句＞   ::=  return['('＜表达式＞')']
void returnStatement();

#endif /* syntax_analysis_hpp */
