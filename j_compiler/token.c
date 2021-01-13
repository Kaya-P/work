/*
 * token_test.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"
#include "stack.h"

int extractInt(char* t) {
	int val;
	while (*t) {
		if (isdigit(*t) || ((*t == '-' || *t == '+')
			&& isdigit(*(t + 1)))) {
			val = (int)strtol(t, &t, 10);
		} else {
			t++;
		}
	}
	return val;
}
int line_number = 0;

void incr(){
	line_number++;
	return;
}

int get(){
	return line_number;
}

void print_token (token *theToken, FILE* f) {	
	switch (theToken->type) {
		case PLUS : fprintf(f, "\t%s\n", "ADD R7, R7, R2");
			break;
		case MINUS : fprintf(f, "\t%s\n", "SUB R7, R7, R2");
			break;
		case MUL : fprintf(f, "\t%s\n", "MUL R7, R7, R2");
			break;
		case DIV : fprintf(f, "\t%s\n", "DIV R7, R7, R2");
			break;
		case MOD : fprintf(f, "\t%s\n", "MOD R7, R7, R2");   
			break;
		case AND : fprintf(f, "\t%s\n", "AND R7, R7, R2");
			break;
		case OR : fprintf(f, "\t%s\n", "OR R7, R7, R2");
			break;
		case NOT : fprintf(f, "\t%s\n", "NOT R7, R3");
			break;		    
        case LT : fprintf(f, "\t%s%d\n", "Brn True_comp_", get());
        	break;
        case LE : fprintf(f, "\t%s%d\n", "Brz True_comp_", get()); 
        	break;
        case EQ : fprintf(f, "\t%s%d\n", "Brz True_comp_", get()); 
        	break;
        case GE : fprintf(f, "\t%s%d\n", "Brzp True_comp_", get());
        	break; 
        case GT : fprintf(f, "\t%s%d\n", "Brp True_comp_", get());
        	break;
        default: break;	
	}
	return;
}



void literal(FILE *f, token* t){
	
	fprintf(f, "\n\t%s\n", ";;load and store literal");
	if (t->literal_value > 256 || t -> literal_value < 0){
		//const
		int x = t->literal_value &  0xFF;
		//hiconst
		int y = t->literal_value & 0xFF00;
		y >>= 8;
		fprintf(f, "\t%s%d\n", "CONST R7, #", x);
		fprintf(f, "\t%s%d\n", "HICONST R7, #", y);
		fprintf(f, "\t%s\n", "STR R7, R6, #-1");
		fprintf(f, "\t%s", "ADD R6, R6, #-1");
	} else {
		fprintf(f, "\t%s%s\n", "CONST R7, #", t->str);
		fprintf(f, "\t%s\n", "STR R7, R6, #-1");
		fprintf(f, "\t%s", "ADD R6, R6, #-1");
	}
	//fprintf(f, "\t%s\n", t->str);
	return;
}
void op_not(FILE*f, token *t) {
	fprintf(f, "\n\t%s\n", ";;not operation");
	fprintf(f, "\t%s\n", "LDR R3, R6, #1");
	//according to input
	print_token(t, f);
	//str not		
	fprintf(f, "\t%s", "STR R7, R6, #-1");
}


void arithmetic(FILE*f, token *t) {
	fprintf(f, "\n\t%s\n", ";;arithmetic operation");
	fprintf(f, "\t%s\n", "LDR R7, R6, #0");
	fprintf(f, "\t%s\n", "LDR R2, R6, #1");
	//according to input
	print_token(t, f);
	//remove literals
	fprintf(f, "\t%s\n", "ADD R6, R6, #2");
	//str sum		
	fprintf(f, "\t%s\n", "STR R7, R6, #-1");
	//move R6 pointer
	fprintf(f, "\t%s", "ADD R6, R6, #-1");
}
void comparisons(FILE*f, token *t){
 	int line_number;
 	//count lines to have unique labels 
 	fprintf(f, "\n\t%s\n", ";; comparison operation");
	//a
	fprintf(f, "\t%s\n", "LDR R7, R6, #0");
	//b
	fprintf(f, "\t%s\n", "LDR R2, R6, #1");
	fprintf(f, "\t%s\n", "CMP R7, R2");
	//according to input
	print_token(t, f);
	fprintf(f, "\t%s\n", "CONST R7, #0");
	fprintf(f, "\t%s%d\n", "Brnzp End_instruct_", get());
	fprintf(f, "%s%d\n", "True_comp_", get());
	fprintf(f, "\t%s\n", "CONST R7, #1");
	fprintf(f, "%s%d\n", "End_instruct_", get());
	//remove literals
	fprintf(f, "\t%s\n", "ADD R6, R6, #2");
	//str sum		
	fprintf(f, "\t%s\n", "STR R7, R6, #-1");
	//move R6 pointer
	fprintf(f, "\t%s", "ADD R6, R6, #-1");
}

void callFunc(FILE* f, token* t) {
	fprintf(f, "\n\t%s\n", ";;function call");
	fprintf(f, "\t%s %s", "JSR", t->str);
}

void drop(FILE* f) {
 	fprintf(f, "\n\t%s\n", ";;drop");
 	fprintf(f, "\t%s", "ADD R6, R6, #1");
}

void dup(FILE* f) {
 	fprintf(f, "\n\t%s\n", ";;dup");
 	fprintf(f, "\t%s\n", "LDR R7, R6, #0");
 	fprintf(f, "\t%s\n", "STR R7, R6, #-1");
 	fprintf(f, "\t%s", "ADD R6, R6, #-1");
}

void swap(FILE* f) {
 	fprintf(f, "\n\t%s\n", ";;swap");
 	fprintf(f, "\t%s\n", "LDR R4, R6, #0");
 	fprintf(f, "\t%s\n", "LDR R3, R6, #1");
 	fprintf(f, "\t%s\n", "STR R4, R6, #1");
 	fprintf(f, "\t%s", "STR R3, R6, #0");
}

void rot(FILE* f) {
 	fprintf(f, "\n\t%s\n", ";;rot");
 	fprintf(f, "\t%s\n", "LDR R4, R6, #0");
 	fprintf(f, "\t%s\n", "LDR R3, R6, #1");
 	fprintf(f, "\t%s\n", "LDR R2, R6, #2");
 	fprintf(f, "\t%s\n", "STR R4, R6, #1");
 	fprintf(f, "\t%s\n", "STR R3, R6, #2");
 	fprintf(f, "\t%s", "STR R2, R6, #0");
}

void rtn(FILE* f) {
	fprintf(f, "\n\t%s\n", ";;return & epilogue");
 	fprintf(f, "\t%s\n", "LDR R7, R6, #0");
 	fprintf(f, "\t%s\n", "STR R7, R5, #2");
 	fprintf(f, "\t%s\n", "ADD R6, R5, #0");
 	fprintf(f, "\t%s\n", "LDR R5, R6, #0");
 	fprintf(f, "\t%s\n", "LDR R7, R6, #1");
 	fprintf(f, "\t%s\n", "ADD R6, R6, #2");
 	fprintf(f, "\t%s\n", "RET");
}

void if_cond(stack *s, FILE* f) {
	fprintf(f, "\n\t%s\n", ";;if statement");
	fprintf(f, "\t%s\n", "CONST R7, #0");
	fprintf(f, "\t%s\n", "LDR R4, R6 #0");
	fprintf(f, "\t%s\n", "ADD R6, R6, #1");
	fprintf(f, "\t%s\n", "CMP R7, R4");	
	stack_elt elt;
	elt = *peek(s);
	int n = elt.numerator;
	fprintf(f, "\t%s%d", "Brz else_", n);
}

void else_cond(stack *s, FILE* f) {
	fprintf(f, "\n\t%s\n", ";;else token");
	stack_elt elt;
	elt = *peek(s);
	int n = elt.numerator;
	fprintf(f, "\t%s%d\n", "Brnzp end_", n);
	fprintf(f, "%s%d", "else_", n);
}

void endif_cond(stack *s, FILE* f, bool e) {
	fprintf(f, "\n\t%s\n", ";;endif token");
	stack_elt elt;
	elt = *peek(s);
	int n = elt.numerator;
	if (!e) {
		fprintf(f, "%s%d\n", "else_", n);
	}
	fprintf(f, "%s%d", "end_", n);
}

void defun(FILE* f, token* label) {
	//prologue
	//write FALIGN
	
	fprintf(f, "\t\t\t%s\n", ".CODE" );
  	fprintf(f, "\t\t\t%s\n", ".FALIGN" );
	fprintf(f, "\n\t%s\n", ";;setup function");
	fprintf(f, "%s\n", label->str);
	fprintf(f, "\t%s\n", "STR R7, R6, #-2");
	fprintf(f, "\t%s\n", "STR R5, R6, #-3");
	fprintf(f, "\t%s\n", "ADD R6, R6, #-3");
	fprintf(f, "\t%s", "ADD R5, R6, #0");
	//locate space for variables
	

}
void argN(FILE* f, char* t) {
	int offset = extractInt(t);
	int offsetChange = 2 + offset;
	fprintf(f, "\n\t%s\n", ";;retreive arg");
	fprintf(f, "\t%s\n", "ADD R6, R6, #-1");
	fprintf(f, "\t%s%d\n", "LDR R7, R5, #", offsetChange);
	fprintf(f, "\t%s", "STR R7, R6, #0");

}
