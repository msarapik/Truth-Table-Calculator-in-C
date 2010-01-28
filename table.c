#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include <ctype.h>
#include <math.h>

short operation(char *f, int a, int b);
short conjunction(int a, int b);
short disjunction(int a, int b);
short implication(int a, int b);
short equivalence(int a, int b);
char *literals(char *s);
int check_existing(char c, char *a, int elements);
int calculate(int *a, int rows, int columns, char *s, int row);

int main() {
  char input[10];
  printf("Sisesta valem: ");
  scanf("%[\040A-Zv&<=>]", input);

  // Finds the number of literals, the rows count and creates an according array
  int nr_of_literals = 0;
  char *return_array = literals(input);

  // Finds out the total number of literals
  while(*return_array != 0) {
    return_array++;
    nr_of_literals++;
  }

  int rows = (int)pow(2, nr_of_literals);
  int array[nr_of_literals][rows];

  int i;
  int j;
  int k;
  // Fills the variables array with true/false values
  for (i = 0; i < nr_of_literals; i++) {
    int l = 0;
    int r = 0;
    int tmp = rows / (int)pow(2, i + 1);
    for (k = 0; k < (int)pow(2, i); k++) {
      for (j = l; j < r + tmp; j++) {
        array[i][j] = 1;
        l++;
      }
      r = l;
      for (j = r; j < r + tmp; j++) {
        array[i][j] = 0;
        l++;
      }
      r = l;
    }
  }

  // Prints out the truth table
  //for (i = 0; i < 4; i++) {
  //  printf("%i %i | %i %i %i\n", a[i], b[i], a[i], operation(input, a[i], b[i]), b[i]);
  //}

  // Extracts the literals from the input
  char* s = input;
  char literals[nr_of_literals];
  int x = 0;
  while (*s != '\0') {
    for (i = 0; i < nr_of_literals; i++) {
      if (isalpha(*s) && *s != 118 && *s != 86 && literals[i] != *s) {
        literals[x] = *s;
        x++;
      }

      s++;
    }
  }

  // Prints out the header
  printf("===========================\n");
  for (i = 0; i < nr_of_literals; i++) {
    printf("%c ", literals[i]);
  }
  printf("| %s", input);
  printf("\n===========================\n");

  // Prints out the full array
  for (j = 0; j < rows; j++) {
    for (i = 0; i < nr_of_literals; i++) {
      printf("%i ", array[i][j]);
    }

    printf("| ");
    calculate(&array[0][0], rows, nr_of_literals, input, j);
  }
  printf("\n");

  return 0;
}

// Calculates the boolean values of the formula depending on the values of the literals
int calculate(int *a, int rows, int columns, char *s, int row) {
  int j;
  for (j = 0; j < strlen(s); j++) {
    printf("+");
  }

  printf("\n");

  return 0;
}

// Counts the alphabetic characters in the input formula and returns that number
// does not increase the count if the character repeats
char *literals(char *s) {
  char array[10];
  int elements = 0;
  while (*s != '\0') {
    char c = *s;
    s++;

    if (c != 'V' && c != 'v' && isalpha(c) != 0) {
      if (check_existing(c, array, elements) == 0) {
        array[elements] = c;
        elements++;
      }
    }
  }
    
  char *literals = NULL;
  literals = (char *)malloc(elements);
  int i;
  for (i = 0; i < elements; i++) {
    literals[i] = array[i];
  }

  return literals;
}

// Checks if the element exists in the given array
int check_existing(char c, char *a, int elements) {
  int i;
  int count = 0;
  for (i = 0; i < elements; i++) {
    if (a[i] == c) count++;
  }

  if (count == 0) {
    return 0;
  }

  return 1;
}

// Checks the input for any logical operation marks and calls the correspondent function
short operation(char *f, int a, int b) {
  if (strstr(f, "&")) return conjunction(a, b);
  if (strstr(f, "v")) return disjunction(a, b);
  if (strstr(f, "<=>")) return equivalence(a, b);
  if (strstr(f, "=>")) return implication(a, b);
  return 0;
}

short conjunction(int a, int b) {
  return (a == 1 && b == 1);
}

short disjunction(int a, int b) {
  return (a == 1 || b == 1);
}

short implication(int a, int b) {
  return (a == 0 || conjunction(a, b));
}

short equivalence(int a, int b) {
  return (a == b);
}
