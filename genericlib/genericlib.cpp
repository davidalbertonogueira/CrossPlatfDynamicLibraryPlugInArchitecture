#include "genericlib.h" 
#include<iostream>

//#ifdef _GENERICLIB_WINDOWS
////Defines the entry point for the DLL application.
//BOOL APIENTRY DllMain(HMODULE hModule,
//                      DWORD  ul_reason_for_call,
//                      LPVOID lpReserved
//) {
//  switch (ul_reason_for_call) {
//  case DLL_PROCESS_ATTACH:
//  case DLL_THREAD_ATTACH:
//  case DLL_THREAD_DETACH:
//  case DLL_PROCESS_DETACH:
//    break;
//  }
//  return TRUE;
//}
////Defines the exported functions for the DLL application.
//#endif

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