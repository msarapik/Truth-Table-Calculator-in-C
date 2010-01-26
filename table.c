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
int literals(char *s);
int check_existing(char c, char *a, int elements);
//int literal_values(int rows, int col_nr, int array);

int main() {
  char input[10];
  printf("Sisesta valem: ");
  scanf("%[\040A-Zv&<=>]", input);

  //int a[4] = {1, 1, 0, 0};
  //int b[4] = {1, 0, 1, 0};

  int nr_of_literals;
  nr_of_literals = literals(input);
  int rows = (int)pow(2, nr_of_literals);
  int array[nr_of_literals][rows];

  int i;
  int j;
  int k;
  int l;
  int r;
  // Fills the variables array with true/false values
  for (i = 0; i < nr_of_literals; i++) {
    l = 0;
    r = 0;
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

  // Prints out the header of the truth table
  //printf("------------\n");
  //printf("A B | %s\n", input);
  //printf("------------\n");

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

  // Prints out the 2nd header
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
    printf("|\n");
  }
  printf("\n");

  return 0;
}

// Counts the alphabetic characters in the input formula and returns that number
// does not increase the count if the character repeats
int literals(char *s) {
  char *p = s;
  char array[10];
  int elements = 0;
  int i = 0;
  while (*p != '\0') {
    char c = *p;
    p++;

    if (c != 118 && c != 86 && isalpha(c) != 0) {
      if (check_existing(c, array, elements) == 0) {
        array[elements] = c;
        i++;
        elements++;
      }
    }
  }
    
  return i;
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
