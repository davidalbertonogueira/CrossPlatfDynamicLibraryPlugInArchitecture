#ifndef GENERICLIB_H
#define GENERICLIB_H

#if defined(_MSC_VER)
#   define _GENERICLIB_WINDOWS
#   define _GENERICLIB_OSNAME "Windows"
#endif

#ifdef __linux__
#   define _GENERICLIB_LINUX
#   define _GENERICLIB_OSNAME "Linux"
#endif


#ifdef _GENERICLIB_WINDOWS
#include <SDKDDKVer.h>
// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, 
// include WinSDKVer.h and set the _WIN32_WINNT macro to the 
// platform you wish to support before including SDKDDKVer.h.


#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#endif

#ifdef __cplusplus
  #define EXTERN_C_BEGIN extern "C" {
  #define EXTERN_C_END }
  #ifdef _GENERICLIB_WINDOWS
    #ifdef GENERICLIB_EXPORTS
      #define DLL_API __declspec(dllexport)
    #else
      #define DLL_API __declspec(dllimport)
    #endif
    #define EXPORT_FUNCTION DLL_API
  #else
    #define EXPORT_FUNCTION 
  #endif
#else
  #define EXTERN_C_BEGIN
  #define EXTERN_C_END
  #define EXPORT_FUNCTION 
#endif


#include <string>

// Methods that we want to expose from a library
void func_print_str(const std::string & a);
int  func_a_plus_b(int const & a, int const & b);

//Equivalent c-method versions of the previous ones
EXTERN_C_BEGIN
EXPORT_FUNCTION void cfunc_print_str(const char *a);
EXPORT_FUNCTION int cfunc_a_plus_b(int const & a, int const & b);
EXTERN_C_END


#endif //GENERICLIB_H