/* This is the private implementation of the evaluator for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme.h"
#include "eval.h"
#include "env/env.h"

lexeme* evalMinus(lexeme* tree, lexeme* env){
    lexeme* lhs = eval(tree->car, env);
    lexeme* rhs = eval(tree->cdr, env);
    if(lhs->type == INTEGER && rhs->type == INTEGER)
        return newLexeme(INTEGER, lhs->intVal - rhs->intVal, NULL, 0);
    if(lhs->type == REAL && rhs->type == REAL)
        return newLexeme(REAL, 0, NULL, lhs->realNumVal - rhs->realNumVal);
    if(lhs->type == INTEGER && rhs->type == REAL)
        return newLexeme(REAL, 0, NULL, (double)lhs->intVal - rhs->realNumVal);
    if(lhs->type == REAL && rhs->type == INTEGER)
        return newLexeme(REAL, 0, NULL, lhs->realNumVal - (double)rhs->intVal);
    printf("called MINUS with illegal args: \n");
    printLexeme(lhs, stdout);
    printLexeme(rhs, stdout);
    exit(-3);
    return NULL;
}

lexeme* evalAdd(lexeme* tree, lexeme* env){
    lexeme* lhs = eval(tree->car, env);
    lexeme* rhs = eval(tree->cdr, env);
    if(lhs->type == INTEGER && rhs->type == INTEGER)
        return newLexeme(INTEGER, lhs->intVal + rhs->intVal, NULL, 0);
    if(lhs->type == REAL && rhs->type == REAL)
        return newLexeme(REAL, 0, NULL, lhs->realNumVal + rhs->realNumVal);
    if(lhs->type == INTEGER && rhs->type == REAL)
        return newLexeme(REAL, 0, NULL, (double)lhs->intVal + rhs->realNumVal);
    if(lhs->type == REAL && rhs->type == INTEGER)
        return newLexeme(REAL, 0, NULL, lhs->realNumVal + (double)rhs->intVal);
    printf("called PLUS with illegal args: \n");
    printLexeme(lhs, stdout);
    printLexeme(rhs, stdout);
    exit(-3);
    return NULL;
}

lexeme* evalMultiply(lexeme* tree, lexeme* env){
    lexeme* lhs = eval(tree->car, env);
    lexeme* rhs = eval(tree->cdr, env);
    if(lhs->type == INTEGER && rhs->type == INTEGER)
        return newLexeme(INTEGER, lhs->intVal * rhs->intVal, NULL, 0);
    if(lhs->type == REAL && rhs->type == REAL)
        return newLexeme(REAL, 0, NULL, lhs->realNumVal * rhs->realNumVal);
    if(lhs->type == INTEGER && rhs->type == REAL)
        return newLexeme(REAL, 0, NULL, (double)lhs->intVal * rhs->realNumVal);
    if(lhs->type == REAL && rhs->type == INTEGER)
        return newLexeme(REAL, 0, NULL, lhs->realNumVal * (double)rhs->intVal);
    printf("called MULTIPLY with illegal args: \n");
    printLexeme(lhs, stdout);
    printLexeme(rhs, stdout);
    exit(-3);
    return NULL;
}

lexeme* evalStruct(lexeme* tree, lexeme* env){
    return insert(env, car(tree), cdr(tree) );
}

lexeme* evalFuncCall(lexeme* tree, lexeme* env){
    lexeme* clos = eval(car(tree), env );   //looks up func def
    lexeme* args = eval(cdr(tree), env);    //evaluates optexprlist of args
    lexeme* params = car(cdr(cdr(clos)));   
    //printLexeme(params, stdout);
    lexeme* body = cdr(cdr(cdr(clos)));
    //printLexeme(body, stdout);
    lexeme* defenv = car(clos);
    //displayLocalEnv(defenv);
    lexeme* evalargs = eval(args, env);
    lexeme* newenv = extend(defenv, params, evalargs);
    displayLocalEnv(newenv);
    return eval(body, newenv);
}

lexeme* eval(lexeme* tree, lexeme* env){
    if(!tree)   return tree;
    lexeme* l = NULL;
    /*printf("\t");
    printLexeme(tree, stdout);
    if (tree->car)
    {
        printLexeme(tree->car, stdout);
    }
    if(tree->cdr){
        printf("\t\t");
        printLexeme(tree->cdr, stdout);
    }*/
    switch(tree->type){
//unary     
        case INTEGER:       return tree;
        case REAL:          return tree;
        case STRING:        return tree;
        case ID:            return lookup(env, tree);
//operators
        case PLUS:          return evalAdd(tree, env);
        case MINUS:         return evalMinus(tree, env);
        case MULTIPLY:      return evalMultiply(tree, env);
        case ASSIGN:        return insert(env, car(tree), eval(cdr(tree),env) );
//sets of statements
        case OPTEXPRLIST:
            if(cdr(tree))
                return eval(cdr(tree), env);
            return NULL;
        case EXPRLIST:
            l = eval(tree->car, env);   //returns eval'd expr
            if(tree->cdr) return cons(EVALDARGS, l, eval(tree->cdr, env) );
            return l;
        case STATEMENTS:
            l = eval(tree->car, env);
            if(tree->cdr) l = eval(tree->cdr, env);
            return l;
        case STATEMENT:     return eval(tree->car, env);
        case BLOCK:         return eval(tree->car, env);
        case DEFLIST:
            l = eval(tree->car, env);
            if(tree->cdr) l = eval(tree->cdr, env);
            return l;
//funcs/objs
        case FUNCDEF:
            return insert(env, car(tree), cons(CLOSURE, env, tree) );
        case FUNCCALL:
            return evalFuncCall(tree, env);
        case CLOSURE:       return tree;
        case GLUE:          return tree;
        case OBJDEF:        return evalStruct(tree, env);
//conditionals
        case WHILE:
            while(eval(tree->car, env)){
                l = eval(tree->cdr, env);
            }
            return l;
        default:
            printf("unhandled statement in eval: \n");
            printLexeme(tree, stdout);
            exit(-3);
    }
}
