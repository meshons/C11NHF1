make:
	clang++ -c -o mystring.o mystring.cpp -std=c++11 -g
	clang++ -o test test.cpp mystring.o -std=c++11 -g
	./test