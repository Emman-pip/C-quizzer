#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000



char ***mapInput(char *filename, int *returnSize, int *questionsCount)
{
  FILE *file = fopen(filename, "r");
  
  char *str = malloc(sizeof(char) * SIZE);

  char ***data = malloc(sizeof(char **) * 2);
  data[0] = malloc(sizeof(char*) * SIZE);
  data[1] = malloc(sizeof(char*) * SIZE);
  int i;
  char past = 'a';
  /* for  (i = 0; (str = fgets(str, SIZE, file));) */
  i = 0;
  while ((str = fgets(str, SIZE, file)))
    {
      if (past == str[0])
	{
	  printf("Invalid_input: %s\n(invalid 'a' or 'q' at the begginging)\n", str);
	  exit(1);
	}

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

{
void printQuestions(char ***questions, int size) {
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

int main(int argc, char ** argv)
{
  int returnSize, questionsCount;
  printf("running\n");
  char ***data = mapInput(argv[1], &returnSize, &questionsCount);
  /* printf("%s%s", data[0][0], data[1][0]); */
  printQuestions(data, questionsCount);
  return 0;
}
