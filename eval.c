/* This is the private implementation of the evaluator for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme.h"
#include "eval.h"

void eval(lexeme* tree, lexeme* env){
    switch(tree->type){
        case STATEMENTS:
            eval(tree->car, env);
            break;
        case STATEMENT:
            eval(tree->car, env);
            break;
        case PLUS:
            printf("found plus\n");
            printf("%d\n", tree->car->intVal + tree->cdr->intVal);
            /*printLexeme(tree, stdout);
            if(tree->car) printLexeme(tree->car, stdout);
            else printf("no car\n");
            
            if(tree->cdr) printLexeme(tree->cdr, stdout);
            else printf("no cdr\n");*/
            return; //cons(INTEGER, tree->c)
            break;
        default:
            printf("unhandled statement in emval: \n");
            printLexeme(tree, stdout);
            //exit(-3);
    }
}