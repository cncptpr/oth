#include "./aufgabe1.h"
int main(void) {
  int i, j, k, x[10000];
  for (i = 0; i < 10000; ++i)
    x[i] = i;
  cout << "Enter integer in 0..9999: ";
  cin >> k;
  tester(x, k);
  return 0;
}
