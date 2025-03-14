all: run
	


compile:
	gcc main.c -o quizzer -Wall -Wextra -Wpedantic


run: compile
	./quizzer questions.txt
