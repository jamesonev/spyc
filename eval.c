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
    printf("eval.evalMultiply\n");
    lexeme* lhs = eval(tree->car, env);
    printLexeme(lhs, stdout);
    lexeme* rhs = eval(tree->cdr, env);
    printLexeme(lhs, stdout);
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

lexeme* evalLessThan(lexeme* tree, lexeme* env){
    lexeme* lhs = eval(tree->car, env);
    //printf("lhs\n");
   // printLexeme(lhs, stdout);
    lexeme* rhs = eval(tree->cdr, env);
    //printf("rhs\n");
    //printLexeme(rhs, stdout);
    if( (lhs->type == INTEGER || lhs->type == REAL) && 
        (rhs->type == INTEGER || rhs->type == REAL) ){
        double l = lhs->intVal + lhs->realNumVal;
        double r = rhs->intVal + rhs->realNumVal;
        if(l < r)   return cons(TRUELEX, NULL, NULL);
        else        return cons(FALSELEX, NULL, NULL);
    }
    /*if(lhs->type == STRING && rhs->type == STRING){

        if( !strcmp(lhs->stringVal, rhs->stringVal) )
            return cons(TRUELEX, NULL, NULL);
        else
            return cons(FALSELEX, NULL, NULL);
    }*/
    printf("called LESS_THAN with illegal args: \n");
    printLexeme(lhs, stdout);
    printLexeme(rhs, stdout);
    exit(-3);
    return NULL;
}

lexeme* evalGreaterThan(lexeme* tree, lexeme* env){
    printf("evalGreaterThan\n");
    lexeme* lhs = eval(tree->car, env);
    //printf("lhs\n");
   // printLexeme(lhs, stdout);
    lexeme* rhs = eval(tree->cdr, env);
    //printf("rhs\n");
    //printLexeme(rhs, stdout);
    if( (lhs->type == INTEGER || lhs->type == REAL) && 
        (rhs->type == INTEGER || rhs->type == REAL) ){
        double l = lhs->intVal + lhs->realNumVal;
        double r = rhs->intVal + rhs->realNumVal;
        if(l < r)   return cons(FALSELEX, NULL, NULL);
        else        return cons(TRUELEX, NULL, NULL);
    }
    /*if(lhs->type == STRING && rhs->type == STRING){

        if( !strcmp(lhs->stringVal, rhs->stringVal) )
            return cons(TRUELEX, NULL, NULL);
        else
            return cons(FALSELEX, NULL, NULL);
    }*/
    printf("called GREATER_THAN with illegal args: \n");
    printLexeme(lhs, stdout);
    printLexeme(rhs, stdout);
    exit(-3);
    return NULL;
}

lexeme* evalExprToBool(lexeme* tree, lexeme* env){
    lexeme* expr = eval(tree, env);
    printf("evalExprToBool\n");
    printLexeme(expr, stdout);
    if(expr->type == TRUELEX || expr->type == FALSELEX)
        return expr;
    if( expr->type == INTEGER && (expr->intVal != 0) )
        return cons(TRUELEX, NULL, NULL);
    if( expr->type == REAL &&
        (expr->realNumVal < .00001 && expr->realNumVal > -.00001) )
        return cons(TRUELEX, NULL, NULL);
    return cons(FALSELEX, NULL, NULL);
}

int isTrue(lexeme* tree, lexeme* env){
    switch(tree->type){
        case INTEGER:   return tree->intVal;
        case REAL:      return (int) tree->realNumVal;
        default:        return 0;
    }
}

lexeme* evalStruct(lexeme* tree, lexeme* env){
    return insert(env, car(tree), cdr(tree) );
}

lexeme* evalFuncCall(lexeme* tree, lexeme* env){
    printf("evalFuncCall\n");
    lexeme* clos = eval(car(tree), env );   //looks up func def
    lexeme* args = cdr(tree);               //evaluates optexprlist of args
    lexeme* params = eval(car(cdr(cdr(clos))), env);
    printf("params\n");
    lexeme* body = cdr(cdr(cdr(clos)));
    //printLexeme(body, stdout);
    lexeme* defenv = car(clos);
    //displayLocalEnv(defenv);
    lexeme* evalargs = eval(args, env); //evalargs must be left leaning
    lexeme* newenv = extend(defenv, params, evalargs);
    insert(newenv, car(tree), clos);
    displayLocalEnv(newenv);
    return eval(body, newenv);
}

lexeme* evalOptParamList(lexeme* tree, lexeme* env){
    (void)env;  
    lexeme* expl;
    lexeme* returner;
    expl = tree = car(tree);           //gets to expressionlist
    if(!tree)   return tree;
    returner = tree = car(expl);
    while(expl){
        expl = cdr(expl);
        tree->car = car(expl);
        tree = car(tree);
    }
    return returner;
}

lexeme* evalLambda(lexeme* tree, lexeme* env){
    return cons(CLOSURE, env, tree);
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
        case LAMBDA:        return evalLambda(env, tree);
//operators
        case PLUS:          return evalAdd(tree, env);
        case MINUS:         return evalMinus(tree, env);
        case MULTIPLY:      return evalMultiply(tree, env);
        case ASSIGN:        return insert(env, car(tree), eval(cdr(tree),env) );
//sets of statements
        case OPTEXPRLIST:
            if(car(tree))
                return eval(car(tree), env);
            return NULL;
        case OPTPARAMLIST:
            return evalOptParamList(tree, env);
        case EXPRLIST:
            l = eval(tree->car, env);   //returns eval'd expr
            if(tree->cdr) l->car = eval(tree->cdr, env);
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
            l = insert(env, car(tree), cons(CLOSURE, env, tree) );
            //displayLocalEnv(env);
            return l;
        case FUNCCALL:
            return evalFuncCall(tree, env);
        case CLOSURE:       return tree;
        case GLUE:          return tree;
        case OBJDEF:        return evalStruct(tree, env);
        case RETURN:        return tree;
//conditionals
        case WHILE:
            while( evalExprToBool(tree->car, env)->type == TRUELEX){
                l = eval(tree->cdr, env);
            }
            return l;
        case IF:
            if(eval(car(tree), env))
                return eval(car(cdr(tree)), env);
            else
                return eval(cdr(cdr(tree)), env);
            /*if( evalExprToBool(tree->car, env)->type == TRUELEX)
                return eval(car(cdr(tree)), env);
            else
                return eval(cdr(cdr(tree)), env);*/
        case ELSE:
            if(tree->car)   
                return eval(tree->car, env);
            return eval(tree->cdr, env);

//comparisons
        case LESS_THAN:
            return evalLessThan(tree, env);
        case GREATER_THAN:
            return evalGreaterThan(tree, env);
        case TRUELEX:
            return tree;
        default:
            printf("unhandled statement in eval: \n");
            printLexeme(tree, stdout);
            exit(-3);
    }
}
