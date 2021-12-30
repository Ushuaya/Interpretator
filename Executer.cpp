//
//  Executer.cpp
//  Tranlator
//
//  Created by Ivan on 06.05.2021.
//

#include "Executer.hpp"


extern Tabl_ident TID, TSTR;

void Executer:: execute(Poliz& prog){
    {
    Stack<int, 100> args;
        int i = 0, j, t, index = 0, size = prog.get_free();
    char c;
    char* s = new char[30];
    while(index < size){
        pc_el = prog[index];
        switch(pc_el.get_type()){
            case LEX_TRUE:
            case LEX_FALSE:
            case LEX_NUM:
            case LEX_STR:
            case POLIZ_ADDRESS:
            case POLIZ_LABEL:
                args.push(pc_el.get_value());
            break;
            case LEX_ID:
                i = pc_el.get_value();
                args.push(TID[i].get_value());
            break;
            case LEX_NOT:
                args.push(!args.pop());
            break;
            case LEX_OR:
                i = args.pop();
                args.push(args.pop() || i);
            break;
            case LEX_AND:
                i = args.pop();
                args.push(args.pop() && i);
            break;
            case POLIZ_GO:
                index = args.pop() - 1;
            break;
            case POLIZ_FGO:
                i = args.pop();
                if(!args.pop())
                    index = i - 1;
            break;
            case LEX_WRITE:
                std::cout << args.pop() << std::endl;
            break;
            case POLIZ_STR_WRITE:
                t = args.pop();
                std::cout << TSTR[t].get_name() << std::endl;
            break;
            case POLIZ_BOOL_WRITE:
                t = args.pop();
                if(t == 1)
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
            break;
            case LEX_READ:
                int k;
                i = args.pop();

                if(TID[i].get_type() == LEX_INT){
                    std::cout << "Input int value ";
                    std::cin >> k;
                    TID[i].put_value(k);
                    TID[i].put_assign();
                }
                else{
                    char j[20];
                rep:
                    std::cout << "Input boolean value(true or false): ";
                    std::cin >> j;
                    if(!strcmp(j, "true"))
                        k = 1;
                    else if(!strcmp(j, "false"))
                        k = 0;
                    else{
                        std::cout << "Error in input: true/false";
                        std::cout << std::endl;
                        goto rep;
                    }
                    {
                        TID[i].put_value(k);
                        TID[i].put_assign();
                    }
                }
            break;
            case POLIZ_STR_READ:
                std::cout << "Input string: ";
                c = ' ';
                i = 0;
                c = getchar();
                while(c != '\n'){
                    s[i] = c;
                    c = getchar();
                    i++;
                }
                s[i] = '\0';
                t = args.pop();
                TSTR.put(s);
                TID[t].put_value(TSTR.get_top() - 1);
            break;
            case LEX_PLUS:
                args.push(args.pop() + args.pop());
            break;
            case POLIZ_STR_PLUS:
                i = args.pop();
                j = args.pop();
                strcpy(s, TSTR[j].get_name());
                TSTR.put(strcat(s, TSTR[i].get_name()));
                args.push(TSTR.get_top() - 1);
            break;
            case LEX_TIMES:
                args.push(args.pop() * args.pop());
            break;
            case LEX_MINUS:
                i = args.pop();
                args.push(args.pop() - i);
            break;
            case LEX_SLASH:
                i = args.pop();
                if(i){
                    args.push(args.pop() / i);
                    break;
                }
                else
                    throw "POLIZ:divide by zero";
            break;
            case POLIZ_UN_MINUS:{
                //i = args.pop();
                TID[i].put_value((-1)*TID[i].get_value());
                //args.push(-i);
            }
            break;
            case LEX_EQEQ:
                args.push(args.pop() == args.pop());
            break;
            case POLIZ_STR_EQEQ:
                args.push((strcmp(TSTR[args.pop()].get_name(), TSTR[args.pop()].get_name())) == 0);
            break;
            case LEX_LSS:
                i = args.pop();
                args.push(args.pop() < i);
            break;
            case POLIZ_STR_LSS:
                args.push((strcmp(TSTR[args.pop()].get_name(), TSTR[args.pop()].get_name())) < 0);
            break;
            case LEX_GTR:
                i = args.pop();
                args.push(args.pop() > i);
            break;
            case POLIZ_STR_GTR:
                args.push((strcmp(TSTR[args.pop()].get_name(), TSTR[args.pop()].get_name())) > 0);
            break;
            case LEX_LEQ:
                i = args.pop();
                args.push(args.pop() <= i);
            break;
            case LEX_GEQ:
                i = args.pop();
                args.push(args.pop() >= i);
            break;
            case LEX_NEQ:
                i = args.pop();
                args.push(args.pop() != i);
            break;
            case POLIZ_STR_NEQ:
                args.push((strcmp(TSTR[args.pop()].get_name(), TSTR[args.pop()].get_name())) != 0);
            break;
            case LEX_EQ:
                
                i = args.pop();//what to put
                j = args.pop();//where to put
                {
                    TID[j].put_value(i);
                    TID[j].put_assign();
                }
            break;
            case POLIZ_STR_EQ:
                i = args.pop();
                j = args.pop();
                   // std::cout << TSTR.get_top() << std::endl;
                   // for ( int j = 1; j < TSTR.get_top(); j++ )
                    //std::cout << TSTR[j].get_name() << std::endl;
                    //std::cout << std::endl;
                
                TSTR[j].put_name(TSTR[i].get_name());
                TID[j].put_value(i);
                TID[j].put_assign();
            break;
            default:
                throw "POLIZ: unexpected elem";
        }
        index++;
    }
        std::cout << "Finish of executing!!!" << std::endl;
    }
    
}
