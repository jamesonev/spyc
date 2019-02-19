#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lexeme.h"
#include "env.h"

//2 linked lists, 1 w var names, 1 with var values
//extend joins them into a new environent by calling
//cons w/ the linked lists, then consing that new env
//with the previous env
//env=newEnv()
//lexeme with car(Table), cdr(NULL)

lexeme *newEnv(){
    return cons(ENV, NULL, cons(ENV, NULL, NULL));
}
lexeme *init(lexeme* env){
    //TODO: seed top level env with builtin functions
    return env;
}

lexeme *extend(lexeme *env, lexeme* k, lexeme* v){
    return cons(ENV, k, cons(ENV, v, env));
}

lexeme *insertEnv(lexeme *env, lexeme *k, lexeme *v){
    //insert k at top of top list
    k->car =car(env);
    env->car = k;
    //move on to v
    env = cdr(env);
    v->car = car(env);
    env->car = v;
    return v;
}
lexeme *getVal(lexeme *env, lexeme *k){
    lexeme *key;
    lexeme *value;
    while(env){
        key = car(env);
        value = car(cdr(env));
        while(key){
            if (!strcmp(k->stringVal, key->stringVal)) return value;
            key = car(key);
            value = car(value);
        }
        env = cdr(cdr(env));
    }
    printf("ERROR: attempt to get a nonexistant ID\n");
    exit(-1);
    return NULL;
}
lexeme *updateVal(lexeme *env, lexeme *k, lexeme *v){
    lexeme *key;
    lexeme *vPtr;   //points to the lexeme in front of the correct value
    while(env){
        key = car(env);
        vPtr = cdr(env);
        while(key){
            if(!strcmp(k->stringVal, key->stringVal)){
                v->car = car(vPtr);
                vPtr->car = v;
                return v;
            }
            key = car(key);
            vPtr = car(vPtr);
        }
        env = cdr(cdr(env));
    }
    printf("ERROR: attempt to update an undefined ID\n");
    exit(-1);
    return NULL;
}
void displayLocalEnv(lexeme *env){
    fprintf(stdout, "-----------ENVIRONMENT----------\n");
    lexeme *k = car(env);       //table
    lexeme *v = car(cdr(env));  //first v in table
    while(k){
        printLexeme(k, stdout);
        printLexeme(v, stdout);
        k = car(k);
        v = car(v);
    }
}
void displayAllEnv(lexeme *env){
    while(env){
        displayLocalEnv(env);
        env = cdr(cdr(env));
    }
}

/*
//THIS PART IS EVALUATING
//all eval calls return lexeme
//cons returns new lexeme
evalFuncDef(tree, env){
    insertEnv(env, tree->car), cons(CLOSURE, env, tree));
}

eval(tree, env){
    if(tree->type == iNTEGER)
        return tree
    if(tree->type == STRING)
        return tree
    if(tree->type == ID)
        return getValfromEnv(env, tree);
    if(tree->type == FUNCTIONDEF){
        return evalFuncDef(tree, env);
    }
}*/
