This is my attempt to build my own lisp

I'm following the instructions from http://www.buildyourownlisp.com

To run the interpreter you can open a terminal and type in: 

``` bash
make run
```
That should build the project, run the program and start the interactive prompt.

Once you have a working prompt you can run simple operations like the following: 

``` lisp 
λ> + 1 2
3

λ> - 1
-1

λ> / 10 0
Error: Division by zero.

λ> + (+ 1 2) (- 5 3)
5

λ> +
<function>

λ> head {1 2 3}
{1}

λ> eval (head {1 2 3})
1

λ> x
Error: Unbound Symbol 'x'

λ> def {x} 100
()

λ> x
100
```