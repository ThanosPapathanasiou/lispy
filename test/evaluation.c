#include "../src/lval.h"
#include <assert.h>
#include <stdbool.h>

bool equals(lval* a, lval* b);
bool evaluate(char* input, lval* expected);
static void test_addition();
static void test_negation();
static void test_division_by_zero();
static void test_division();
static void test_multiplication();

int main() {
    test_addition();
    test_negation();
    test_division();
    test_division_by_zero();
    test_multiplication();
}

static void test_addition() {
  bool result = evaluate("+ 1 2", lval_num(3));
  assert(result && "test_addition");
}

static void test_negation() {
  bool result   = evaluate("- 1", lval_num(-1));
  assert(result && "test_negation");
}

static void test_division_by_zero() {
  bool result   = evaluate("/ 10 0", lval_err("Division by zero."));
  assert(result && "test_division_by_zero");
}

static void test_division() {
  bool result   = evaluate("/ 10 5", lval_num(2));
  bool result2  = evaluate("/ 9 5", lval_num(1));
  assert(result && result2 && "test_division");
}

static void test_multiplication() {
  bool result   = evaluate("* 3 5", lval_num(15));
  bool result2  = evaluate("* 0 5", lval_num(0));
  assert(result && result2 && "test_multiplication");
}

bool evaluate(char* input, lval* expected) {

  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Symbol    = mpc_new("symbol");
  mpc_parser_t* Sexpr     = mpc_new("sexpr");
  mpc_parser_t* Qexpr     = mpc_new("qexpr");
  mpc_parser_t* Expr      = mpc_new("expr");
  mpc_parser_t* Lispy     = mpc_new("lispy");
    
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                             \
        number  : /-?[0-9]+/ ;                    \
        symbol  : '+' | '-' | '*' | '/'           \
                | \"list\" | \"head\" | \"tail\"  \
                | \"eval\" | \"join\" ;           \
        sexpr   : '(' <expr>* ')' ;               \
        qexpr   : '{' <expr>* '}' ;               \
        expr    : <number> | <symbol>             \
                | <sexpr>  | <qexpr> ;            \
        lispy   : /^/ <expr>* /$/ ;               \
    ",
    Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

  bool result = false;
  mpc_result_t r;
  if(mpc_parse("<stdin>", input, Lispy, &r)) {
    lval* x = lval_eval(lval_read(r.output));
    result = equals(x, expected);
    lval_del(x);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
  return result;
}

bool equals(lval* a, lval* b) {
  if ( a->type != b->type) { return false; }
  switch (a->type)
  {
    case LVAL_ERR:
      return strcmp(a->err, b->err) == 0;
    
    case LVAL_NUM:
      return a->num == b->num;

    default:
      return false;
  }
}

