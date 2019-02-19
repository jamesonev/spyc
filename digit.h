/* This is the public implementation of number functions for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include "lexer.h"

#ifndef __DIGIT_INCLUDED__
#define __DIGIT_INCLUDED__

extern int isNum(char ch, FILE *fp);
extern lexeme *getNum(FILE *fp);

#endif