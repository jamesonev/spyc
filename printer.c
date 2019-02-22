/* This is the private implementation of pretty printer for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include "lexeme.h"

void pp(lexeme* tree){
    if(!tree) return;
    /*printf("\n**************************\n");
    printType(tree->type, stdout);
    if(tree->car){
        printf("car: ");
        printType(tree->car->type, stdout);
    }
    if(tree->cdr){
        printf("cdr: ");
        printType(tree->cdr->type, stdout);
    }
    printf("**************************\n");*/
    switch(tree->type){
//unary
        case REAL:
            printf("%f ", tree->realNumVal);
            break;
        case INTEGER:
            printf("%d ", tree->intVal);
            break;
        case STRING:
            printf("%s ", tree->stringVal);
            break;
        case ID:
            printf("%s ", tree->stringVal);
            break;
        case OBJDEF:
            printf("struct\n");
            pp(tree->car);  //calls id
            printf("{\n");
            pp(tree->cdr);  //calls expressionList
            printf("}\n");
            break;
//operators
        case ASSIGN:
            printf("in pp.ASSIGN\n");
            pp(tree->car);
            printf("= ");
            pp(tree->cdr);
            printf("\n");
            break;
        case PLUS:
            pp(tree->car);
            printf("+ ");
            pp(tree->cdr);
            break;
        case MINUS:
            pp(tree->car);
            printf("- ");
            pp(tree->cdr);
            break;
        case MULTIPLY:
            pp(tree->car);
            printf("* ");
            pp(tree->cdr);
            break;
        case DIVIDE:
            pp(tree->car);
            printf("/ ");
            pp(tree->cdr);
            break;
        case MOD:
            pp(tree->car);
            printf("%c ", '%');
            pp(tree->cdr);
            break;
        case AND:
            pp(tree->car);
            printf("& ");
            pp(tree->cdr);
            break;
        case OR:
            pp(tree->car);
            printf("| ");
            pp(tree->cdr);
            break;
//keywords
        case WHILE:
            printf("while(");
            pp(tree->car);  //calls expression
            printf(")\n");
            pp(tree->cdr);  //calls block
            break;
        case IF:
            printf("if(");
            pp(tree->car);
            printf(")\n");
            pp(tree->cdr);
            break;
        case IFGLUE:
            pp(tree->car);  //calls block
            if(tree->cdr) pp(tree->cdr);    //calls else
            break;
        case ELSE:
            printf("else\n");
            if(tree->car) pp(tree->car);    //calls if
            else pp(tree->cdr);             //calls block
            break;
        case BLOCK:
            printf("{\n");
            pp(tree->car);  //calls statements
            printf("}\n");
            break;
        case STATEMENTS:
            pp(tree->car);
            if(tree->cdr) pp(tree->cdr);
            break;
        case DEFLIST:
            pp(tree->car);
            if(tree->cdr)   pp(tree->cdr);
            break;
        case RETURN:
            printf("return ");
            if(tree->car) pp(tree->car);
            break;
        case EXPRESSION:
            pp(tree->car);
            if(tree->cdr){
                pp(tree->cdr->car); //print operator
                pp(tree->cdr->cdr); //recur
            }
            break;
        case EXPRLIST:
            pp(tree->car);          //calls expression
            if(tree->cdr){
                printf(", ");
                pp(tree->cdr);      //recur
            }
            break;
        case OPTEXPRLIST:
            if(tree->car){
                pp(tree->car);      //call exprlist
            }
            break;
        case OPTPARAMLIST:
            pp(tree);
            if(tree->car){
                pp(tree->car);      //call exprlist
            }
            break;
        case FUNCCALL:
            pp(tree->car);  //calls id
            printf("(");
            pp(tree->cdr);   //calls 'GLUE'
            printf(")\n");
            break;
        case FUNCDEF:
            printf("funcdef \n");
            pp(tree->car);  //calls id
            pp(tree->cdr);   //calls 'GLUE'
            break;
        case GLUE:
            printf("(");
            pp(tree->car);  //calls 'OPTEXPRLIST'
            printf(")\n");
            pp(tree->cdr);  //calls BLOCK
            break;
        case ARRAY:
            pp(tree->car);  //id
            printf("[");
            pp(tree->cdr);  //exprlist
            printf("]\n");
            break;
//comparisons
        case GREATER_THAN:
            pp(tree->car);
            printf("> ");
            pp(tree->cdr);
            break;
        case LESS_THAN:
            pp(tree->car);
            printf("< ");
            pp(tree->cdr);
            break;
        case EQUALS:
            pp(tree->car);
            printf("== ");
            pp(tree->cdr);
            break;
        default:
            printf("unhandled statement in pp: \n");
            printLexeme(tree, stdout);
            exit(-3);
    }
}
