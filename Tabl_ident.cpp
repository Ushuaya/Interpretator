//
//  Tabl_ident.cpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//

#include "Tabl_ident.hpp"


int Tabl_ident::put ( const char *buf )
{
                        //for ( int j = 1; j < top; j++ )
                        //std::cout << p[j].get_name() << std::endl;
                        //std::cout << std::endl;
  for ( int j = 1; j < top; j++ )
    if ( !strcmp ( buf, p[j].get_name() ) )
      return j;
  p[top].put_name(buf);
  ++top;
  return top-1;
}


 
