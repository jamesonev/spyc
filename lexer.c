/* This is the private implementation of lexer by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <stdlib.h> //for exit, malloc, 
#include <string.h> //strcmp
#include "lexer.h"
#include "custString.h"
#include "digit.h"

int lineNumber = 1;
extern FILE * fp;
string buffer;

int isWhiteSpace(char ch);
void skipWhiteSpace(FILE *fp);
void skipToNextline(FILE *fp);
void findBlockCommentEnd(FILE *fp);
int isSpecialChar(char ch);

//PUBLIC FUNCTION DEFINITIONS
lexeme *lex(){
    lexeme *item        = NULL;
    (void)newString(&buffer, 8);
    char *word;
    skipWhiteSpace(fp);
    char ch             = fgetc(fp);
    char peek;
    if(ch == '\"')
    {
        append(&buffer, ch);
        ch = fgetc(fp);
        while(ch != '\"')
        {   
            if(ch == EOF){
                fprintf(stdout, "ERROR: unterminated quote beginning on line %d\n", lineNumber);
                exit(-2);
            }
            append(&buffer, ch);
            ch = fgetc(fp);
        }
        append(&buffer, '\"');
        item = newLexeme(STRING, 0, getString(&buffer), 0);
        resetString(&buffer);
    }
    else if (isNum(ch, fp))
    {
        ungetc(ch, fp);
        item = getNum(fp);
    }
    else if (isSpecialChar(ch))
    {
        switch(ch){
            //GROUPINGS
            case '{':
                item = newLexeme(OBRACE, 0, NULL, 0);
                break;
            case '}':
                item = newLexeme(CBRACE, 0, NULL, 0);
                break;
            case '[':
                item = newLexeme(OBRACKET, 0, NULL, 0);
                break;
            case ']':
                item = newLexeme(CBRACKET, 0, NULL, 0);
                break;
            case '(':
                item = newLexeme(OPAREN, 0, NULL, 0);
                break;
            case ')':
                item = newLexeme(CPAREN, 0, NULL, 0);
                break;
            //OPERATORS
            case '=':
                peek = fgetc(fp);
                if(peek == '=')
                    item = newLexeme(EQUALS, 0, NULL, 0);
                else{
                    ungetc(peek, fp);
                    item = newLexeme(ASSIGN, 0, NULL, 0);
                }
                break;
            case '+':
                item = newLexeme(PLUS, 0, NULL, 0);
                break;
            case '-':
                item = newLexeme(MINUS, 0, NULL, 0);
                break;
            case '%':
                item = newLexeme(MOD, 0, NULL, 0);
                break;
            case '/':
                item = newLexeme(DIVIDE, 0, NULL, 0);
                break;
            case '*':
                item = newLexeme(MULTIPLY, 0, NULL, 0);
                break;
            case '&':
                item = newLexeme(AND, 0, NULL, 0);
                break;
            case '|':
                item = newLexeme(OR, 0, NULL, 0);
                break;
            //COMPARISONS
            case '>':
                item = newLexeme(GREATER_THAN, 0, NULL, 0);
                break;
            case '<':
                item = newLexeme(LESS_THAN, 0, NULL, 0);
                break;
            //MISC    
            case '.':
                item = newLexeme(DOT, 0, NULL, 0);
                break;
            case ',':
                item = newLexeme(COMMA, 0, NULL, 0);
                break;
            case EOF:
                item = newLexeme(ENDINPUT, 0, NULL, 0);
                break;
        }
    }
    else    //we are working with an unquoted string
    {
        while(ch != EOF && !isWhiteSpace(ch)){
            if(canAppend(ch)){
                append(&buffer, ch);
                ch = fgetc(fp);
            }
            else{
                ungetc(ch, fp);
                break;
            }
        }
        word = getString(&buffer);
        //check if word is a keyword
        if      (!strcmp(word, "while"))    item = newLexeme(WHILE, 0, NULL, 0);
        else if (!strcmp(word, "for"))      item = newLexeme(FOR_LOOP, 0, NULL, 0);
        else if (!strcmp(word, "if"))       item = newLexeme(IF, 0, NULL, 0);
        else if (!strcmp(word, "else"))     item = newLexeme(ELSE, 0, NULL, 0);
        //else if (!strcmp(word, "int"))      item = newLexeme(INTEGER_TYPE, 0, NULL, 0);
        //else if (!strcmp(word, "string"))   item = newLexeme(STRING, 0, NULL, 0);
        else if (!strcmp(word, "return"))   item = newLexeme(RETURN, 0, NULL, 0);
        else if (!strcmp(word, "print"))    item = newLexeme(PRINT, 0, NULL, 0);
        else if (!strcmp(word, "get"))      item = newLexeme(GET, 0, NULL, 0);        
        else if (!strcmp(word, "func"))     item = newLexeme(FUNCTION, 0, NULL, 0);
        else if (!strcmp(word, "obj"))      item = newLexeme(OBJDEF, 0, NULL, 0);
        else if (!strcmp(word, "lambda"))   item = newLexeme(LAMBDA, 0, NULL, 0);
        else                                item = newLexeme(ID, 0, word, 0);
        resetString(&buffer);
    }
    freeString(&buffer);
    return item;

}


//PRIVATE FUNCITON DEFINITIONS
int isWhiteSpace(char ch){
    switch(ch){
        case ' ': return 1;
        //these based on isspace() in ctype. docs: https://www.tutorialspoint.com/c_standard_library/c_function_isspace.htm
        case '\t': return 1;    //tab
        case '\n':
            lineNumber++;
            return 1;           //newline
        case '\v': return 1;    //vertical tab
        case '\f': return 1;    //feed
        case '\r':              //carriage return
            lineNumber++;
            return 1;    
        default: return 0;
    }
}
void skipWhiteSpace(FILE *fp){
    char ch             = fgetc(fp);
    while(ch != EOF){
        if(isWhiteSpace(ch))
            ch = fgetc(fp);
        //handle comments
        else if(ch == '/')
        {
            ch = fgetc(fp);
            if(ch == '/')
            {
                skipToNextline(fp);
                ch = fgetc(fp);
            }
            else if(ch == '*')
            {
                findBlockCommentEnd(fp);
                ch = fgetc(fp);
            }
            else
            {
                ungetc(ch, fp);
                ungetc('/', fp);
                return;
            }
        }
        else
        {
            ungetc(ch, fp);
            return;
        }
    }
}
void skipToNextline(FILE *fp){
    char ch             = fgetc(fp);
    while(ch != '\n')
    {
        ch = fgetc(fp);
    }
    lineNumber++;
    return;
}
void findBlockCommentEnd(FILE *fp){
    char ch             = fgetc(fp);
    while(ch != EOF)
    {
        if(ch == '\n') 
            lineNumber++;
        if(ch == '*')
        {
            ch = fgetc(fp);
            if(ch == '/')
                return;
        }
        else ch = fgetc(fp);
    }
    return;
}
int isSpecialChar(char ch){
    switch(ch){
        //GROUPINGS
        case '\"': return 1;
        case '{': return 1;
        case '}': return 1;
        case '[': return 1;
        case ']': return 1;
        case '(': return 1;
        case ')': return 1;
        //MATH
        case '+': return 1;
        case '-': return 1;
        case '%': return 1;
        case '/': return 1;
        case '*': return 1;
        //COMPARISONS
        case '>': return 1;
        case '<': return 1;
        case '=': return 1;
        case '&': return 1;
        case '|': return 1;
        //MISC    
        case '.': return 1;
        case ',': return 1;
        case EOF: return 1;
        default: return 0;
    }
}
