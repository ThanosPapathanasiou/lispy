#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#define true 1
#define false 0

#ifdef true

# include <string.h>

static char buffer[2048];

char* readline(char* prompt){
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer+1));
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

void add_history(char* unused) {}

#else
// if I get the editline lib to work with the greek alphabet I'll add it back.
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv){

    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");
    
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                       \
            number  : /-?[0-9]+/ ;                              \
            operator: '+' | '-' | '*' | '/' ;                   \
            expr    : <number> | '(' <operator> <expr>+ ')' ;   \
            lispy   : /^/ <operator> <expr>+ /$/ ;              \
        ",
        Number, Operator, Expr, Lispy);

    puts("λispy Version 0.0.2");
    puts("Press Ctrl+c to exit\n");

    while(true){
        char* input = readline("λ> ");

        add_history(input);

        mpc_result_t r;
        
        if(mpc_parse("<stdin>", input, Lispy, &r)){
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    
    return 0;
}















