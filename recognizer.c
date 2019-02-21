#include <stdio.h>
#include <stdlib.h> //for exit
#include "lexer.h"
#include "lexeme.h"
#include "recognizer.h"

//GLOBALS
extern lexeme* current;
extern FILE *fp;
//PROMISES
lexeme* ifStatement();
lexeme* block();
int blockPending();
lexeme* optExpressionList();
lexeme* expressionList();
lexeme* expression();
int ifPending();
int statementPending();

void damn(const char* msg){
    printf("%s. ", msg);
    //printLexeme(current, stdout);
    printf("Error detected on line: %d\n", current->lineNo);
    exit(-2);
}

void advance(){
    current = lex(fp);
}

int check(enum lexTypes type){
    return current->type == type;
}

void matchNoAdvance(enum lexTypes type){
    if(!check(type)){
        printf("found: ");
        printLexeme(current, stdout);
        printf("expected: ");
        printType(type, stdout);
        printf("\n");
        damn("illegal");
    }
}

lexeme* match(enum lexTypes type){
    matchNoAdvance(type);
    lexeme* item = current;
    advance();
    //printLexeme(item, stdout);
    return item;
}

int varExpressionPending(){
    return check(ID);
}
lexeme* varExpression(){
    lexeme* i;
    lexeme* e;
    i = match(ID);
    if(check(OPAREN)){
        match(OPAREN);
        e = optExpressionList();
        match(CPAREN);
        return cons(FUNCCALL, i, e);
    }
    else if(check(OBRACKET)){
        match(OBRACKET);
        e = expressionList();
        match(CBRACKET);
        return cons(ARRAY, i, e);
    }
    return i;
}

int unaryPending(){
    return check(REAL) || check(INTEGER) || check(STRING) ||
            check(OBJDEF) || varExpressionPending();
}
lexeme* unary(){
    lexeme* item = NULL;
    if      (check(REAL))                item = match(REAL);
    else if (check(INTEGER))             item = match(INTEGER);
    else if (check(STRING))              item = match(STRING);
    else if (check(OBJDEF))              item = match(OBJDEF);
    else if (varExpressionPending())     item = varExpression();
    else {
        printf("found: ");
        printLexeme(current, stdout);
        printf("expected: ");
        printType(type, stdout);
        printf("\n");
        damn("illegal");
    }
    return item;
}

int operatorPending(){
    return check(ASSIGN) || check(PLUS) || check(MINUS) ||
            check(MULTIPLY) || check(DIVIDE) || check(MOD) ||
            check(EQUALS) || check(GREATER_THAN) || check(LESS_THAN) ||
            check(AND) || check(OR);
}
lexeme* operator(){
    lexeme* item = NULL;
    if(check(ASSIGN))               item = match(ASSIGN);
    else if(check(PLUS))            item = match(PLUS);
    else if(check(MINUS))           item = match(MINUS);
    else if(check(MULTIPLY))        item = match(MULTIPLY);
    else if(check(DIVIDE))          item = match(DIVIDE);
    else if(check(MOD))             item = match(MOD);
    else if(check(EQUALS))          item = match(EQUALS);
    else if(check(GREATER_THAN))    item = match(GREATER_THAN);
    else if(check(LESS_THAN))       item = match(LESS_THAN);
    else if(check(AND))             item = match(AND);
    else if(check(OR))              item = match(OR);
    else{
        printf("found: ");
        printLexeme(current, stdout);
        printf("expected: ");
        printType(type, stdout);
        printf("\n");
        damn("illegal");
    }
    //item is the match of one of the above
    return item;
}

