#include <stdio.h>

#include "input.h"
#include "process.h"

int main() {
    char * expression = "log(sin(x))";
    char * postfixexp = topostfix(expression);

    puts(expression); puts(postfixexp);

    double * codomain = calculate_graph(postfixexp);

    print_graph(codomain); free(codomain); free(postfixexp);

    return 0;
}
