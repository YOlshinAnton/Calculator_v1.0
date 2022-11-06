#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "input.h"

static int subexplen(const char * exp) {
    int index = 0;
    int open_braces = 0;
    if (*exp == '(') {
        open_braces++;
        exp++;
    } 
    while (*exp && open_braces > 0) {
        if (*exp == '(') {
            open_braces++;
        } else if (*exp == ')') {
            open_braces--;
        }
        ++exp;
        ++index;
    }
    return index - 1;
}

char* topostfix(char * exp) {
    long exp_len = strlen(exp);
    char * pep = calloc(2 * exp_len + 2, 1), * pes = pep;
    
    t_stack* opstack = init_stack();
    while (pep && *exp) {
        /* skip space */
        while (isspace(*exp)) {
            exp++;
        }

        /* numbers and operands just go to postfix expression string */
        if (*exp == 'x') {
            *pep = *exp; pep++, exp++;
            *pep = ' '; pep++;
        }

        else if (isdigit(*exp) || *exp == '.') {
            while (isdigit(*exp) || *exp == '.') {
                *pep = *exp; pep++, exp++;
            }
            *pep = ' '; pep++;
        }

        /* '*' and '/' operators go to stack until '+' or '-' operator is not arrived */
        else if (*exp == '*' || *exp == '/' || *exp == '^' || strncmp(exp, "mod", 3) == 0) {
            push(opstack, exp);
            if (strncmp(exp, "mod", 3) == 0) {
                exp += 3;
            } else {
                exp++;
            }
        }

        /* on '+' or '-' operators unroll stack into pep and push it */
        else if (*exp == '+' || *exp == '-') {
            while( opstack -> count ) {
                *pep = *((char*)pop(opstack)); pep++;
                *pep = ' '; pep++;
            }
            push(opstack, exp); exp++;
        }

        /* recursion for sub expression */
        else if (*exp == '(') {
            long len = subexplen(exp);
            char * sep = calloc(len + 1, 1); strncpy(sep, exp + 1, len);
            char * psp = topostfix(sep);

            strcat(pep, psp); pep += len; * pep = ' '; pep++;
            free(sep);
            free(psp);

            exp += len + 2;
        }

        /* function */
        else if (isalpha(*exp)) {
            int func_id = get_function_name_id(exp);
            if (func_id != -1) {
                const char* function_name = get_function_name(func_id);
                exp += strlen(function_name);

                while (isspace(*exp)) {
                    exp++;
                }

                if (*exp == '(') {
                    long len = subexplen(exp);
                    char * sep = calloc(len + 1, 1); strncpy(sep, exp + 1, len);
                    char * psp = topostfix(sep);
                    
                    long psplen = strlen(psp);
                    strcat(pep, psp); pep += psplen; * pep = ' '; pep++;

                    free(sep);
                    free(psp);
                    
                    exp += len + 2;
                }

                *pep = 0;
                strcat(pep, function_name);
                pep += strlen(function_name); * pep = ' '; pep++;
            }
        }

        /* space */
        else exp++;
    }   
    while( opstack -> count ) {
        *pep = *((char*)pop(opstack)); pep++;
        *pep = ' '; pep++;
    }
    destroy_stack(opstack, NULL);

    pep--; * pep = 0;

    return pes;
}
