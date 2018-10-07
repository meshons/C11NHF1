make:
	clang++ -fprofile-instr-generate -fcoverage-mapping -c -o mystring.o mystring.cpp -std=c++11 -g -Wall
	clang++ -fprofile-instr-generate -fcoverage-mapping -o test test.cpp mystring.o -std=c++11 -g -Wall

coverage:
	LLVM_PROFILE_FILE="test.profraw" ./test
	llvm-profdata merge -sparse test.profraw -o test.profdata
	llvm-cov show ./test -instr-profile=test.profdata
	llvm-cov report ./test -instr-profile=test.profdata

run:
	./test
