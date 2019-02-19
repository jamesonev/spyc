#include <stdio.h>
#include <stdlib.h> //for exit
#include "lexeme.h"
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
    printf("creating environment\ninserting x and y\n");
    k = newLexeme(ID, 0, "x", 0);
    v = newLexeme(INTEGER, 5, NULL, 0);
    insertEnv(env, k, v);
    current = k = newLexeme(ID, 0, "y", 0);
    v = newLexeme(INTEGER, 12, NULL, 0);
    insertEnv(env, k, v);
    printf("extending environment\nprinting newEnv\n");
    lexeme *env2 = extend(env);
    displayLocalEnv(env2);
    printf("inserting z to the original env\nprinting originalenv\n");
    k = newLexeme(ID, 0, "z", 0);
    v = newLexeme(INTEGER, 44, NULL, 0);
    insertEnv(env, k, v);
    displayLocalEnv(env);
    printf("the extended env is unchanged:\n");
    displayLocalEnv(env2);
    printf("updating y in the extended env:\n");
    updateVal(env2, current, newLexeme(INTEGER, 1000, NULL, 0));
    displayLocalEnv(env2);
    //printLexeme(getVal(env, current), stdout);
    printf("displaying all environments\n");
    displayAllEnv(env);
    return 0;
}
