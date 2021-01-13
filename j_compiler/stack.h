/*
 * stack.h
 */
#ifndef STACK_H
#define STACK_H

typedef struct stack_elt_tag {
  int numerator;
  struct stack_elt_tag *next;
} stack_elt;

typedef struct {
  stack_elt *first;
} stack;

void init_stack (stack *s);
void push (stack *s, int num);
void pop (stack *s);
stack_elt* peek (stack *s);
void clear (stack *s);
void print_first(stack *s);
void quit (stack *s);
void print_stack (stack *s);

#endif