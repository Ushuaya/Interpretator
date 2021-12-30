//
//  type_of_lex.hpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//
#pragma once
#ifndef type_of_lex_hpp
#define type_of_lex_hpp

#include <stdio.h>

enum type_of_lex
{
  LEX_NULL, /*0*/
  LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_DO, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE, LEX_INT, /*9*/
  LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_THEN, LEX_TRUE, LEX_VAR, LEX_WHILE, LEX_WRITE, /*18*/
  LEX_FIN, /*19*/
  LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS, /*27*/
  LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, /*35*/
  LEX_NUM, /*36*/
  LEX_ID, /*37*/
  POLIZ_LABEL, /*38*/
  POLIZ_ADDRESS, /*39*/
  POLIZ_GO, /*40*/
  POLIZ_FGO, /*41*/
    //--NEW--
    LEX_BRAC1, // {
    LEX_BRAC2, // }
    LEX_STRING, //string
    LEX_STR, // smthng like "dfvfd"
    //LEX_MIN
    LEX_MARK, //"
    POLIZ_UN_MINUS, // унарный минус ?!?!?
    LEX_FOR, //  cам ый обчный цикл for(<op>;<op>;<op>)
    POLIZ_STR_EQ,// присвоение строки
    POLIZ_STR_WRITE,
    POLIZ_BOOL_WRITE,
    POLIZ_STR_READ,
    LEX_BREAK,
    POLIZ_STR_PLUS,
    LEX_EQEQ,//==
    POLIZ_STR_NEQ,//!=
    POLIZ_STR_EQEQ,//==
    POLIZ_STR_LSS,//<
    POLIZ_STR_GTR//>
};

#endif /* type_of_lex_hpp */
