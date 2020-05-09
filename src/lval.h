#include "../lib/mpc.h"

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };

typedef struct lval {
  int type;
  long num;
  char* err;
  char* sym;
  int count;
  struct lval** cell;
} lval;

lval* lval_read(mpc_ast_t* t) ;

lval* lval_eval(lval* v);

void lval_println(lval* v);

void lval_del(lval* v);