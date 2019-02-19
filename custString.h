#include <stdio.h>

#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

typedef struct string
{
    char* ptr;
    int strlen;
    int size;
} string;

extern string *newString(string* s, int len);
extern char *getString(string *s);
extern int getStrlen(string *s);
extern string *append(string *s, char ch);
extern int canAppend(char ch);
extern void freeString(string *s);
extern void resetString(string *s);
#endif
