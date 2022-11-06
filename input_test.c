#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "input.h"

const char * assert(int true);
int test(char * exp, char * expected);

int main() {
    // radicals
    printf("%s\n\n", assert(test("1 / x",     "1 x /")));
    printf("%s\n\n", assert(test("2 + 3 * 4", "2 3 4 * +")));
    printf("%s\n\n", assert(test("2 ^ 3", "2 3 ^")));
    printf("%s\n\n", assert(test("2 mod 3", "2 3 m")));

    // sub expressions
    printf("%s\n\n", assert(test("(x)", "x")));
    printf("%s\n\n", assert(test("(2.3)", "2.3")));
    printf("%s\n\n", assert(test("(x + 2)", "x 2 +")));
    printf("%s\n\n", assert(test("x * (x + 2) - 2", "x x 2 + * 2 -")));

    // functions
    printf("%s\n\n", assert(test("sin(x)", "x sin")));
    // printf("%s\n\n", assert(test("sin x", "x sin")));
    // printf("%s\n\n", assert(test("sin 0.2", "0.2 sin")));
    printf("%s\n\n", assert(test("sin(x) * cos(x)", "x sin x cos *")));
    printf("%s\n\n", assert(test("sin(x) * cos(0.76)", "x sin 0.76 cos *")));

    printf("%s\n\n", assert(test("log(sin(x))", "x sin log")));


    return 0;
}

const char * assert(int true) {
    return true ? "SUCCESS" : "FAIL";
}

int test(char * exp, char * expected) {
    int assert;

    char * postfixexp = topostfix(exp);
    printf("infix:              %s\n", exp);
    printf("postfix calculated: %s\n", postfixexp);
    printf("postfix excpected:  %s\n", expected);

    assert = strcmp(postfixexp, expected) == 0;
    
    free(postfixexp);

    return assert;
}
