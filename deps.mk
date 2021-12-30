Executer.o: Executer.cpp Executer.hpp Lex.hpp type_of_lex.hpp names.hpp \
  Poliz.hpp Stack.hpp Scanner.hpp Tabl_ident.hpp Ident.hpp Exeption.hpp
Exeption.o: Exeption.cpp Exeption.hpp Lex.hpp type_of_lex.hpp names.hpp
Ident.o: Ident.cpp Ident.hpp type_of_lex.hpp
Lex.o: Lex.cpp Lex.hpp type_of_lex.hpp names.hpp
Parser.o: Parser.cpp Parser.hpp Scanner.hpp type_of_lex.hpp \
  Tabl_ident.hpp Ident.hpp Exeption.hpp Lex.hpp names.hpp Stack.hpp \
  Poliz.hpp
Poliz.o: Poliz.cpp Poliz.hpp Lex.hpp type_of_lex.hpp names.hpp
Scanner.o: Scanner.cpp Scanner.hpp type_of_lex.hpp Tabl_ident.hpp \
  Ident.hpp Exeption.hpp Lex.hpp names.hpp
Stack.o: Stack.cpp Stack.hpp
TID.o: TID.cpp TID.hpp Tabl_ident.hpp Ident.hpp type_of_lex.hpp
TSTR.o: TSTR.cpp TSTR.hpp Tabl_ident.hpp Ident.hpp type_of_lex.hpp
TW.o: TW.cpp TW.hpp
Tabl_ident.o: Tabl_ident.cpp Tabl_ident.hpp Ident.hpp type_of_lex.hpp
main.o: main.cpp Parser.hpp Scanner.hpp type_of_lex.hpp Tabl_ident.hpp \
  Ident.hpp Exeption.hpp Lex.hpp names.hpp Stack.hpp Poliz.hpp \
  Executer.hpp
names.o: names.cpp names.hpp
type_of_lex.o: type_of_lex.cpp type_of_lex.hpp
