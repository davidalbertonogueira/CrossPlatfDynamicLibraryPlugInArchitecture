#ifndef CIRCLE_H
#define CIRCLE_H
#include <TargetApplication/shape.h>

#if defined(_MSC_VER)
#   define _DYNAMICLIBRARY_WINDOWS
#   define _DYNAMICLIBRARY_OSNAME "Windows"
#endif

#ifdef __linux__
#   define _DYNAMICLIBRARY_LINUX
#   define _DYNAMICLIBRARY_OSNAME "Linux"
#endif


#ifdef _DYNAMICLIBRARY_WINDOWS
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
  #ifdef _DYNAMICLIBRARY_WINDOWS
    #ifdef CIRCLE_EXPORTS
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


class circle : public shape {
public:
  circle() {};
  ~circle();
  void draw();
};

EXTERN_C_BEGIN
EXPORT_FUNCTION shape *create_object();
EXPORT_FUNCTION void destroy_object(shape * object);
}
#endif 