all: compile run

compile:
	gcc main.c -o quizzer -Wall -Wextra -Wpedantic


run: quizzer
	./quizzer questions.txt
