/* This is the public implementation of the evaluator for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include "lexeme.h"

#ifndef __EVAL_INCLUDED__
#define __EVAL_INCLUDED__

extern lexeme* eval(lexeme* tree, lexeme* env);

#endif