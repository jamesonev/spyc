/* This is the private implementation of lexeme by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <stdlib.h> //for exit, malloc, 
#include "lexeme.h"
#include "string.h"

extern int lineNumber;

lexeme *newLexeme(enum lexTypes type, int ival, char * sval, double rval){
    lexeme *item = malloc(sizeof(lexeme));
    int temp = lineNumber;
    if (item == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    item->type = type;
    if(sval){
        item->stringVal = malloc(sizeof(sval));
        if (item->stringVal == 0)
            {
                fprintf(stderr,"out of memory");
                exit(-1);
            }
        strcpy(item->stringVal, sval);
    }
    else item->stringVal = NULL;
    item->intVal = ival;
    item->realNumVal = rval;
    item->lineNo = temp;
    item->car = NULL;
    item->cdr = NULL;
    return item;
}

lexeme *cons(enum lexTypes type, lexeme *car, lexeme *cdr){
    lexeme *item = malloc(sizeof(lexeme));
    if (item == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    item->type = type;
    item->stringVal = NULL;
    item->intVal = item->lineNo = item->realNumVal = 0;
    item->car = car;
    item->cdr = cdr;
    return item;
}

void deleteLexeme(lexeme *item){
    if(item->stringVal) free(item->stringVal);
    free(item);
}
void printType(enum lexTypes type, FILE *fp){
    const char* printLexTypes[]= {
        //UNARY
        "UNARY",
        "REAL",
        "INTEGER",
        "VARIABLE",
        "PARENEXP",
        "ID",
        "STRING",   //remove?
        "LAMBDA",
        //OPERATORS
        "OPERATOR",
        "ASSIGN",
        "PLUS",
        "MINUS",
        "MULTIPLY",
        "DIVIDE",
        "MOD",
        "AND",
        "OR",
        //KEYWORDS
        "WHILE",
        "FOR_LOOP",
        "IF",
        "ELSE",
        "PROGRAM",
        "BLOCK",
        "STATEMENTS",
        "STATEMENT",
        "DEFLIST",
        "RETURN",
        "RETURNED",
        "FUNCTION",
        "FUNCCALL",
        "FUNCDEF",
        "OBJDEF",
        "ARRAY",
        "PRINT",
        "GET",
        "EXPRESSION",
        "EXPRLIST",
        "OPTEXPRLIST",
        "OPTPARAMLIST",
        "EVALDARGS",
        "ENV",
        "CLOSURE",
        "TABLE",
        "IDLIST",
        "GLUE",
        "IFGLUE",
        //SPECIAL CHARS
        "OBRACE",
        "CBRACE",
        "OBRACKET",
        "CBRACKET",
        "OPAREN",
        "CPAREN",
        "COMMA",
        "DOT",
        "ENDofINPUT",
        //COMPARISONS
        "GREATER_THAN",
        "LESS_THAN",
        "EQUALS",
        "TRUELEX",
        "FALSELEX",
    };
    fprintf(fp, "%s ", printLexTypes[type]);
}
void printLexeme(lexeme *item, FILE *fp){
    if(!item) return;
    printType(item->type, fp);
    if      (item->type == INTEGER)     fprintf(fp, "%d\n", item->intVal);
    else if (item->stringVal)           fprintf(fp, "%s\n", item->stringVal);
    else if (item->type == REAL)        fprintf(fp, "%f\n", item->realNumVal);
    else                                fprintf(fp, "\n");
    //fprintf(fp, "\t\torigin: %d\n", item->lineNo);
}

lexeme *car(lexeme *tree){
    if(!tree){      //avoids segfault from accessing null->car
        return NULL;
    }
    return tree->car;
}
lexeme *cdr(lexeme *tree){
    if(!tree){      //avoids segfault from accessing null->car
        return NULL;
    }
    return tree->cdr;
}
