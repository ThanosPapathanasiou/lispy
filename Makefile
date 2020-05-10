build:
	cc -g -std=c99 -Wall ./src/lval.h ./src/lval.c ./lib/mpc.c ./lib/mpc.h ./src/lispy.c -ledit -lm -o ./artifacts/lispy.o

run: build
	./artifacts/lispy.o

build-test:
	cc -g -std=c99 -Wall ./src/lval.h ./src/lval.c ./lib/mpc.h ./lib/mpc.c ./test/evaluation.c -ledit -lm -o ./artifacts/evaluation.o

test: build-test
	./artifacts/evaluation.o

clean:
	\rm -v ./artifacts/*
