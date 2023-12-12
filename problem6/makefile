all: test run

test: main.cpp
	g++ -fsanitize=address -g -o test -lasan -lgtest -lgtest_main ./main.cpp

.PHONY: run

run:
	./test

