#include "../lib/mpc.h"

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM,
       LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;
typedef lval*(*lbuiltin)(lenv*, lval*);

struct lval {
  int type;

  // basic
  long num;
  char* err;
  char* sym;
  
  // function
  lbuiltin builtin;
  lenv* env;
  lval* formals;
  lval* body;

  // expression
  int count;
  lval** cell;
};

struct lenv {
  lenv* par;
  int count;
  char** syms;
  lval** vals;
};

lval* lval_read(mpc_ast_t* t) ;

lval* lval_eval(lenv* e, lval* v);

void lval_println(lval* v);

void lval_del(lval* v);

lval* lval_num(long x);

lval* lval_err(char* fmt, ...);

// lisp environment

lenv* lenv_new(void);

lenv* lenv_copy(lenv* e);

void lenv_del(lenv* e);

void lenv_add_builtins(lenv* e);