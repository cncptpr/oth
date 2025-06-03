#include "../std_lib_facilities.h"
int main() {
random_device rd;
mt19937 gen(rd( ));
uniform_int_distribution<int> dis(1, 4);
cout << "ten␣random␣numbers␣beween␣1␣and␣4:␣";
for (int n=0; n<10; ++n)
cout << dis(gen) << ’␣’;
cout << endl; return 0; }
