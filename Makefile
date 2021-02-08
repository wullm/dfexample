#Compiler options
GCC = gcc
CFLAGS = -Wall -Wshadow=global -fopenmp -march=native -O4

all:
	$(GCC) phase_space.c -o phase_space $(CFLAGS) -lm

clean:
	rm phase_space

format:
	clang-format-10 -style="{BasedOnStyle: LLVM, IndentWidth: 4, AlignConsecutiveMacros: true, IndentPPDirectives: AfterHash}" -i *.c *.h
	astyle -i *.c *.h