int expressionPending(){
    return unaryPending();
}
lexeme* expression(){
    lexeme* u;
    lexeme* e;
    lexeme* o;
    u = unary();
    if(operatorPending()){
        o = operator();
        e = expression();
        return cons(o->type, u, e);
    } 
    return u;
}
lexeme* expressionList(){
    lexeme* e;
    lexeme* l = NULL;
    e = expression();
    if(check(COMMA)){
        match(COMMA);
        l = expressionList();
    }
    return cons(EXPRLIST, e, l);
}
lexeme* optExpressionList(){
    lexeme* e = NULL;
    if(expressionPending()) e = expressionList();
    return cons(OPTEXPRLIST, e, NULL);
}

int elsePending(){
    return check(ELSE);
}
lexeme* elseBlock(){
    lexeme* i = NULL;
    lexeme* b = NULL;
    match(ELSE);
    if(ifPending()){
        i = ifStatement();
    }
    else{
        b = block();
    }
    return cons(ELSE, i, b);
}
int ifPending(){
    return check(IF);
}
lexeme* ifStatement(){
    lexeme* ex;
    lexeme* b;
    lexeme* e = NULL;
    match(IF);
    match(OPAREN);
    ex = expression();
    match(CPAREN);
    b = block();
    if(elsePending()) e = elseBlock();
    return cons(IF, ex, cons(IFGLUE, b, e));
}

int whilePending(){
    return check(WHILE);
}
lexeme* whileStatement(){
    lexeme* e;
    lexeme* b;
    match(WHILE);
    match(OPAREN);
    e = expression();
    match(CPAREN);
    b = block();
    return cons(WHILE, e, b);
}

int objectDefPending(){
    return check(OBJDEF);
}
lexeme* objectDef(){
    lexeme* i;
    lexeme* e;
    match(OBJDEF);
    i = match(ID);
    match(OBRACE);
    e = expressionList();
    match(CBRACE);
    return cons(OBJDEF, i, e);
}
int functionDefPending(){
    return check(FUNCTION);
}
lexeme* functionDef(){
    lexeme* b;
    lexeme* i;
    lexeme* o;
    match(FUNCTION);
    i = match(ID);
    match(OPAREN);
    o = optExpressionList();
    match(CPAREN);
    b = block();
    return cons(FUNCDEF, i, cons(GLUE, o, b));
}
int defPending(){
    return functionDefPending() || objectDefPending();
}
lexeme* definition(){
    lexeme* item = NULL;
    if (objectDefPending())             item = objectDef();
    else if (functionDefPending())      item = functionDef();
    else {
        printf("found: \n");
        printLexeme(current, stdout);
        printf("expected: ");
        printType(type, stdout);
        printf("\n");
        damn("illegal");
    }
    //item is FUNCDEF or OBJDEF
    return item;
}
lexeme* defList(){
    lexeme* d;
    lexeme* l = NULL;
    d = definition();
    if (defPending())   l = defList();
    return cons(DEFLIST, d, l);
}

int returnPending(){
    return check(RETURN);
}
lexeme* returnStatement(){
    lexeme* e = NULL;
    match(RETURN);
    if (expressionPending()) e = expression();
    return cons(RETURN, e, NULL);
}

int statementPending(){
    return expressionPending() || ifPending() || whilePending() ||
            defPending() || returnPending();
}
lexeme* statement(){
    lexeme* item = NULL;
    if      (defPending())              item = defList();
    else if (ifPending())               item = ifStatement();
    else if (whilePending())            item = whileStatement();
    else if (returnPending())           item = returnStatement();
    else if (expressionPending())       item = expression();
    else{
        printf("found: ");
        printLexeme(current, stdout);
        printf("expected: "); 
        printType(type, stdout);
        printf("\n");
        damn("illegal");
    }
    return item;
}

lexeme* statements(){
    lexeme* s;
    lexeme* p = NULL;
    s = statement();
    if (statementPending()){
        p = statements();
    }
    return cons(STATEMENTS, s, p);
}

int blockPending(){
    return check(OBRACE);
}

lexeme* block(){
    match(OBRACE);
    lexeme* tree = statements();
    match(CBRACE);
    return cons(BLOCK, tree, NULL);
}

lexeme* program(){
    return statements();
}

