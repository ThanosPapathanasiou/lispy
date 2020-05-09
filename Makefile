build:
	cc -g -std=c99 -Wall ./src/lispy.c ./src/lval.h ./src/lval.c ./lib/mpc.c ./lib/mpc.h -ledit -lm -o ./artifacts/lispy.o

run: build
	./artifacts/lispy.o

build-test:
	cc -g -std=c99 -Wall ./test/evaluation.c ./src/lval.h ./src/lval.c ./lib/mpc.c ./lib/mpc.h -ledit -lm -o ./artifacts/evaluation.o

test: build-test
	./artifacts/evaluation.o

clean:
	\rm -v ./artifacts/*
