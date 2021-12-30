//
//  Parser.hpp
//  Tranlator
//
//  Created by Ivan on 05.05.2021.
//
#pragma once
#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include "Scanner.hpp"
#include "type_of_lex.hpp"
#include "Stack.hpp"
#include "Poliz.hpp"
extern Tabl_ident TID, TSTR;




class Parser
{
        Lex          curr_lex;
        type_of_lex  c_type;
       type_of_lex   current_type;
        int          c_val;
   int c;
        Scanner      scan;
        Stack < int, 100 > st_int;
        Stack < type_of_lex, 100 >  st_lex;
        void         P(std::string cur_f);
        void         D1(std::string cur_f);
        void         D(std::string cur_f);
        int         B(std::string cur_f);
        void         S(std::string cur_f);
        void         E(std::string cur_f);
        void         EQ(std::string cur_f);
        void         E1(std::string cur_f);
        void         T(std::string cur_f);
        void         F(std::string cur_f);
        void         dec (Lex p);
        void         check_id ();
        void         check_op ();
        void         check_not ();
        void         eq_type ();
        void         eq_bool ();
        void         check_id_in_read ();
        void         gl (std::string cur_func)
                     {
                       curr_lex = scan.get_lex(cur_func);
                       c_type = curr_lex.get_type();
                       c_val = curr_lex.get_value();
                     }
public:
   int br = 0;
        Poliz        prog;
                     Parser (const char *program ) : scan (program),prog (1000) {}
        void         analyze();
};

#endif /* Parser_hpp */
