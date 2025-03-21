#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1000

#define CLEAR "clear"

char ***mapInput(char *filename, int *returnSize, int *questionsCount) {
  FILE *file = fopen(filename, "r");

  char *str = malloc(sizeof(char) * SIZE);

  char ***data = malloc(sizeof(char **) * 2);
  data[0] = malloc(sizeof(char *) * SIZE);
  data[1] = malloc(sizeof(char *) * SIZE);
  int i;
  char past = 'a';
  /* for  (i = 0; (str = fgets(str, SIZE, file));) */
  i = 0;
  while ((str = fgets(str, SIZE, file))) {
    if (past == str[0]) {
      printf("Invalid_input: %s\n(invalid 'a' or 'q' at the begginging)\n",
             str);
      exit(1);
    }
    /* str[strlen(str) - 1] = '\0'; */
    switch (tolower(str[0])) {
    case 'q':
      data[0][i] = str;
      past = 'q';
      break;
    case 'a':
      data[1][i++] = str;
      past = 'a';
      break;
    case '\n':
      continue;
      break;
    case '#':
      continue;
      break;
    default:
      printf("Invalid_input: %s\n(could be missing 'a' or 'q)\n", filename);
      exit(1);
      break;
    }
    str = malloc(sizeof(char) * SIZE);
  }
  *returnSize = 2;
  *questionsCount = i;
  return data;
}

void printWithCol(char *s) {
  for (int i = 0; i < (int)strlen(s); i++) {
    if (i % 64 == 0 && i > 0)
      printf("\n");
    printf("%c", s[i]);
  }
}

void printQuestions(char ***questions, int size) {
  system(CLEAR);
  printf("#### Answer Key: ####\n");
  for (int i = 0; i < size; i++) {
    printWithCol(questions[0][i]);
    printf("-----> %s\n", questions[1][i]);
  }
}

void printEval(char ***questions, char *eval, int size) {
  system(CLEAR);
  printf("\n################ EVALUATION: ################\n");
  for (int i = 0; i < size; i++) {
    printf("[%c] %d. ", eval[i], i + 1);
    printWithCol(questions[0][i]);
    printf("-----> %s\n", questions[1][i]);
  }
}

void shuffleQuestions(char ***questions, int questionsCount) {
  srand(time(NULL));
  for (int i = 0, j = rand() % questionsCount; i < questionsCount;
       i++, j = (i + rand() / (RAND_MAX / questionsCount - i)) %
                questionsCount) {
    srand(time(NULL) + i * i);
    char *questionTmp = malloc(sizeof(char) * SIZE);
    char *answerTmp = malloc(sizeof(char) * SIZE);
    strcpy(questionTmp, questions[0][i]);
    strcpy(answerTmp, questions[1][i]);
    strcpy(questions[0][i], questions[0][j]);
    strcpy(questions[1][i], questions[1][j]);
    strcpy(questions[0][j], questionTmp);
    strcpy(questions[1][j], answerTmp);
  }
}

void clearInputBuffer() {
  while (getc(stdin) != '\n' && getchar() != EOF)
    ;
}

int identificationQuiz(char ***questions, int questionsCount) {
  system(CLEAR);
  shuffleQuestions(questions, questionsCount);
  char *ans = malloc(sizeof(char) * SIZE);
  char *answers = malloc(sizeof(char) * questionsCount);
  int score = 0;
  printf("Quiz Start: \n");
  clearInputBuffer();
  for (int i = 0; i < questionsCount; i++) {
    printf("%d/%d. ", i + 1, questionsCount);
    printWithCol(questions[0][i]);
    printf("Answer: ");
    ans = fgets(ans, SIZE, stdin);
    fflush(stdin);

    if (strstr(questions[1][i], ans) && strlen(ans) > 1) {

      score++, answers[i] = '/';
      printf("Right answer!\n");
    } else {
      answers[i] = 'X';
      printf("Wrong answer!\nCorrect was:---> %s", questions[1][i]);
    }
    printf("\n");
  }
  printf("##################################\nScore: %d/%d\n", score,
         questionsCount);
  clearInputBuffer();
  printf("See evaluation? (Y/n): ");
  char c;
  scanf("%c", &c);

  if (c != 'n')
    printEval(questions, answers, questionsCount);

  free(ans);
  free(answers);
  return 1;
}

