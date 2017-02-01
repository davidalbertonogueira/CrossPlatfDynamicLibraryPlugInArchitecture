#ifndef SIMPLEFUNCTIONSLIB_H
#define SIMPLEFUNCTIONSLIB_H

#if defined(_MSC_VER)
#   define _SIMPLEFUNCTIONSLIB_WINDOWS
#   define _SIMPLEFUNCTIONSLIB_OSNAME "Windows"
#endif

#ifdef __linux__
#   define _SIMPLEFUNCTIONSLIB_LINUX
#   define _SIMPLEFUNCTIONSLIB_OSNAME "Linux"
#endif

#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

#ifdef _SIMPLEFUNCTIONSLIB_WINDOWS
#include <windows.h>
#endif

#include <string>

// Methods that we want to expose from a library
void func_print_str(const std::string & a);
int  func_a_plus_b(int const & a, int const & b);

//Equivalent c-method versions of the previous ones
EXTERN_C_BEGIN
void cfunc_print_str(const char *a);
int cfunc_a_plus_b(int const & a, int const & b);
EXTERN_C_END

#endif //SIMPLEFUNCTIONSLIB_H
