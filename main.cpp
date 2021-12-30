#include <iostream>

#include <string>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>

//#include "TSTR.hpp"

//#include "Tabl_ident.hpp"


#include "Parser.hpp"
//#include "Stack.hpp"
#include "Executer.hpp"

#include "Tabl_ident.hpp"

 
Tabl_ident TSTR(100);
Tabl_ident TID ( 100 );
 
 
/////////////////////////  Класс Lex  //////////////////////////
 
//------------class exeption------------


 
/////////////////////  Класс Ident  ////////////////////////////
 
 
//////////////////////  Класс Tabl_ident  ///////////////////////

 

/////////////////////////////////////////////////////////////////

 
 
/////////////////////////  Класс Poliz  /////////////////////////////
 
////////////////////////////////////////////////////////////////////
 
 
/////////////////////  Класс Scanner  //////////////////////////////
 
///////////////////////////  Класс Parser  /////////////////////////////////

//////////////////////////////////  Класс Executer  //////////////////////////////


class Interpretator{
    Executer E;
public:
    Parser pars;
    Interpretator(char* program) : pars(program) {};
    void interpretation(){
        pars.analyze();
        E.execute(pars.prog);
    }
};




int main ( int argc, char ** argv )
{
  try
  {
    Interpretator I ( argv[1] );
    I.interpretation ();
      //Parser   pars("m");
      //pars.analyze ();
    return 0;
  }
  catch (char c)
  {
      std::cout << "unexpected symbol " << c << std::endl;
    return 1;
  }
  catch (Lex l)
  {
      std::cout << "unexpected lexeme";
      std::cout << l;
    return 1;
  }
    catch (Exeption exp)
    {
        std::cout << "Thh error: " << exp.error << std::endl;
        std::cout << "In line: " << exp.line << std::endl;
        std::cout << "In symbol: " << exp.sym << std::endl;
        std::cout << "In func: " << exp.func << std::endl;
        std::cout << "In lexeme: " << exp.lexeme << std::endl;
        return 1;
    }
  catch ( const char *source )
  {
      std::cout << source << std::endl;
    return 1;
  }
}

