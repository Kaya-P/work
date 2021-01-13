/*
 * jc.c
 */

#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"
#include "stack.h"


int isValidStr(char* s){
  int n = 1;
  while (*s){
    if (ispunct(*s) == 0 || isdigit(*s) != 0|| 
       *s == 95) {
      n = n * 1;
    } else {
     return 0;
    }
    
    s++;
  }
  return n;
}

int startsWith(const char* a, const char* b) {
    if (strncmp(a,b,strlen(b)) == 0) {
      return 1;
    }
    return 0;
  }

token t;

int main(int argc, char **argv) {
  if (argc > 2) {
    exit(1);
  }   
    
  size_t s = strlen(argv[1]);
  char * check = argv[1];
  if (s <= 2 && check[s] != 'j' && check[s - 1] != '.') {
    exit(1);
  }

  FILE* input = fopen(argv[1], "r");
  FILE* output;
  bool conditional = false;
  char *line = NULL;
    size_t len = 0;
  char valid;
    char *semiColon = NULL;
    char *token;
    stack theIfStack;
    init_stack(&theIfStack);
    //extract file name
    
    int size = strlen(argv[1]) - 2;
    char* fileName = calloc((size + 5), sizeof(char));
    fileName = strncpy(fileName, argv[1], size);
    strcat(fileName, ".asm");
    printf("%s\n", fileName);
    output = fopen(fileName, "w");
    free(fileName);
    //falign
    //code headers 

  bool else_stat = false;
  bool returns = true;

    while ((valid = getline(&line, &len, input))  != -1) {

      incr();
        /* get the first token */
      token = strtok(line,  "  \t\r\n\v\f");

      while( token != NULL ) {
          
          semiColon = strstr(token, ";");
          if (semiColon == token) {
            break;
          }
          //argN check 
          int x = strncmp(token, "arg", 3);         
          //argN
          if (x == 0) {
            //printf("%s\n", "here" );
            argN(output, token);
          } else if (startsWith(token, "0x") == 1) {
            int length = strlen(token);
        for (int i = 2; i < length; i++) {
          if (!isxdigit(token[i])){
            printf("%s\n", "invalid hexadecimal number");
                free(line);
                fclose(output);
                fclose(input);
                exit(1);
          }
        }
       
            t.type = LITERAL;
            t.literal_value = (int)strtol(token, &token, 0);
            strcpy(t.str, token);
            literal(output, &t);
        //check decimal  
          } else if (isdigit(token[0]) || (*token == '-' && isdigit(token[1]))){
            int length = strlen(token);
            for (int i = 2; i < length; i++) {
          if (!isxdigit(token[i])){
            printf("%s\n", "invalid number");
              free(line);
              fclose(output);
              fclose(input);
              exit(1);
          }
        }
            t.type = LITERAL;
            strcpy(t.str, token);   
            t.literal_value = (int)strtol(token, &token, 10);
            literal(output, &t);
            
          } else if (strcmp("+", token) == 0) {
            t.type = PLUS;
            arithmetic(output, &t); 
          //subtract  
          } else if (strcmp("-", token) == 0) {
            t.type = MINUS;
            arithmetic(output, &t); 
          //multiply  
          } else if (strcmp("*", token) == 0) {
            t.type = MUL;
            arithmetic(output, &t); 
          //divide  
          } else if (strcmp("/", token) == 0) {
            t.type = DIV;
            arithmetic(output, &t);  
          //mod  
          } else if (strcmp("%", token) == 0) {
            t.type = MOD;
            arithmetic(output, &t);
          //and  
          } else if (strcmp("and", token) == 0) {
            t.type = AND;
            arithmetic(output, &t); 
          //or 
          } else if (strcmp("or", token) == 0) {
            t.type = OR;
            arithmetic(output, &t);  
          //not 
          } else if (strcmp("not", token) == 0) {
            t.type = NOT;
            op_not(output, &t);
          //eq     
          } else if (strcmp("eq", token) == 0) {
            t.type =  EQ;
            comparisons(output, &t);  
          //lt  
          } else if (strcmp("lt", token) == 0) {
            t.type = LT;
            comparisons(output, &t); 
          //le 
          } else if (strcmp("le", token) == 0) {
            t.type = LE;
            comparisons(output, &t);  
          //gt 
          } else if (strcmp("gt", token) == 0) {
            t.type = GT;
            comparisons(output, &t);
          //ge     
          } else if (strcmp("ge", token) == 0) {
            t.type =  GE;
            comparisons(output, &t);
          //drop  
          } else if (strcmp("drop", token) == 0) {
            drop(output);
          //dup 
          } else if (strcmp("dup", token) == 0) {
            dup(output); 
          //swap 
          } else if (strcmp("swap", token) == 0) {
            swap(output);
          //rot    
          } else if (strcmp("rot", token) == 0) {
            rot(output);    
          //defun                     
          } else if (strcmp("return", token) == 0 ) {
            rtn(output);
            returns = true;
          } else if (strcmp("if", token) == 0) {
            push(&theIfStack, get());
            if_cond(&theIfStack, output);
            //store literal before
          } else if (strcmp("else", token) == 0) {
            else_stat = true;
            else_cond(&theIfStack, output);

          } else if (strcmp("endif", token) == 0) {
            endif_cond(&theIfStack, output, else_stat);
            pop(&theIfStack);
            else_stat = false;
            
          } else if (strcmp("defun", token) == 0) {
            if (!returns) {
              printf("%s\n", "missing return statement" );
              free(line);
              fclose(output);
              fclose(input);
              exit(1);
            }
            //function name IDENT 
            t.type = IDENT; 
            //get next token and store string
          token = strtok(NULL, "  \t\r\n\v\f");
            //check if valid name 
            strcpy(t.str, token);
            //printf("label: %s\n", token);
            //prologue
            defun(output, &t);
            returns = false;
          //function call 
          } else if (isValidStr(token)){  
            //jsr to function call
            strcpy(t.str, token);
            callFunc(output, &t);
          } else {
            t.type = BROKEN_TOKEN;
            fprintf( output, " %s\n", token );
          }

          token = strtok(NULL, "  \t\r\n\v\f");
        } 

      
  }

  if (!returns) {
    printf("%s\n", "missing return statement" );
    free(line);
    fclose(output);
    fclose(input);
    exit(1);
  }
  free(line);
  fclose(output);
  fclose(input);
  return 0;
} 
