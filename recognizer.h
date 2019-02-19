/* This is the public implementation of the recognizer for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include "lexeme.h"
#include "lexer.h"
#ifndef __RECOGNIZER_INCLUDED__
#define __RECOGNIZER_INCLUDED__

extern lexeme *program();
extern void advance();
#endif