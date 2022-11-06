#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

#include "token.h"
#include "stack.h"

char * scan_expression();
int valid(char * expression);
char * topostfix(char * infixexp);

#endif  // SRC_INPUT_H_
