#include <stdio.h>
void func(int d[3]) {
  for (int f = 0; f < 3; f++)
    d[f] = 42;
}
int main() {
  int d[3];
  func(d);
  int *dptr = d;
  printf("Hi\n");
  for (int f = 0; f < 3; f++)
    printf("%d\n", dptr[f]);
  return 0;
}
