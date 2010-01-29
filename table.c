#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include <ctype.h>
#include <math.h>

int find_nr_of_literals(char *input);
int find_nr_of_valid_characters(char *input);
void find_literals(char *output, char *input);
void convert_input(char *output, char *input);
void value_literals(char *output, char *formula, char *values, char *literals, int nr_of_literals, int formula_size);
int check_existing(char character, char *formula);
int calculate(char *formula, int formula_size);
int operation(char symbol, int el1, int el2);

int main() {
  char input[10];
  printf("Sisesta valem: ");
  scanf("%[\040A-Zv&=>]", input);

  // Finds the number of literals, the rows count and creates an according array
  int nr_of_literals = find_nr_of_literals(input);
  char literals[nr_of_literals];
  find_literals(literals, input);

  int rows = (int)pow(2, nr_of_literals);
  char array[rows][nr_of_literals];

  int i, j;
  
  // Fills the variables array with true/false values
  for (i = rows - 1; i >= 0; i--) {
    for (j = nr_of_literals; j > 0; j--) {
      int val = (i % (int)pow(2, j)) / (int)(pow(2, j) / 2);
      array[rows - 1 - i][nr_of_literals - j] = val;
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
  int nr_of_valid_characters = find_nr_of_valid_characters(input);
  char formula[nr_of_valid_characters];
  convert_input(formula, input);

  // Prints out the full array
  for (i = 0; i < rows; i++) {
    for (j = 0; j < nr_of_literals; j++) {
      printf("%i ", array[i][j]);
    }

    printf("| ");

    // Prints out the formulas with the boolean of the literals
    char tmp[nr_of_valid_characters];    
    value_literals(tmp, formula, array[i], literals, nr_of_literals, nr_of_valid_characters);
    printf("  %i\n", calculate(tmp, nr_of_valid_characters));
  }
  printf("\n");

  return 0;
}

// Calculates the boolen values and prints out the result
int calculate(char *formula, int formula_size) {
  char operations[] = {'&', 'v', '>', '='};

  // Returns the value of the formula if it has a size of 1
  if (formula_size == 1) { return formula[0]; }

  // Creates an array for the new formula
  char new_formula[formula_size - 2];

  int symbol = 0; // The symbol of the operation
  int i, j;
  int el1, el2;
  for (i = 0; i < 4; i++) { // 4 comes from the number of different operations
    for (j = 0; j < formula_size; j++) {
      if (formula[j] == operations[i]) {
        symbol = operations[i];
        el1 = j - 1;
        el2 = j + 1;
        break;
      }
    }

    if (symbol != 0) { break; }
  }

  int val = operation(symbol, formula[el1], formula[el2]);

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

  return calculate(new_formula, formula_size - 2);
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
      printf("APPI!\n");
      break;
  }

  return val;
}

// Replaces the literals in the formula with their corresponding boolean values
void value_literals(char *output, char *formula, char *values, char* literals, int nr_of_literals, int formula_size) {
  int i, j;
  for (i = 0; i < formula_size ; i++) {
    output[i] = formula[i];

    for (j = 0; j < nr_of_literals; j++) {
      if (output[i] == literals[j]) {
        output[i] = values[j];
      }
    }
  }
}

int find_nr_of_valid_characters(char *input) {
  int i;
  int j = 0;
  for (i = 0; i < strlen(input); i++) {
    if (input[i] != ' ') {
      j++;
    }
  }
  return j;
}

// Converts the input formula into an array and removes any spaces
void convert_input(char *output, char *input) {
  int i;
  int j = 0;
  for (i = 0; i < strlen(input); i++) {
    if (input[i] != ' ') {
      output[j] = input[i];
      j++;
    }
  }
}

// Counts the alphabetic characters in the input formula and returns that number
// does not increase the count if the character repeats
int find_nr_of_literals(char *input) {
  char array[10];

  int elements = 0;
  int i;
  for (i = 0; i < strlen(input); i++) {
    char c = input[i];

    if (c != 'V' && c != 'v' && isalpha(c) != 0) {
      if (check_existing(c, array) == 0) {
        array[elements] = c;
        elements++;
      }
    }
  }

  return elements;
}

void find_literals(char *output, char *input) {
  int elements = 0;
  int i;
  for (i = 0; i < strlen(input); i++) {
    char c = input[i];

    if (c != 'V' && c != 'v' && isalpha(c) != 0) {
      if (check_existing(c, output) == 0) {
        output[elements] = c;
        elements++;
      }
    }
  }
}

// Checks if the element exists in the given array
int check_existing(char character, char *formula) {
  int i;
  int count = 0;
  for (i = 0; i < (int)sizeof(formula) / sizeof(char); i++) {
    if (formula[i] == character) count++;
  }

  return (count != 0);
}
