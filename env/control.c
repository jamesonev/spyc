#include <stdio.h>
#include <stdlib.h> //for exit
#include "../lexeme.h"
#include "env.h"

lexeme *current;
int lineNumber = 0;

int main(int argc, char const *argv[])
{
    lexeme *v;
    lexeme *k;
    (void)argc;     //remove compile warning
    (void)argv[0];
    lexeme *env = newEnv();
    current = k = newLexeme(ID, 0, "x", 0);
    v = newLexeme(STRING, 5, "mammamia", 0);
    insertEnv(env, k, v);
    k = newLexeme(ID, 0, "y", 0);
    v = newLexeme(INTEGER, 12, NULL, 0);
    insertEnv(env, k, v);
    k = newLexeme(ID, 0, "z", 0);
    v = newLexeme(INTEGER, 35, NULL, 0);
    lexeme *env2 = extend(env,k,v);
    printLexeme(getVal(env2, current), stdout);
    //updateVal(env2, current, newLexeme(INTEGER, 1000, NULL, 0));
    //printLexeme(getVal(env, current), stdout);
    printf("displaying environments\n");
    displayAllEnv(env2);
    return 0;
}
