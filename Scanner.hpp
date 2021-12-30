//
//  Scanner.hpp
//  Tranlator
//
//  Created by Ivan on 05.05.2021.
//
#pragma once
#ifndef Scanner_hpp
#define Scanner_hpp

#include <stdio.h>
#include <iostream>
#include "type_of_lex.hpp"
#include "Tabl_ident.hpp"
//#include "Lex.hpp"
#include "Exeption.hpp"
//#include "TID.hpp"
//#include "TSTR.hpp"
extern Tabl_ident TID, TSTR;


class Scanner
{
        enum         state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ, STR };
 static char       * TW    [];
 static type_of_lex  words [];
 static char       * TD    [];
 static type_of_lex  dlms  [];
        state        CS;
        FILE       * fp;
        char         c;
        char         buf [ 80 ];
        int          buf_top;
        void         clear ()
                     {
                       buf_top = 0;
                       for ( int j = 0; j < 80; j++ )
                         buf[j] = '\0';
                     }
        void         add ()
                     {
                       buf [ buf_top++ ] = c;
                     }
        int          look ( const char *buf, char **list )
                     {
                         int i = 0;
                       while (list[i])
                       {
                         if ( !strcmp(buf, list[i]) )
                           return i;
                         ++i;
                       }
                       return 0;
                     }
        void         gc ()
                     {
                         c = fgetc (fp);
                         if (c == '\n')
                         {
                             file_line++;
                             file_sym = 0;
                         }
                         else
                             file_sym++;
                     }
   
public:
           int file_line = 0;
           int file_sym = 0;
       int get_line()
       {
           return file_line;
       }
       int get_sym()
       {
           return file_sym;
       }
   
           Scanner (const char * program)
           {
               fp = fopen ( program, "r" );
               if (fp == NULL)
                   throw "Cannot open the file\n";
               CS = H;
               clear();
               gc();
           }
        Lex          get_lex (std::string cur_func);
};

#endif /* Scanner_hpp */
