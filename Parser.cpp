//
//  Parser.cpp
//  Tranlator
//
//  Created by Ivan on 05.05.2021.
//

#include "Parser.hpp"
#include <iostream>
#include <string>

void Parser::analyze ()
{
 gl("");
 P("analyze");
 //prog.print();
   std::cout << std::endl << "Passed!!!" << std::endl;
}

void Parser::P (std::string cur_f)
{
   if (c_type == LEX_PROGRAM)
       gl("P");
   else
       throw Exeption("@ sym", scan.get_line(), scan.get_sym(), cur_f, curr_lex);
   if(c_type == LEX_BRAC1)
       gl("P");
   else
       throw Exeption("FIRST \"{\"", scan.get_line(), scan.get_sym(), cur_f, curr_lex);
 D("P");//это <описания> -> {<описание>}  D -> {D1;}
   while(c_type != LEX_BRAC2)
       S("P"); //<операторы>
   //check_labels();
   prog.print();
   std::cout <<  std::endl;
   
}

void Parser::D1 (std::string cur_f)
{
   try{
       do{
           gl("D1");
           if(c_type != LEX_ID)
               throw Exeption("D1_ID", scan.get_line(),scan.get_sym(), cur_f, curr_lex);
           int k = c_val;
           dec(curr_lex);
           gl("D1");
           if(c_type == LEX_EQ){
               gl("D1");
               if(c_type == LEX_MINUS){
                   gl("D1");
                   if(c_type != LEX_NUM)
                       throw Exeption("MIN" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
                   c_val *= -1;
                   dec(curr_lex);
                   prog.put_lex(Lex(POLIZ_ADDRESS, k));
                   prog.put_lex(Lex(LEX_NUM, c_val));
                   prog.put_lex(Lex(LEX_EQ, 0));
                   gl("D1");
               }
               else if(c_type == LEX_NUM){
                   dec(curr_lex);
                   prog.put_lex(Lex(POLIZ_ADDRESS, k));
                   prog.put_lex(curr_lex);
                   prog.put_lex(Lex(LEX_EQ, 0));
                   gl("D1");
               }
               else if(c_type == LEX_STR){
                   dec(curr_lex);
                   prog.put_lex(Lex(POLIZ_ADDRESS, k));
                   prog.put_lex(curr_lex);
                   prog.put_lex(Lex(POLIZ_STR_EQ, 0));//!!!!!!!!!!!!!!!!!
                   gl("D1");
               }
               else if(c_type == LEX_TRUE){
                   dec(curr_lex);
                   prog.put_lex(Lex(POLIZ_ADDRESS, k));
                   prog.put_lex(curr_lex);
                   prog.put_lex(Lex(LEX_EQ, 0));
                   gl("D1");
               }
               else if(c_type == LEX_FALSE){
                   dec(curr_lex);
                   prog.put_lex(Lex(POLIZ_ADDRESS, k));
                   prog.put_lex(curr_lex);
                   prog.put_lex(Lex(LEX_EQ, 0));
                   gl("D1");
               }
               else
                   throw Exeption("WRONG DESCRIPTION" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
           }
       }
       while(c_type == LEX_COMMA);
       if(c_type != LEX_SEMICOLON)
           throw Exeption(";" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
       gl("D1");
   }
   catch(const char* s){
       std::cout << "SYNTAX ERROR: " << s << std::endl;
       exit(0);
   }
}

void Parser::D (std::string cur_f)//описания
{
try{
   if(c_type == LEX_BRAC2)
       return;
   
   if(c_type != LEX_INT && c_type != LEX_STRING && c_type != LEX_BOOL && c_type )
       throw Exeption("WRONG DESCRIPTION" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
   
   while(true){
       if(c_type == LEX_INT || c_type == LEX_STRING || c_type == LEX_BOOL){
           current_type = c_type;
           
           D1("D");
       }
       else
           break;
   }
}
   catch(const char* s){
       std::cout << "SYNTAX ERROR: " << s << std::endl;
       exit(0);
   }

}

int Parser:: B(std::string cur_f){ // проверка на вложенные {...}
   if(c_type == LEX_BRAC1){
       gl("B");
       while(c_type != LEX_BRAC2)
           S("B");
       gl("B");
       return 1;
   }
       else
           return 0;
}

void Parser:: EQ(std::string cur_f){
   if(c_type == LEX_ID){
       int s = 0;
       if(TID[c_val].get_type() == LEX_STR)
           s = 1;
       check_id();
       prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
       gl("EQ");
       if(c_type == LEX_EQ){
           gl("EQ");
           E("EQ");
           eq_type();
           if(s)
               prog.put_lex(Lex(POLIZ_STR_EQ));
           else
               prog.put_lex(Lex(LEX_EQ));
       }
       else
           throw Exeption("EXPRESSION WITHOUT EQ\n" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
   }
   else
       E("EQ");
}


void Parser::S (std::string cur_f)
{
   int pl0, pl1, pl2, pl3, pl4, pl5, pl6, pl7, pl8;
 if (c_type == LEX_IF)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 {
   gl("S");
     if(c_type != LEX_LPAREN)
         throw Exeption("IF: expected (" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
     gl("S");
   E("S");
   eq_bool();
     if(c_type != LEX_RPAREN)
         throw Exeption("IF: expected )" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
   pl2 = prog.get_free ();//сохраняем для перехода по false из альфа
   prog.blank();
   prog.put_lex (Lex(POLIZ_FGO));
     gl("S");
     if(!B("S")) // для новых { ... }
         S("S");
     pl3 = prog.get_free();//переход после бэтта безусловный
     prog.blank();// увеличивает free
     prog.put_lex(Lex(POLIZ_GO));//кладёт lex в Lex*p из class poliz
     prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);//переход по неправде  после альфа
     if(c_type == LEX_ELSE)
     {
         gl("S");
         if(!B("S"))
             S("S");
         prog.put_lex(Lex(POLIZ_LABEL,prog.get_free()),pl3);//переход по неправде
     }
     else//случай if без else
     {
         prog.put_lex(Lex(POLIZ_LABEL, pl3+2), pl3);
     }
 }//end if
   
 else if (c_type == LEX_WHILE)
 {
   pl0=prog.get_free();//адрес для перехода после бэтта безусловно
   gl("S");
     if(c_type != LEX_LPAREN)
         throw Exeption("WHILE: expected (" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
     gl("S");
   E("S");
   eq_bool();
     if(c_type != LEX_RPAREN)
         throw Exeption("WHILE: expected )" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
   pl1=prog.get_free();//переход по false после альфа
   prog.blank();
   prog.put_lex (Lex(POLIZ_FGO));
     gl("S");
     ////cycle++;!!!!!!!!!!!!!!!!!!!!!!!
     if(!B("S"))
         S("S");
     //////cycle--;!!!!!!!
     prog.put_lex(Lex(POLIZ_LABEL, pl0));//переход на альфа
     prog.put_lex(Lex(POLIZ_GO));
     prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()),pl1);//переход по false из альфа
       
         if(br != 0){
             prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), br);//!!!!!!!!!!!!!!!!!!
             br = 0;
         }
 }//end while
   
 else if(c_type == LEX_FOR){
       gl("S");
       if(c_type != LEX_LPAREN)
           throw Exeption("for (" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
       gl("S");
       if(c_type != LEX_SEMICOLON)
           EQ("S");
       if(c_type != LEX_SEMICOLON)
           throw Exeption("; in the end" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
       gl("S");
       pl5 = prog.get_free();// освобождаенм место для бэтта
       if(c_type == LEX_SEMICOLON)
           throw Exeption("INFINITY CYCLE\n" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
       if(c_type != LEX_SEMICOLON){
           E("S");
       }
       eq_bool();
       pl6 = prog.get_free();// переход из бетта по false
       prog.blank();//free ++
       prog.put_lex(Lex(POLIZ_FGO));
       pl7 = prog.get_free();// переход из бетта по правде
       prog.blank();// free ++
       prog.put_lex(Lex(POLIZ_GO));
       pl8 = prog.get_free();// это адрес гамма
       if(c_type != LEX_SEMICOLON)
           throw Exeption("; in the end" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);;
       gl("S");
       if(c_type != LEX_LPAREN)
           EQ("S");
       prog.put_lex(Lex(POLIZ_LABEL, pl5));// переход после гамма на бэтта
       prog.put_lex(Lex(POLIZ_GO));// безусловный
       prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl7);// после бэтта
       if(c_type != LEX_RPAREN)
           throw Exeption("expectced ) in the end of for" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);;
       gl("S");
       //cycle++;
       if(!B("S"))
           S("S");
       //cycle--;
       prog.put_lex(Lex(POLIZ_LABEL, pl8));// безусловный на гамма
       prog.put_lex(Lex(POLIZ_GO));
       prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl6);
       if(br != 0){
           prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), br);
           br = 0;
       }
     //gl("S");
   }
   
   
 else if (c_type == LEX_READ)
 {
   gl("S");
   if (c_type == LEX_LPAREN)
   {
       gl("S");
       if (c_type == LEX_ID) {
           check_id_in_read();
           prog.put_lex (Lex ( POLIZ_ADDRESS, c_val) );
           //gl("S");
       }
       else
           throw Exeption("READ: expected varaible" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
       if(TID[c_val].get_type() == LEX_STRING || TID[c_val].get_type() == LEX_STR)
           prog.put_lex(Lex(POLIZ_STR_READ));
       else
           prog.put_lex(Lex(LEX_READ));
       gl("S");
       if ( c_type == LEX_RPAREN )
       {
           gl("S");
       }
       else
           throw Exeption("READ: expected )" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);

       if(c_type != LEX_SEMICOLON)
           throw Exeption("READ: expected ;" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);//throw "a";
       gl("S");
 }
 else
   throw Exeption("READ: expected (" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
 }//end read
   
   
 else if (c_type == LEX_WRITE)
 {
       type_of_lex t;
       gl("S");
       if (c_type == LEX_LPAREN)
       {
           gl("S");
           E("S");
           
           if((t = st_lex.pop()) == LEX_STR || t == LEX_STRING)
               prog.put_lex(Lex(POLIZ_STR_WRITE));
           else if(t == LEX_BOOL || t == LEX_TRUE || t == LEX_FALSE)
               prog.put_lex(Lex(POLIZ_BOOL_WRITE));
           else
               prog.put_lex(Lex(LEX_WRITE));
           st_lex.push(t);

           while(c_type == LEX_COMMA){
               gl("S");
               E("S");

               if((t = st_lex.pop()) == LEX_STR || t == LEX_STRING)
                   prog.put_lex(Lex(POLIZ_STR_WRITE));
               else if(t == LEX_BOOL || t == LEX_TRUE || t == LEX_FALSE)
                   prog.put_lex(Lex(POLIZ_BOOL_WRITE));
               else
                   prog.put_lex(Lex(LEX_WRITE));
               st_lex.push(t);
           }
           if (c_type == LEX_RPAREN)//)
           {
               gl("S");
               //prog.put_lex (Lex(LEX_WRITE));// по идее нужно добавить больше типов полиза
           }
           else
               throw Exeption("WRITE: expected )" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);

           if(c_type != LEX_SEMICOLON)//;
               throw Exeption("WRITE: expected ;" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);//throw "WRITE";
           gl("S");
       }
       else
           throw Exeption("WRITE: expected (" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
     
 }//end write
 else if ( c_type == LEX_ID )
 {
   check_id ();
   prog.put_lex (Lex ( POLIZ_ADDRESS, c_val) );
   gl("S");
   if ( c_type == LEX_EQ )
   {
     gl("S");
     E("S");
     eq_type();
     prog.put_lex (Lex (LEX_EQ) );
       if(c_type != LEX_SEMICOLON)//;
           throw Exeption("EQ: expected ;" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);//
       gl("S");
   }
   else
     throw Exeption("expected =" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
 }//assign-end
 else if(c_type == LEX_BREAK){
     /*if(cycle <= 0)
         throw "BREAK";*/
     gl("S");
     if(c_type != LEX_SEMICOLON)
         throw Exeption("BREAK: expected ;" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);;
     br = prog.get_free();//сохраняем место для перехода по break
     prog.blank();
     prog.put_lex(Lex(POLIZ_GO));
     gl("S");
 }
 else if(c_type == LEX_MINUS){
     gl("S");
     if(c_type == LEX_ID){
         check_id();
         if(TID[c_val].get_type() != LEX_INT)
             throw Exeption("MINUS: WRONG TYPE WITH \"-\"" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
         prog.put_lex(Lex(LEX_ID, c_val));
         prog.put_lex(Lex(POLIZ_UN_MINUS, 0));
         gl("F");
     }
     
     
 }
 else if(c_type == LEX_SEMICOLON)
     gl("S");
 else
     throw Exeption("Unexpected smthng dabldabltiefffff" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
/*
 else
   B("S");*/
}
   




void Parser::E (std::string cur_f)
{
 E1("E");
 if ( c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
      c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ || c_type == LEX_EQEQ )
 {
   st_lex.push (c_type);
   gl("E");
   E1("E");
   check_op();
 }
}

void Parser::E1 (std::string cur_f)
{
 T("E1");
 while ( c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR)
 {
   st_lex.push (c_type);
   gl("E1");
   T("E1");
   check_op();
 }
}

void Parser::T (std::string cur_f)
{
 F("T");
 while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND)
 {
   st_lex.push (c_type);
  gl("T");
  F("T");
  check_op();
 }
}

void Parser::F (std::string cur_f)
{
 if ( c_type == LEX_ID )
 {
   check_id();//проверяем есть ли такая переменная вообще и заносим в стэк лексем
   prog.put_lex (Lex (LEX_ID, c_val));
   gl("F");
 }
 else if ( c_type == LEX_NUM )
 {
   st_lex.push ( LEX_INT );
   prog.put_lex ( curr_lex );
   gl("F");
 }
 else if ( c_type == LEX_TRUE )
 {
   st_lex.push ( LEX_BOOL );
   prog.put_lex (Lex (LEX_TRUE, 1) );
   gl("F");
 }
 else if ( c_type == LEX_FALSE)
 {
   st_lex.push ( LEX_BOOL );
   prog.put_lex (Lex (LEX_FALSE, 0) );
   gl("F");
 }
 else if (c_type == LEX_NOT)
 {
   gl("F");
   F("F");
   check_not();
 }
 else if ( c_type == LEX_LPAREN )
 {
   gl("F");
   E("F");
   if ( c_type == LEX_RPAREN)
     gl("F");
   else
     throw Exeption("F: expected (" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
 }
 else if(c_type == LEX_STR){
     st_lex.push(LEX_STRING);
     prog.put_lex(curr_lex);
     gl("F");
 }
 else if(c_type == LEX_MINUS){
     gl("F");
     if(c_type == LEX_NUM){
         st_lex.push(LEX_INT);
         c_val *= -1;
         prog.put_lex(Lex(LEX_NUM, c_val));
         gl("F");
     }
     else if(c_type == LEX_ID){
         check_id();
         if(TID[c_val].get_type() != LEX_INT)
             throw Exeption("WRONG TYPE WITH \"-\"" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
         prog.put_lex(Lex(LEX_ID, c_val));
         prog.put_lex(Lex(POLIZ_UN_MINUS, 0));
         gl("F");
     }
 }

 else
   throw Exeption("expected operation" , scan.get_line(), scan.get_sym(), cur_f, curr_lex);
}

////////////////////////////////////////////////////////////////

void Parser::dec (Lex p )
{
   {
   if(p.get_type() == LEX_ID ){
       int i = p.get_value();
       if(TID[i].get_declare())
           throw Exeption("TWICE defenition" , scan.get_line(), scan.get_sym(), "dec", curr_lex);
       else{
           TID[i].put_declare();
           TID[i].put_type(current_type);
       }
   }
   
   else if(current_type == LEX_BOOL && (p.get_type() == LEX_TRUE || p.get_type() == LEX_FALSE)){}
   else if(current_type == LEX_INT && p.get_type() == LEX_NUM){}
   else if(current_type == LEX_STRING && p.get_type() == LEX_STR){}
   else
       throw Exeption("WRONG TYPE" , scan.get_line(), scan.get_sym(), "dec", curr_lex);
   }
  
   
}

void Parser::check_id ()
{
 if ( TID[c_val].get_declare() )
   st_lex.push ( TID[c_val].get_type() );
 else
   throw Exeption("not declared" , scan.get_line(), scan.get_sym(), "dec", curr_lex);
}

void Parser::check_op ()
{
 type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;

 t2 = st_lex.pop();
 op = st_lex.pop();
 t1 = st_lex.pop();
 
   if(t2 == LEX_STRING && t1 == LEX_STRING && op == LEX_PLUS){
       r = LEX_STRING;
       op = POLIZ_STR_PLUS;
   }
   else if(t1 == LEX_STRING && t2 == LEX_STRING && (op == LEX_NEQ || op == LEX_EQEQ || op == LEX_GTR || op == LEX_LSS)){
       r = LEX_BOOL;
       if(op == LEX_NEQ)
           op = POLIZ_STR_NEQ;
       else if(op == LEX_EQEQ)
           op = POLIZ_STR_EQEQ;
       else if(op == LEX_LSS)
           op = POLIZ_STR_LSS;
       else
           op = POLIZ_STR_GTR;
   }
   else if(t1 == LEX_INT && t2 == LEX_INT && (op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH))
       r = LEX_INT;
   else if(t1 == LEX_INT && t2 == LEX_INT && (op == LEX_LEQ || op == LEX_NEQ || op == LEX_GEQ || op == LEX_EQEQ || op == LEX_LSS || op == LEX_GTR))
       r = LEX_BOOL;
   else if(t1 == LEX_BOOL && t2 == LEX_BOOL && (op == LEX_NEQ || op == LEX_EQEQ || op == LEX_OR || op == LEX_AND))
       r = LEX_BOOL;
   else
       throw Exeption("wrong types are in operation" , scan.get_line(), scan.get_sym(), "chek_op", curr_lex);
   
   
 //if (t1 == t2  &&  t1 == t)
   st_lex.push(r);
 
 prog.put_lex (Lex (op) );
}

void Parser::check_not ()
{
 if (st_lex.pop() != LEX_BOOL)
   throw Exeption("wrong type is in not" , scan.get_line(), scan.get_sym(), "check_not", curr_lex);
 else
 {
   st_lex.push (LEX_BOOL);
   prog.put_lex (Lex (LEX_NOT));
 }
}

void Parser::eq_type ()
{
 if (st_lex.pop() != st_lex.pop())
   throw Exeption("wrong types are in =" , scan.get_line(), scan.get_sym(), "eq_type", curr_lex);
}

void Parser::eq_bool ()
{
 if ( st_lex.pop() != LEX_BOOL )
   throw Exeption("expression is not boolean" , scan.get_line(), scan.get_sym(), "eq_bool", curr_lex);
}

void Parser::check_id_in_read ()
{
 if ( !TID [c_val].get_declare() )
   throw Exeption("not declared" , scan.get_line(), scan.get_sym(), "check_id_in_read", curr_lex);
}
