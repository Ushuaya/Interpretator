//
//  Ident.hpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//
#pragma once
#ifndef Ident_hpp
#define Ident_hpp

#include <stdio.h>
#include <iostream>
#include "type_of_lex.hpp"
//#include "Tabl_ident.hpp"


class Ident
{
   
        char       * name;
        bool         declare;
        type_of_lex  type;
        bool         assign;
        int          value;
public:
                     Ident() { declare = false; assign = false; }
        char       * get_name () { return name; }
        void         put_name (const char *n)
                     {
                       name = new char [ strlen(n)+1];
                       strcpy(name,n);
                     }
        bool         get_declare () { return declare; }
        void         put_declare () { declare = true; }
        type_of_lex  get_type    () { return type; }
        void         put_type    ( type_of_lex t ) { type = t; }
        bool         get_assign  () { return assign; }
        void         put_assign  (){ assign = true; }
        int          get_value   () { return value; }
        void         put_value   (int v){ value = v; }
};


#endif /* Ident_hpp */
