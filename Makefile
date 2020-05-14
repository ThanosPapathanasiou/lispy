build:
	cc -g -std=c99 -Wall ./lib/mpc.h ./lib/mpc.c ./src/lispy.c -ledit -lm -o ./artifacts/lispy.o

run: build
	cp ./samples/*.lispy ./artifacts/
	./artifacts/lispy.o

build-test:
	cc -g -std=c99 -Wall ./lib/mpc.h ./lib/mpc.c ./src/lispy.c ./test/lispy-test.c -ledit -lm -o ./artifacts/lispy-test.o

test: build-test
	./artifacts/lispy-test.o

clean:
	\rm -v ./artifacts/*
