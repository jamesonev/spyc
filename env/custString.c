#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custString.h"

//private
char *growString(char *p, int size){
    char *new = realloc(p, size*2*sizeof(char));
    if (new == 0)
    {
        fprintf(stdout, "out of memory\n");
        exit(-1);
    }
    return new;
}
//PUBLIC
string *newString(string *s, int len){
    s->ptr = malloc(sizeof(char)*len);
    if (s->ptr == 0)
    {
        fprintf(stdout, "out of memory\n");
        exit(-1);
    }
    s->strlen = 0;
    s->size = len;
    return s;
}

string *append(string *s, char ch){
    s->ptr[s->strlen] = ch;
    s->ptr[s->strlen+1] = '\0';
    s->strlen++;
    if(s->strlen+1 == s->size){
        s->ptr = growString(s->ptr, s->size);
        s->size*=2;
    }
    return s;
}
int canAppend(char ch){

    if (ch >= 65 && ch <= 90)       return 1;
    if (ch >= 97 && ch <= 122)      return 1;
    if (ch >= 48 && ch <= 57)       return 1;
    switch(ch){
        case '_': return 1;
        case '-': return 1;
        case '>': return 1;
        case '.': return 1;
    }
    return 0;
}

int getStrlen(string *v){
    return v->strlen;
}

char *getString(string *v){
    return v->ptr;
}

void freeString(string *s){
    free(s->ptr);
    s->ptr = NULL;
    s->size = 0;
    s->strlen = 0;
}

void resetString(string *s){
    s->ptr[0] = '\0';
    s->strlen = 0;
}
