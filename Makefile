build:
	cc -std=c99 -Wall ./src/lispy.c ./src/lval.h ./src/lval.c ./lib/mpc.c ./lib/mpc.h -ledit -lm -o ./artifacts/lispy.o

run: build
	./artifacts/lispy.o

clean:
	\rm -v ./artifacts/*
