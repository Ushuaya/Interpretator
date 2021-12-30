//
//  Exeption.cpp
//  Tranlator
//
//  Created by Ivan on 05.05.2021.
//

#include "Exeption.hpp"
//#include "type_of_lex.hpp"



Exeption::Exeption(const char * ferror, int fline, int fsym, std::string ffunc)
{
    size_t SIZE_T = strlen(ferror) + 1;
    this->error = new char[SIZE_T];
    snprintf(error, SIZE_T, "%s", ferror);
    line = fline;
    sym = fsym;
    SIZE_T = ffunc.length() + 1;
    this->func = new char[SIZE_T];
    snprintf(func, SIZE_T, "%s", ffunc.c_str());
    lexeme = Lex(LEX_NULL, 0);

    
}
Exeption::Exeption(const char * ferror, int fline, int fsym, std::string ffunc, Lex flexeme)
{
    size_t SIZE_T = strlen(ferror) + 1;
    this->error = new char[SIZE_T];
    snprintf(error, SIZE_T, "%s", ferror);
    line = fline;
    sym = fsym;
    SIZE_T = ffunc.length() + 1;
    this->func = new char[SIZE_T];
    snprintf(func, SIZE_T, "%s", ffunc.c_str());
    lexeme = flexeme;

    
}

Exeption::Exeption(const Exeption& source)
{
    // Поскольку m_length не является указателем, то мы можем выполнить поверхностное копирование
    if (source.error)
    {
        // Выделяем память для нашей копии
        error = new char[strlen(source.error)];
        strcpy(error, source.error);
        
    }
    else
        error = 0;
    
    line = source.line;
    sym = source.sym;
    
    if (source.func)
    {
        // Выделяем память для нашей копии
        func = new char[strlen(source.func)];
        strcpy(func, source.func);
        
    }
    else
        func = 0;
    
    lexeme = source.lexeme;
    
}
Exeption::~Exeption()
{
    delete[] this->error;
    delete[] this->func;
}

 
