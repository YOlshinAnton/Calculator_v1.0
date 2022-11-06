#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

enum token_type { ARGUMENT, OPERAND, OPERATOR, FUNCTION, SPACE, BAD };

struct token {
    enum token_type type;
    void * it;
};

struct op {
    const char * opname;
    double (*op)(double, double);
};

struct func {
    const char* fname;
    double (*f)(double);
};

struct token* operand(double value);
struct token* operator(char op);
struct token* function(char * exp, char** expp);

int get_function_name_id(const char* exp);
const char* get_function_name(int id);

double get_operand(struct token* token);
char get_operator(struct token* token);
struct func* get_function(struct token* token);

int is_token(const char* exp);
int is_operand(const char* exp);
int is_operator(const char* exp);
int is_additive_operator(const char* exp);
int is_multiplicative_operator(const char* epx);
int is_function(const char* exp);

enum token_type token_type(const char * exp);

void print_token(struct token* token);
char * form_format_string(struct token* token);

void free_token(void * token);

#endif  // SRC_TOKEN_H_
