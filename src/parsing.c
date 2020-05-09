#include <stdio.h>
#include <stdlib.h>
#include "../lib/mpc.h"
#include "lval.h"

#define true 1
#define false 0

#ifdef true

  # include <string.h>
  static char buffer[2048];
  char* readline(char* prompt){
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
  }

  void add_history(char* unused) {}

#else

  #include <editline/readline.h>
  #include <editline/history.h>

#endif

int main(int argc, char** argv) {

  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Symbol    = mpc_new("symbol");
  mpc_parser_t* Sexpr     = mpc_new("sexpr");
  mpc_parser_t* Expr      = mpc_new("expr");
  mpc_parser_t* Lispy     = mpc_new("lispy");
    
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                             \
        number  : /-?[0-9]+/ ;                    \
        symbol  : '+' | '-' | '*' | '/' ;         \
        sexpr   : '(' <expr>* ')' ;               \
        expr    : <number> | <symbol> | <sexpr> ; \
        lispy   : /^/ <expr>* /$/ ;               \
    ",
    Number, Symbol, Sexpr, Expr, Lispy);

  puts("λispy Version 0.0.4");
  puts("Press Ctrl+c to exit\n");

  while (true) {
    char* input = readline("λ> ");
    add_history(input);

    mpc_result_t r;
    if(mpc_parse("<stdin>", input, Lispy, &r)) {
      lval* x = lval_eval(lval_read(r.output));
      lval_println(x);
      lval_del(x);
      mpc_ast_delete(r.output);
    } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispy);
  
  return 0;
}
