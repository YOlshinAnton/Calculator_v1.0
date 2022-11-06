#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "process.h"

t_stack* charge_stack(char * exp, double x) {
    t_stack* stack = init_stack();
    while (*exp) {
        struct token* token = NULL; enum token_type type = token_type(exp);
        switch (type) {
            case SPACE: exp++; break;
            case OPERAND:  token = operand(strtod(exp, (char**) & exp)); break;
            case ARGUMENT: token = operand(x); exp++; break;
            case OPERATOR: token = operator(*(exp)++); break;
            case FUNCTION: token = function(exp, (char**) & exp); break;
            case BAD: break;
        }
        if (type != SPACE) {
            if (type != BAD && token != NULL && stack != NULL) {
                push(stack, token);
            } else {
                if (token) {
                    free(token); token = NULL;
                }
                if (stack) {
                    destroy_stack(stack, free); stack = NULL;
                }
            }
        }
    }
    return stack;
}

double process_stack(t_stack* expstack) {
    struct token* token = pop(expstack);
    double value = 0;
    switch (token -> type) {
        case OPERAND: value = get_operand(token); break;
        case OPERATOR: value = process_operator(token,
                                                process_stack(expstack),
                                                process_stack(expstack)); break;
        case FUNCTION: value = (get_function(token)) -> f(process_stack(expstack)); break;
        case ARGUMENT: case SPACE: case BAD: break;
    }
    free_token(token);
    return value;
}

double process_operator(struct token* token, double a, double b) {
    double value = 0;
    switch (get_operator(token)) {
        case '+': value = a + b; break;
        case '-': value = a - b; break;
        case '*': value = a * b; break;
        case '/': value = a / b; break;
        case '^': value = pow(a, b); break;
        case 'm': value = fmod(a, b);
    }
    return value;
}

double calulate_point(char * postfixexp, double x) {
    double y;
    t_stack* expstack = charge_stack(postfixexp, x);
    y = process_stack(expstack);
    destroy_stack(expstack, free_token);
    return y;
}

double * calculate_graph(char * postfixexp) {
    double * codomain = malloc(N * sizeof(double));
    double x_step = 4 * M_PI / N;
    double x;
    for (int i = 0; i < N; i++) {
        x = i * x_step;
        codomain[i] = calulate_point(postfixexp, x);
    }
    return codomain;
}

void print_graph(double * codomain) {
    char graph[M][N];
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            graph[m][n] = '.';
        }
    }
    for (int n = 0; n < N; n++) {
        if (-1 <= codomain[n] && codomain[n] <= 1) {
            long m = lround(12 - 12 * codomain[n]);
            graph[m][n] = '*';
        }
    }
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            printf("%c", graph[m][n]);
        }
        printf("\n");
    }
}
