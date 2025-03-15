#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1000

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

void printQuestions(char ***questions, int size) {
  system("clear");
  printf("#### Answer Key: ####\n");
  for (int i = 0; i < size; i++)
    printf("%d. %s----> %s\n", i + 1, questions[0][i], questions[1][i]);
}

void printEval(char ***questions, char *eval, int size) {
  system("clear");
  printf("\n################ EVALUATION: ################\n");
  for (int i = 0; i < size; i++)
    printf("[%c]%d. %s----> %s\n", eval[i], i + 1, questions[0][i],
           questions[1][i]);
}

void shuffleQuestions(char ***questions, int questionsCount) {
  srand(time(NULL));
  for (int i = 0, j = rand() % questionsCount; i < questionsCount;
       i++, j = rand() % questionsCount) {
    srand(time(NULL));
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

int getLine(char *string, int size) {
  char c;
  int i = 0;
  while (i < size - 1 && (c = getc(stdin)) != EOF)
    string[i++] = c;
  string[i] = '\0';
  clearInputBuffer();

  return 1;
}

int startQuiz(char ***questions, int questionsCount) {
  system("clear");
  shuffleQuestions(questions, questionsCount);
  char *ans = malloc(sizeof(char) * SIZE);
  char *answers = malloc(sizeof(char) * questionsCount);
  int score = 0;
  printf("Quiz Start: \n");
  clearInputBuffer();
  for (int i = 0; i < questionsCount; i++) {
    printf("%sAnswer: ", questions[0][i]);
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
  return 1;
}

int main(int argc, char **argv) {
  int returnSize, questionsCount;
  char ***data = mapInput(argv[1], &returnSize, &questionsCount);
  /* printf("%s%s", data[0][0], data[1][0]); */
  system("clear");
  printf("Created by Emman-pip :)\n");
  while (1) {
    printf("----------------- Welcome to my quizzer. ----------------- \n");
    printf("[1] Start quiz\n[2] See answer key\n[3] clear screen\n[else] "
           "exit\n\n");
    int option;
    printf("Choose an option: ");
    scanf("%d", &option);
    switch (option) {
    case 1:
      startQuiz(data, questionsCount);
      break;
    case 2:
      printQuestions(data, questionsCount);
      break;
    case 3:
      system("clear");
      break;
    case 4:
      exit(0);
      break;
    default:
      exit(1);
      break;
    }
  }
  return 0;
}
