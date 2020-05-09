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

lval* lval_num(long x);

lval* lval_err(char* m);

lval* lval_sym(char* s);

lval* lval_sexpr(void);

void lval_del(lval* v);

lval* lval_add(lval* v, lval* x);

lval* lval_pop(lval* v, int i);

lval* lval_take(lval* v, int i);

void lval_print(lval* v);

void lval_expr_print(lval* v, char open, char close);

void lval_println(lval* v);

lval* builtin_op(lval* a, char* op);

lval* lval_eval(lval* v);

lval* lval_eval_sexpr(lval* v);

lval* lval_read_num(mpc_ast_t* t);

lval* lval_read(mpc_ast_t* t);
