#Compiler options
GCC = gcc
CFLAGS = -Wall -Wshadow=global -fopenmp -march=native -O4

all:
	$(GCC) deltaf.c -o deltaf $(CFLAGS) -lm

clean:
	rm deltaf

format:
	clang-format-10 -style="{BasedOnStyle: LLVM, IndentWidth: 4, AlignConsecutiveMacros: true, IndentPPDirectives: AfterHash}" -i *.c *.h
	astyle -i *.c *.h
