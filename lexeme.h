/* This is the public implementation of lexeme for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#ifndef __LEXEME_INCLUDED__
#define __LEXEME_INCLUDED__

enum lexTypes   //ALSO UPDATE PRINTLEXEME() IN LEXEME.C
{
    //UNARY
    UNARY,
    REAL,
    INTEGER,
    VARIABLE,
    PARENEXP,
    ID,
    STRING,
    LAMBDA,
    //OPERATORS
    OPERATOR,
    ASSIGN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    AND,
    OR,
    //KEYWORDS
    WHILE,
    FOR_LOOP,
    IF,
    ELSE,
    PROGRAM,
    BLOCK,
    STATEMENTS,
    STATEMENT,
    DEFLIST,
    RETURN,
    RETURNED,
    FUNCTION,
    FUNCCALL,
    FUNCDEF,
    OBJDEF,
    ARRAY,
    PRINT,
    GET,
    EXPRESSION,
    EXPRLIST,
    OPTEXPRLIST,
    OPTPARAMLIST,
    EVALDARGS,
    ENV,
    CLOSURE,
    TABLE,
    IDLIST,
    GLUE,
    IFGLUE,
    //SPECIAL CHARS
    OBRACE,
    CBRACE,
    OBRACKET,
    CBRACKET,
    OPAREN,
    CPAREN,
    COMMA,
    DOT,
    ENDINPUT,
    //COMPARISONS
    GREATER_THAN,
    LESS_THAN,
    EQUALS,
    TRUELEX,
    FALSELEX,
}type;

typedef struct lexeme
{
    enum lexTypes type;
    char* stringVal;
    int intVal;
    int lineNo;
    double realNumVal;
    struct lexeme *car;
    struct lexeme *cdr;
} lexeme;

extern struct lexeme *newLexeme(enum lexTypes type, int ival, char * sval, double rval);
extern struct lexeme *cons(enum lexTypes type, lexeme *car, lexeme *cdr);
extern void deleteLexeme(lexeme *item);
extern void printLexeme(lexeme *item, FILE *fp);
extern void printType(enum lexTypes type, FILE *fp);
extern lexeme *car(lexeme *tree);
extern lexeme *cdr(lexeme *tree);
#endif