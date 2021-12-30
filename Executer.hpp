//
//  Executer.hpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//
#pragma once
#ifndef Executer_hpp
#define Executer_hpp

#include <stdio.h>
#include "Lex.hpp"
#include "Poliz.hpp"
#include "Stack.hpp"
#include "Scanner.hpp"
#include "Tabl_ident.hpp"
//extern Tabl_ident TID, TSTR;



class Executer{
    Lex pc_el;
public:
    void execute(Poliz& prog);
};

#endif /* Executer_hpp */
