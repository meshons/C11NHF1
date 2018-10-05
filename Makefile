make:
	clang++ -c -o mystring.o mystring.cpp -std=c++11
	clang++ -o test test.cpp mystring.o -std=c++11
	./test