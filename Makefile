#https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

CC=gcc
OPTIONS=-Wall -I inc

.PHONY: clean run test

main.exe: main.c
	${CC} $^ -o $@ ${OPTIONS}
run: main.exe
	./main
clean:
	rm ./main.exe
test: main.exe
	 #hack to eval ansi escape codes in wt git bash
	./test.sh 2>&1 | cat
