#include "../src/lispy.c"
#include <assert.h>
#include <stdbool.h>

bool equals(lval* a, lval* b);
bool evaluate(char* input, lval* expected);

static void test_addition() {
  bool result = evaluate("+ 1 2", lval_num(3));
  assert(result && "test_addition");
}

static void test_subtraction() {
  bool result = evaluate("- 2 1", lval_num(1));
  assert(result && "test_addition");
}

static void test_negation() {
  bool result   = evaluate("- 1", lval_num(-1));
  assert(result && "test_negation");
}

static void test_division_by_zero() {
  bool result   = evaluate("/ 10 0", lval_err("Division by zero."));
  bool result2   = evaluate("/ (+ 5 5) (- 5 5)", lval_err("Division by zero."));
  assert(result && result2 && "test_division_by_zero");
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

static void test_equality() {
  lval* True  = lval_num(1);
  lval* False = lval_num(0);

  bool eq_true  = evaluate("== 2 2", True);
  bool eq_false = evaluate("== 2 1", False);

  bool ne_true  = evaluate("!= 1 2", True);
  bool ne_false = evaluate("!= 1 1", False);

  bool gt_true  = evaluate("> 3 2", True);
  bool gt_true2 = evaluate("> 2 2", False);
  bool gt_false = evaluate("> 1 2", False);

  bool ge_true  = evaluate(">= 3 2", True);
  bool ge_true2 = evaluate(">= 2 2", True);
  bool ge_false = evaluate(">= 1 2", False);
  
  bool le_true  = evaluate("<= 1 2", True);
  bool le_true2 = evaluate("<= 2 2", True);
  bool le_false = evaluate("<= 3 2", False);

  bool lt_true  = evaluate("< 1 2", True);
  bool lt_true2 = evaluate("< 2 2", False);
  bool lt_false = evaluate("< 3 2", False);

  assert(eq_true && eq_false 
      && ne_true && ne_false
      && ge_true && ge_true2 && ge_false
      && gt_true && gt_true2 && gt_false
      && le_true && le_true2 && le_false
      && lt_true && lt_true2 && lt_false
      && "test_equality");
}

static void test_definition() {
  bool undefined = evaluate("x", lval_err("Unbound Symbol 'x'"));
  assert(undefined && "test_definition");
}

int main() {
    test_addition();
    test_subtraction();
    test_negation();
    test_division();
    test_division_by_zero();
    test_multiplication();
    test_equality();
    test_definition();
}

// helper functions

bool evaluate(char* input, lval* expected) {

  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Symbol    = mpc_new("symbol");
  mpc_parser_t* Sexpr     = mpc_new("sexpr");
  mpc_parser_t* Qexpr     = mpc_new("qexpr");
  mpc_parser_t* Expr      = mpc_new("expr");
  mpc_parser_t* Lispy     = mpc_new("lispy");
    
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                               \
        number  : /-?[0-9]+/ ;                      \
        symbol  : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;\
        sexpr   : '(' <expr>* ')' ;                 \
        qexpr   : '{' <expr>* '}' ;                 \
        expr    : <number> | <symbol>               \
                | <sexpr>  | <qexpr> ;              \
        lispy   : /^/ <expr>* /$/ ;                 \
    ",
    Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

  lenv* e = lenv_new();
  lenv_add_builtins(e);

  bool result = false;
  mpc_result_t r;
  if(mpc_parse("<stdin>", input, Lispy, &r)) {
    lval* x = lval_eval(e, lval_read(r.output));
    result = equals(x, expected);
    lval_del(x);
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }

  lenv_del(e);
  mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

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

