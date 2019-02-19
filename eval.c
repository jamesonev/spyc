/* This is the private implementation of the evaluator for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme.h"
#include "eval.h"

void eval(lexeme* tree){
    switch(tree->type){
        case WHILE:
            break;
        default:
            printf("unhandled statement in eval: \n");
            printLexeme(tree, stdout);
            exit(-3);
    }
}