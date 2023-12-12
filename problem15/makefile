all: test run

test: main.cpp
	g++ -std=c++20 -g -o test -lgtest -lgtest_main ./main.cpp

.PHONY: run

run:
	./test

