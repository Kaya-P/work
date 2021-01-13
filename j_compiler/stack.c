/*
 * stack.c
 */

#include "stack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_stack (stack *s)
{
  s->first = NULL;
}

//add at the front of the stack
void push (stack *s, int num)
{
  stack_elt *elt;
  
  // Allocate a new list element with malloc
  elt = malloc(sizeof(*elt));

  elt->next = NULL;


  // Copy the value
  elt->numerator = num;

  // Check if stack is empty
  if (s->first == NULL) {
    // add elt to the beginning
    s->first = elt;
  } else {
  	elt->next = s->first;
    s->first = elt;
  }
  
}
//remove first element
void pop (stack *s)
{
  if (s->first == NULL) {
  	printf ("STACK ERROR \n");
    return;
  }			
  stack_elt *elt;
  elt = s->first;
  s->first = elt->next;
  free(elt);
}

stack_elt* peek(stack *s) {
  stack_elt* temp = s->first;
  return temp;
}


void clear(stack *s) {
	while (s->first != NULL) {
		pop(s);
	}
  return;
}

void quit(stack* s) {
  clear(s);
  exit(0);
}

 








