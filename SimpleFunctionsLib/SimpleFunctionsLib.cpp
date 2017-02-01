#include "SimpleFunctionsLib.h"
#include<iostream>

void func_print_str(const std::string & a) {
  std::cout << "cfunc called with arg = " << a << std::endl;
}
int  func_a_plus_b(int const & a, int const & b) {
  return a + b;
};

EXTERN_C_BEGIN
void cfunc_print_str(const char *a) {
  return func_print_str(std::string(a));
};


int cfunc_a_plus_b(int const & a, int const & b) {
  return func_a_plus_b(a, b);
};
EXTERN_C_END