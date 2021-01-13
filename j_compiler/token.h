/*
 * token.h
 */

#define MAX_TOKEN_LENGTH 250

#include <stdio.h>
#include "stack.h"

typedef struct {
  enum { DEFUN, IDENT, RETURN, 
         PLUS, MINUS, MUL, DIV, MOD, 
         AND, OR, NOT, 
         LT, LE, EQ, GE, GT,
         IF, ELSE, ENDIF, 
         DROP, DUP, SWAP, ROT,
   ARG,
         LITERAL,
         BROKEN_TOKEN } type;
  int literal_value;    // this field used to store the value of literal tokens
  int arg_no;           // this field used to store the index of argument literals argN
  char str[MAX_TOKEN_LENGTH];
} token;

// line_number : You can use this to keep track of the current line number which can be useful in reporting syntax errors.
extern int line_number;

int read_token (token *theToken, FILE *theFile);

// Extra functions which you may wish to define and use , or not
const char *token_type_to_string (int type);

void incr();
int get();
void print_token (token *theToken, FILE* f);
void arithmetic(FILE*f, token *t);
void op_not(FILE*f, token *t);
void defun(FILE* f, token* label);
void argN(FILE* f, char* t);
void literal(FILE *f, token* t);
void comparisons(FILE*f, token *t);
void rot(FILE* f);
void swap(FILE* f);
void dup(FILE* f);
void drop(FILE* f);
void if_cond(stack *s, FILE* f);
void else_cond(stack *s, FILE* f);
void endif_cond(stack *s, FILE* f, bool e); 
void rtn(FILE* f);
void callFunc(FILE* f, token* t);
