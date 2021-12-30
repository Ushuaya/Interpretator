//
//  Scanner.cpp
//  Tranlator
//
//  Created by Ivan on 05.05.2021.
//

#include "Scanner.hpp"
#include <iostream>


char * Scanner::TW    [] = {"", "and", "begin", "bool", "do", "else", "end", "if", "false", "int", "bool", "string", "not", "or", "program", "read", "then", "true", "var", "while", "write", "for", "break", NULL};

type_of_lex
Scanner::words [] = {LEX_NULL, LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_DO, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE, LEX_INT, LEX_BOOL, LEX_STRING, LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_THEN, LEX_TRUE, LEX_VAR, LEX_WHILE, LEX_WRITE, LEX_FOR, LEX_BREAK, LEX_NULL};

char * Scanner::TD    [] = {"", "@", ";", ",", ":", ":=", "(", ")", "=", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=", "{","}", "\"","==", NULL};

type_of_lex
Scanner::dlms  [] = {LEX_NULL, LEX_FIN, LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ,
                    LEX_LSS, LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_BRAC1, LEX_BRAC2,LEX_MARK, LEX_EQEQ, LEX_NULL};

Lex Scanner::get_lex (std::string cur_f)
{
   int d = 0, j;

 CS = H;
 do
 {
   switch(CS)
   {
     case H:
       if ( c==' ' || c == '\n' || c== '\r' || c == '\t' )
         gc();
       else if ( isalpha(c) )
       {
         clear();
         add();
         gc();
         CS = IDENT;
       }
       else if ( isdigit(c) )
       {
         d = c - '0';
         gc();
         CS = NUMB;
       }
       else if(c == '=' || c == '<' || c == '>' || c == '!')
       {
         clear();
         add();
         gc();
         CS = ALE;
       }
       else if(c == '\"'){                 // —“–Œ ¿
           gc();
           clear();
           CS = STR;
       }
       else if (c == '@')
         return Lex(LEX_FIN);
       else if (c == '!')
       {
         clear();
         add();
         gc();
         CS = NEQ;
       }
       else
         CS = DELIM;
       break;
     case IDENT:
       if ( isalpha(c) || isdigit(c) )
       {
         add();
         gc();
       }
       else if ( (j = look (buf, TW)) )
         return Lex (words[j], j);
       else
       {
         j = TID.put(buf);
         return Lex (LEX_ID, j);
       }
       break;
           
     case NUMB:
       if ( isdigit(c) )
       {
         d = d * 10 + (c - '0'); gc();
       }
       else
         return Lex ( LEX_NUM, d);
       break;
           
       case COM:
           if(c == '@')
               throw Exeption("@ sym", get_line(), get_sym(), cur_f);
           if(c == '*'){
               gc();
               if(c == '/'){
                   gc();
                   CS = H;
               }
           }
           else
               gc();
           break;
           
     case ALE:
       if ( c== '=')
       {
         add();
         gc();
         j = look ( buf, TD );
         return Lex ( dlms[j], j);
       }
       else
       {
         j = look ( buf, TD );
         return Lex ( dlms[j], j );
       }
       break;
           
     case NEQ:
       if (c == '=')
       {
         add();
         gc();
         j = look ( buf, TD );
         return Lex ( LEX_NEQ, j );
       }
       else
         throw '!';
       break;
           
           
     case DELIM:
           if(c == '/'){
               gc();
               if(c == '*'){
                   CS = COM;
                   continue;
               }
               else{
                   return Lex(LEX_SLASH, 0);
               }
           }
           clear();
           add();
           if ( (j = look ( buf, TD)) )
           {
             gc();
             return Lex ( dlms[j], j );
           }
           else
             throw Exeption("unexpected sym", get_line(), get_sym(), cur_f);
           
           
       case STR:
           if(c == '\"' && buf_top > 0){
               j = TSTR.put(buf);
               gc();
               return Lex(LEX_STR, j);
           }
           else if(c == '\"' && buf_top == 0){
               c = '\0';
               add();
               gc();
               j = TSTR.put(buf);
               return Lex(LEX_STR, j);
           }
           else if(c == '@')
               throw Exeption("@ sym", get_line(), get_sym(), cur_f);
           else{
               add();
               gc();
           }
           break;
           
           
           
           
           
           
           break;
   }//end switch
 } while (true);
}
