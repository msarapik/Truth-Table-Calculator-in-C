#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include <ctype.h>
#include <math.h>

char *literals(char *s);
char *convert_input(char *formula);
char *value_literals(int formula_size, char *formula, int *values, char *literals, int line);
int check_existing(char c, char *a, int elements);
int calculate(char *formula);
int operation(char symbol, int el1, int el2);

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
  int formula_size = strlen(formula);

  // Prints out the full array
  for (i = 0; i < rows; i++) {
    for (j = 0; j < nr_of_literals; j++) {
      printf("%i ", array[i][j]);
    }

    printf("| ");

    // Prints out the formulas with the boolean of the literals

    char *tmp;
    tmp = value_literals(formula_size, formula, array[i], literals, nr_of_literals);
    printf("%i", calculate(tmp));
  }
  printf("\n");

  return 0;
}

// Calculates the boolen values and prints out the result
int calculate(char *formula) {
  char operations[] = {'&', 'v', '>', '='};

  // Makes a copy of the formula
  char *new_formula = NULL;
  int formula_size = strlen(formula);

  int i;
  for (i = 0; i < 5; i++) {
    printf("%i\n", formula[i]);
  }
  // Returns the value of the formula if it has a size of 1
  if (formula_size == 1) { return formula[0]; }

  // Creates an array for the new formula
  new_formula = (char *)malloc(formula_size - 2);

  char symbol;// = NULL; // The symbol of the operation
  //int i;
  int j;
  int el1;
  int el2;
  for (i = 0; i < 4; i++) { // 4 comes from the number of different operations
    for (j = 0; j < formula_size; j++) {
      if (formula[j] == operations[i]) {
        symbol = operations[i];
        el1 = j - 1;
        el2 = j + 1;
        break;
      }
    }

    if (symbol) { break; }
  }
 
  int val;
  val = operation(symbol, formula[el1], formula[el2]);

  i = 0;
  for (j = 0; j < formula_size; j++) {
    if (j >= el1 && j <= el2) {
      if (j == el1) { 
        new_formula[i] = val; 
        i++;
      }
    } else {
      new_formula[i] = formula[j];
      i++;
    }
  }

  return calculate(new_formula);
}

// Performs the operation between el1 and el2
int operation(char symbol, int el1, int el2) {
  int val;
  switch(symbol) {
    case '&': 
      val = el1 && el2;
      break;
    case 'v': 
      val = el1 || el2;
      break;
    case '>': 
      val = !el1 || el2;
      break;
    case '=': 
      val = el1 == el2;
      break;
    default:
      printf("APPI!");
      break;
  }

  return val;
}

// Replaces the literals in the formula with their corresponding boolean values
char *value_literals(int formula_size, char *formula, int *values, char *literals, int nr_of_literals) {
  char *bumpala = NULL;
  bumpala = (char *)malloc(formula_size);
  strcpy(bumpala, formula);
  int i;
  int j;
  for (i = 0; i < formula_size ; i++) {
    for (j = 0; j < nr_of_literals; j++) {
      if (bumpala[i] == literals[j]) {
        bumpala[i] = values[j];
      }
    }
  }

  return bumpala;
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
