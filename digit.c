/* This is the private implementation of number functions by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <stdlib.h> //for exit
#include <ctype.h>  //isspace
#include "digit.h"
#include "lexer.h"

extern int lineNumber;
//PRIVATE
int isDigit(char ch){
    if (ch <= 57 && ch >= 48)    return 1;
    return 0;
}

//PUBLIC
int isNum(char ch, FILE *fp){
    if(isDigit(ch))             return 1;
    char peek = fgetc(fp);
    if (ch == '.' ){
        if(isDigit(peek)){
                                ungetc(peek, fp);
                                return 1;
        }
        else{                   
                                ungetc(peek, fp);
                                return 0;       
        }
    }
    if (ch == '-' )
    {
        if(isDigit(peek)){
                                ungetc(peek, fp);
                                return 1;
        }
        else if (peek == '.')
        {
                                peek = fgetc(fp);
            if(isDigit(peek)){
                                ungetc(peek, fp);
                                ungetc('.', fp);
                                return 1;
            }
        }
        else{
                                ungetc(peek, fp);
                                return 0;
        }
    }
    ungetc(peek, fp);
    return 0;
}

lexeme *getNum(FILE *fp){
    lexeme *item;
    char ch             = fgetc(fp);
    char buffer[16];
    int i               = 0;
    double d            = 0;
    int point           = 0;
    if (ch == '-')
    {  
        buffer[i] = ch;
        i++;
        ch = fgetc(fp);
    }
    while(isDigit(ch) || ch == '.'){
        if (ch == '.'){          
            if(!point)  point = 1;
            else{
                        fprintf(stdout, "ERROR: invalid number on line %d (multiple decimals)\n", lineNumber);
                        exit(-2);
            }
        }
        buffer[i] = ch;
        i++;
        if(i==16){
                        fprintf(stdout, "ERROR: num on line %d caused overflow\n", lineNumber);
                        exit(-2);
        }
        ch = fgetc(fp);
    }
    ungetc(ch, fp);
    if(!point){
                        //thanks to Penelope: https://stackoverflow.com/questions/10204471/convert-char-array-to-a-int-number-in-c
                        sscanf(buffer, "%d", &i);
                        item = newLexeme(INTEGER, i, NULL, 0);
    }
    else{
                        sscanf(buffer, "%lf", &d);
                        item = newLexeme(REAL, 0, NULL, d);
    }
    return item;
}


