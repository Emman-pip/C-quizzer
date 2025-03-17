all: compile run

compile:
	gcc main.c -o quizzer -Wall -Wextra -Wpedantic


run: quizzer
	./quizzer questions.txt


makeWindows:
	gcc main.c -o quizzer -Wall -Wextra -Wpedantic
	quizzer.exe questions.txt
