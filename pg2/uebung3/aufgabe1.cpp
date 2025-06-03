
#include "../std_lib_facilities.h"
#include <typeinfo>
int main() {
  auto a = 42.;
  cout << typeid(a).name() << endl;
  return 0;
}
