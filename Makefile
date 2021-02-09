#Compiler options
GCC = gcc
CFLAGS = -Wall -Wshadow=global -fopenmp -march=native -O4

all:
	$(GCC) delta_f.c -o delta_f $(CFLAGS) -lm

clean:
	rm delta_f

format:
	clang-format-10 -style="{BasedOnStyle: LLVM, IndentWidth: 4, AlignConsecutiveMacros: true, IndentPPDirectives: AfterHash}" -i *.c *.h
	astyle -i *.c *.h
