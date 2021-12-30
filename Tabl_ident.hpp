//
//  Tabl_ident.hpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//
#pragma once
#ifndef Tabl_ident_hpp
#define Tabl_ident_hpp

#include <stdio.h>
#include "Ident.hpp"


class Tabl_ident
{
    
        Ident      * p;
        int          size;
        int          top;
public:
                     Tabl_ident ( int max_size )
                     {
                       p = new Ident [ size = max_size ];
                       top = 1;
                     }
    ~Tabl_ident () {/* std::cout << "DDD\n" << this << std::endl<< std::endl;*/ delete [] p; }
        Ident      & operator[] ( int k ) { return p[k]; }
        int          put ( const char *buf );
       int get_top(){
           return top;
       }
    
};








#endif /* Tabl_ident_hpp */
