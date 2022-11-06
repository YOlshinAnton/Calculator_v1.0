#ifndef SRC_PROCESS_H_
#define SRC_PROCESS_H_

#include "token.h"
#include "stack.h"

#define N 80
#define M 25

t_stack* charge_stack(char * postfixexp, double x);
double process_stack(t_stack* expstack);
double process_operator(struct token* token, double a, double b);
double* calculate_graph(char * postfixexp);

void print_graph(double * codomain);

#endif  // SRC_PROCESS_H_
