#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include <ctype.h>

short operation(char *f, int a, int b);
short conjunction(int a, int b);
short disjunction(int a, int b);
short implication(int a, int b);
short equivalence(int a, int b);
int values(char *s);

int main() {
  char input[10];
  printf("Sisesta valem: \n");
  scanf("%[\040A-Zv&<=>]", input);

  int a[4] = {1, 1, 0, 0};
  int b[4] = {1, 0, 1, 0};

  printf("------------\n");
  printf("A B | %s\n", input);
  printf("------------\n");

  int i;
  for (i = 0; i < 4; i++) {
    printf("%i %i | %i %i %i\n", a[i], b[i], a[i], operation(input, a[i], b[i]), b[i]);
  }

  int bla;
  bla = values(input);
  printf ("%i\n", bla);

  return 0;
}

int values(char *s) {
  printf("------------\n");

  char array[10];
  char *p = s;

  int i = 0;
  while (*p != '\0') {
    char c = *p;
    p++;
    if (isalpha(c) != 0) {
      array[i] = c;
      i++;
    }
  }
    
  return i;
}

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
