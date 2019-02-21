#include <stdio.h>
#include <stdlib.h> //for exit
#include "lexer.h"
#include "lexeme.h"
#include "recognizer.h"
#include "printer.h"
#include "env/env.h"
#include "eval.h"

lexeme *current;
FILE *fp;

int main(int argc, char const *argv[])
{
    (void)argc;     //removec compile warning
    fp       = fopen(argv[1], "r");
    if(!fp){
        fprintf(stdout, "ERROR: failed to open file %s\n", argv[1]);
        exit(-1);
    }
    advance();
    //run with testcase.spc -l to print all the lexemes
    if(argv[2] && !strcmp(argv[2], "-l")){
        while(!feof(fp)){
            printLexeme(current, stdout);
            advance();
        }
        fclose(fp);
        return 0;
    }
    lexeme *prog = program();
    if(argv[2] && !strcmp(argv[2], "-pp")){
        pp(prog);
        
        return 0;
    }
    
    lexeme *env = newEnv();
    prog = eval(prog, env);
    //printf("success\n");
    ///displayAllEnv(env);
    printLexeme(prog, stdout);
    //displayAllEnv(env);
    fclose(fp);
    return 0;
}
