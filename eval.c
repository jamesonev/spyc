/* This is the private implementation of the evaluator for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme.h"
#include "eval.h"

lexeme* evalPlus(lexeme* tree, lexeme* env){
    lexeme* lhs = eval(tree->car, env);
    lexeme* rhs = eval(tree->cdr, env);
    if(lhs->type == INTEGER) {

        if(rhs->type == INTEGER)
            return newLexeme(INTEGER, lhs->intVal + rhs->intVal, NULL, 0);
        else if(rhs->type == REAL)
            return newLexeme(REAL, 0, NULL, (double)lhs->intVal + rhs->realNumVal);
        
    }
    else if(lhs->type == REAL){

        if(rhs->type == REAL)
            return newLexeme(REAL, 0, NULL, lhs->realNumVal + rhs->realNumVal);
        else if(rhs->type == INTEGER)
            return newLexeme(REAL, 0, NULL, lhs->realNumVal + (double)rhs->intVal);

    }
    printf("called PLUS with illegal args: \n");
    printLexeme(lhs, stdout);
    printLexeme(rhs, stdout);
    exit(-3);
    return NULL;
}

lexeme* eval(lexeme* tree, lexeme* env){
    switch(tree->type){
        case STATEMENTS:
            return eval(tree->car, env);
        case STATEMENT:
            return eval(tree->car, env);
//unary
        case INTEGER:
            return tree;
        case REAL:
            return tree;
        case STRING:
            return tree;
//operators
        case PLUS:
            return evalPlus(tree, env);
        default:
            printf("unhandled statement in emval: \n");
            printLexeme(tree, stdout);
            exit(-3);
    }
}
