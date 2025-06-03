#include "../std_lib_facilities.h"
#include <complex>
int main() {
  using namespace std::complex_literals;
  complex<double> z = 0. + 1i;
  cout << z*z << endl;
  return 0;
}
