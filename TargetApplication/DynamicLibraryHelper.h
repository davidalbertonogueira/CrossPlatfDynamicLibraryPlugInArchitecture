#ifndef DYNAMICLIBRARYHELPER_H
#define DYNAMICLIBRARYHELPER_H

#if defined(_MSC_VER)
#   define _TARGETAPPLICATION_WINDOWS
#   define _TARGETAPPLICATION_OSNAME "Windows"
#endif

#ifdef __linux__
#   define _TARGETAPPLICATION_LINUX
#   define _TARGETAPPLICATION_OSNAME "Linux"
#endif



#include <iostream>
#include <string>
#ifdef _TARGETAPPLICATION_LINUX
#include <dlfcn.h>
#endif

struct ArgumentsToReceiveFromConfigFile {
  std::string linux_lib_path;// { "../DynamicLibrary/dynamiclibrary.so" };
  std::string windows_dll_GUID;// { "{157d1f66-0110-4b7c-83be-a68340ca2a30}" };
};

bool OpenDynLibPlugIn(ArgumentsToReceiveFromConfigFile const & argument_struct,
                      void ** lib_handle_ptr) {
#ifdef _TARGETAPPLICATION_LINUX
  (*lib_handle_ptr) = dlopen(argument_struct.linux_lib_path.c_str(), RTLD_NOW);

  if ((*lib_handle_ptr)==NULL) {
    fprintf(stderr, "%s\n", dlerror());
    return false;
  }
#endif
  return true;
}

//Returns address to the function which has been loaded with the shared library.
bool GetDynLibFunctionPointer(const std::string & function_name, 
                              void * lib_handle,
                              void ** function_ptr) {
#ifdef _TARGETAPPLICATION_LINUX

  dlerror();    /* Clear any existing error */

  (*function_ptr) = dlsym(lib_handle, function_name.c_str());

  char *error;
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    return false;
  }
#endif
  return true;
}

bool CloseDynLibPlugIn(void * lib_handle) {
#ifdef _TARGETAPPLICATION_LINUX
  int retval = dlclose(lib_handle);
  return (retval == 0) ? true : false;
#endif
  return true;
}


#endif //DYNAMICLIBRARYHELPER_H
