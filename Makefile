all:
	g++ main.cpp -o main -std=c++11

run: all
	./main
