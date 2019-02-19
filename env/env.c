#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme.h"
#include "env.h"

//2 linked lists, 1 w var names, 1 with var values
//extend joins them into a new environent by calling
//cons w/ the linked lists, then consing that new env
//with the previous env
//env=newEnv()
//lexeme with car(Table), cdr(NULL)

lexeme *newEnv(){
    lexeme *item = newLexeme(ENVIRONMENT, 0, NULL, 0);
    item->car = newLexeme(TABLE, 0, NULL, 0);
    return item;
}

lexeme *copyTable(lexeme *k, lexeme *v, lexeme *destEnv){
    if(k->car) copyTable(car(k), cdr(v), destEnv);
    return insertEnv(destEnv, k, v);
}

lexeme *extend(lexeme *callingEnv){
    lexeme *item = newEnv();
    copyTable(car(car(callingEnv)), cdr(car(callingEnv)), item);
    callingEnv->cdr = item;
    return item;
}

lexeme *insertEnv(lexeme *env, lexeme *k, lexeme *v){
    k->car = car(car(env));
    v->cdr = cdr(car(env));
    env->car->car = k;
    env->car->cdr = v;
    return v;
}
lexeme *getVal(lexeme *env, lexeme *k){
    lexeme *key = car(car(env));
    lexeme *value = cdr(car(env));
    while(key){
        if (!strcmp(k->stringVal, key->stringVal)) break;
        key = car(key);
        value = cdr(value);
    }
    return value;
}
lexeme *updateVal(lexeme *env, lexeme *k, lexeme *v){
    lexeme *key = car(car(env));
    lexeme *value = car(env);
    while(key){
        if (!strcmp(k->stringVal, key->stringVal)){
            v->cdr = cdr(cdr(value));
            value->cdr = v;
            return v;
        }
        key = car(key);
        value = cdr(value);
    }
    printf("ERROR: attempt to update an unknown ID\n");
    exit(-1);
}
void displayLocalEnv(lexeme *env){
    fprintf(stdout, "-----------ENVIRONMENT----------\n");
    lexeme *k = car(car(env)); //table
    lexeme *v = cdr(car(env));  //first v in table
    while(k){
        printLexeme(k, stdout);
        printLexeme(v, stdout);
        k = car(k);
        v = cdr(v);
    }
}
void displayAllEnv(lexeme *env){
    lexeme *current = env;
    while(current){
        displayLocalEnv(current);
        current = cdr(current);
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
}


int main(int argc, char const *argv[])
{
    env = newEnv()
    tree = parse(fp)
    eval(tree, env);
    return 0;
}*/
