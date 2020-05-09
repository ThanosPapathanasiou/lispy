build:
	cc -std=c99 -Wall ./src/parsing.c ./src/lval.h ./src/lval.c ./lib/mpc.c ./lib/mpc.h -ledit -lm -o ./artifacts/parsing.o

run: build
	./artifacts/parsing.o

clean:
	\rm -v ./artifacts/*