char **shuffleArr(char ***source, int questionsCount) {
  /* generating new array */
  char **questions = malloc(sizeof(char *) * questionsCount);
  for (int i = 0; i < questionsCount; i++)
    questions[i] = malloc(sizeof(char) * SIZE);
  for (int i = 0; i < questionsCount; i++)
    strcpy(questions[i], source[1][i]);

  /* shuffling */
  srand(time(NULL));
  int i, j;
  char *tmp = malloc(sizeof(char) * SIZE);

  for (i = 0, j = rand() % questionsCount; i < questionsCount;
       i++, j = rand() % questionsCount) {
    strcpy(tmp, questions[i]);
    strcpy(questions[i], questions[j]);
    strcpy(questions[j], tmp);
    tmp = malloc(sizeof(char) * SIZE);
  }
  for (int i = 0; i < questionsCount; i++)
    questions[i][0] = 'A' + i, questions[i][strlen(questions[i]) - 1] = '\0';
  return questions;
}

void printChoices(char **copy, int questionsCount) {
  for (int i = 0; i < questionsCount; i++) {
    printf("%s\n", copy[i]);
  }
  printf("\n\n");
}

int indentificationWithChoicesQuiz(char ***questions, int questionsCount) {
  system(CLEAR);
  shuffleQuestions(questions, questionsCount);
  char *ans = malloc(sizeof(char) * SIZE);
  char *answers = malloc(sizeof(char) * questionsCount);
  int score = 0;
  printf("Quiz Start: \n");
  clearInputBuffer();

  char **choices = shuffleArr(questions, questionsCount);
  for (int i = 0; i < questionsCount; i++) {
    system(CLEAR);
    printChoices(choices, questionsCount);
    printWithCol(questions[0][i]);
    printf("Answer: ");
    ans = fgets(ans, SIZE, stdin);
    fflush(stdin);

    if (strstr(questions[1][i], ans))
      score++, answers[i] = '/';
    else
      answers[i] = 'X';
    printf("\n");
  }
  printf("##################################\nScore: %d/%d\n", score,
         questionsCount);
  clearInputBuffer();
  printf("See evaluation? (Y/n): ");
  char c;
  scanf("%c", &c);

  if (c != 'n')
    printEval(questions, answers, questionsCount);

  free(ans);
  free(answers);
  free(choices);
  return 1;
}

int main(int argc, char **argv) {
  int returnSize, questionsCount;
  if (strcmp(argv[1], "help") == 0) {
    printf("Use the program like this: \n./quizzer questions.txt_file\n\nRead "
           "the readme file for more documentation\n");
    exit(0);
  }
  char ***data = mapInput(argv[1], &returnSize, &questionsCount);
  /* printf("%s%s", data[0][0], data[1][0]); */
  system(CLEAR);
  printf("Created by Emman-pip :)\n");
  while (1) {
    printf("----------------- Welcome to my quizzer. ----------------- \n");
    printf(
        "[1] Start identification quiz\n[2] Start indentificationWithChoices "
        "quiz\n[3] See answer key\n[4] clear screen\n[5] "
        "exit\n\n");
    int option;
    printf("Choose an option: ");
    fflush(stdin);
    scanf("%d", &option);
    switch (option) {
    case 1:
      identificationQuiz(data, questionsCount);
      break;
    case 2:
      indentificationWithChoicesQuiz(data, questionsCount);
      break;
    case 3:
      printQuestions(data, questionsCount);
      break;
    case 4:
      system(CLEAR);
      break;
    case 5:
      exit(0);
      break;
    default:
      printf("Invalid input\n");
      break;
    }
  }
  return 0;
}
