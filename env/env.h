/* This is the public implementation of the environment for Spyc by Jameson Evans, jtevans3@crimson.ua.edu 
for CS403, spring 2019
*/
#include <stdio.h>
#include <string.h>
#include "../lexeme.h"
#ifndef __ENV_INCLUDED__
#define __ENV_INCLUDED__


extern lexeme *newEnv();
extern lexeme *init(lexeme *env);
extern lexeme *extend(lexeme *env, lexeme* k, lexeme* v);
extern lexeme *insert(lexeme *env, lexeme *k, lexeme *v);
extern lexeme *lookup(lexeme *env, lexeme *k);
extern lexeme *update(lexeme *env, lexeme *k, lexeme *v);
extern void displayLocalEnv(lexeme *env);
extern void displayAllEnv(lexeme *env);

#endif
