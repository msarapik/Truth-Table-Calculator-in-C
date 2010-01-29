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
char *convert_input(char *formula);
char value_literals(char *formula, int *values, char *literals, int line);
int check_existing(char c, char *a, int elements);

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
  int array[rows][nr_of_literals];

  int i;
  int j;
  
  // Fills the variables array with true/false values
  for (i = rows - 1; i >= 0; i--) {
    for (j = nr_of_literals; j > 0; j--) {
      int val = (i % (int)pow(2, j)) / (int)(pow(2, j) / 2);
      array[rows - 1 - i][nr_of_literals - j] = val;
    }
  }

  // Extracts the literals from the input
  char* s = input;
  char literals[nr_of_literals];
  int x = 0;
  while (*s != '\0') {
    for (i = 0; i < nr_of_literals; i++) {
      if (isalpha(*s) && *s != 'v' && *s != 'V' && literals[i] != *s) {
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

  // Converts the input and gets the new size of the converted formula
  char *formula = convert_input(input);
  int formula_size = 0;
  while(*formula != 0) {
    formula++;
    formula_size++;
  }

  // Prints out the full array
  for (i = 0; i < rows; i++) {
    for (j = 0; j < nr_of_literals; j++) {
      printf("%i ", array[i][j]);
    }

    printf("| ");

    // Prints out the formulas with the boolean of the literals
    value_literals(formula, array[i], literals, nr_of_literals);
  }
  printf("\n");

  return 0;
}

// Replaces the literals in the formula with their corresponding boolean values
char value_literals(char *formula, int *values, char *literals, int nr_of_literals) {
  int i;
  for (i = 0; i < nr_of_literals; i++) {
    printf("-- %i", values[i]);
  }
  printf("\n");

  return 0;
}

// Converts the input formula into an array and removes any spaces
char *convert_input(char *formula) {
  char *new_formula = NULL;
  new_formula = (char *)malloc(sizeof(*formula));

  int i = 0;
  while (*formula != '\0') {
    if (*formula != ' ') {
      new_formula[i] = *formula;
      i++;
    }

    formula++;
  }
 
  return new_formula;
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
