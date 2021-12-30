//
//  Lex.hpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//
#pragma once
#ifndef Lex_hpp
#pragma once
#define Lex_hpp

#include <cstdio>
#include <iostream>
#include "type_of_lex.hpp"
#include "names.hpp"
//#include "Lex.cpp"



class Lex
{
    //static const char*names;

 type_of_lex t_lex;
 int v_lex;
public:
                     Lex ( type_of_lex t = LEX_NULL, int v = 0): t_lex (t), v_lex (v) {}
        type_of_lex  get_type ()  { return t_lex; }
        int          get_value () { return v_lex; }
   friend std::ostream &    operator<< (std::ostream &s, Lex l)
                     {
                         s << '(' << names[l.t_lex] << ',' << l.v_lex << ");";
                         return s;
                     }
};

#endif /* Lex_hpp */
