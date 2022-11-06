#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "token.h"

/* private */
static int index_of(const char* exp, const char* variants[], int count) {
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (strncmp(exp, variants[i], strlen(variants[i])) == 0) {
            index = i;
        } 
    }
    return index;
}

static const char* _additive_operators[] = {
    "+",
    "-"
};
static const char* _multiplicative_operators[] = {
    "*",
    "/",
    "^",
    "mod"
};
static const char* _function_names[] = {
    "sin",
    "cos",
    "tan",
    "asin",
    "acos",
    "atan",
    "sqrt",
    "ln",
    "log"
};
static const struct func _functions[] = {
    { "sin", sin },
    { "cos", cos },
    { "tan", tan },
    { "asin", sin },
    { "acos", cos },
    { "atan", tan },
    { "sqrt", sqrt },
    { "ln", NULL },
    { "log", log }
};

static const int _multiplicative_operator_count = sizeof(_multiplicative_operator_count) / sizeof(const char*);
static const int _additive_operator_count = sizeof(_additive_operators) / sizeof(const char*);
static const int _function_count = sizeof(_function_names) / sizeof(const char*);
/* private */

/* token constructors*/
struct token* operand(double value) {
    struct token* token = malloc(sizeof(struct token));
    double * vp = malloc(sizeof(double)); * vp = value;
    token -> type = OPERAND;
    token -> it = vp;
    return token;
}

struct token* operator(char op) {
    struct token* token = malloc(sizeof(struct token));
    char * opp = malloc(1); * opp = op;
    token -> type = OPERATOR;
    token -> it = opp;
    return token;
}

struct token* function(char * exp, char** expp) {
    int func_id = get_function_name_id(exp);

    struct token* token = malloc(sizeof(struct token));
    struct func* func = malloc(sizeof(struct func));
    func -> fname = _functions[func_id].fname;
    func -> f = _functions[func_id].f;
    token -> type = FUNCTION;
    token -> it = func;

    *expp += strlen(_function_names[func_id]);

    return token;
}

int is_operand(const char* exp) {
    return isdigit(*exp) || *exp == '.';
}
int is_additive_operator(const char* exp) {
    return -1 != index_of(exp, _additive_operators, _additive_operator_count);
}
int is_multiplicative_opeartor(const char* exp) {
    return -1 != index_of(exp, _multiplicative_operators, _multiplicative_operator_count);
}
int is_operator(const char* exp) {
    return is_additive_operator(exp) || is_multiplicative_opeartor(exp);
}
int is_function(const char * exp) {
    return -1 != index_of(exp, _function_names, _function_count);
}
int is_token(const char* exp) {
    return is_operand(exp) || is_operator(exp) || is_function(exp);
}

double get_operand(struct token* token) {
    return *((double*) token->it);
}
char get_operator(struct token* token) {
    return *((char*) token->it);
}
struct func* get_function(struct token* token) {
    return ((struct func*) token->it);
}
int get_function_name_id(const char* exp) {
    int func_id = -1;
    if (isalpha(*exp)) {
        func_id = index_of(exp, _function_names, _function_count);
    }
    return func_id;
}
const char* get_function_name(int id) {
    int count = sizeof(_function_names) / sizeof(char*);
    return _function_names[id % count];
}

enum token_type token_type(const char * exp) {
    enum token_type type;
    if (*exp == 'x') {
        type = ARGUMENT;
    } else if (is_operand(exp)) {
        type = OPERAND;
    } else if (is_operator(exp)) {
        type = OPERATOR;
    } else if (is_function(exp)) {
        type = FUNCTION;
    } else if (isspace(*exp)) {
        type = SPACE;
    } else {
        type = BAD;
    }
    return type;
}

char * form_format_string(struct token * token) {
    char * format;
    switch (token -> type) {
        case OPERATOR:  format = "%c"; break;
        case FUNCTION:  format = "%s"; break;
        case ARGUMENT:
        case OPERAND:   format = "%lf"; break;
        case SPACE:
        case BAD:       format = "%c";
    }
    return format;
}

void print_token(struct token * token) {
    char * format = form_format_string(token);
    switch (token -> type) {
        case ARGUMENT:
        case OPERAND:   printf(format, get_operand(token)); break;
        case OPERATOR:  printf(format, get_operator(token)); break;
        case FUNCTION:  printf(format, get_function(token) -> fname); break;
        case SPACE:
        case BAD:       break;
    }
}

void free_token(void * t) {
    struct token * token = t;
    if (token) {
        if (token -> it) {
            free(token -> it);
        }
        free(token);
    }
}
