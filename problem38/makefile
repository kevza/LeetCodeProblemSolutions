.PHONY: all

all: test
	./test

test: main.cpp
	clang++ -o test -std=c++20 -g ./main.cpp -lgtest_main -lgtest

