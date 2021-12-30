//
//  Exeption.hpp
//  Tranlator
//
//  Created by Ivan on 05.05.2021.
//
#pragma once
#ifndef Exeption_hpp
#define Exeption_hpp

#include <stdio.h>
#include <iostream>
#include "Lex.hpp"
#include "type_of_lex.hpp"

class Exeption
{
    public:
    char *error;
    int line;
    int sym;
    char *func;
    Lex lexeme;
    
    public:
    Exeption(int ERR_CODE);
    Exeption(const char * error, int line, int sym, std::string ffunc);
    Exeption(const char * ferror, int fline, int fsym, std::string ffunc, Lex flexeme);
    const char* GetName() const {return error;}
    Exeption(const Exeption& source);
    ~Exeption();
};






#endif /* Exeption_hpp */
