#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <functional>
#include "DynamicLibraryHelper.h"
#include "shape.h"

#ifdef _DYNAMICLIBRARY_LINUX
//factory of classes : maps names to pair <constructor, destructor>
std::map <std::string, std::pair<shape*(*)(), void(*)(shape*)> > factory;
#endif

int main(int argc, char **argv) {

  //1) Open dynamic lib; 
  //2) Get functions addresses of that lib and run them
  //3) Close lib handle
  {
    LibHandle lib_handle{ nullptr };
    void(*func_print_str)(const char *a) { nullptr };
    int(*func_a_plus_b)(int const & a, int const & b) { nullptr };

    LibraryInfo library_info;
    library_info.linux_lib_path = "../genericlib/genericlib.so";
    library_info.windows_lib_path = "../x64/Debug/genericlib.dll";

    if (!OpenDynLibPlugIn(library_info, &lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    if (!GetDynLibFunctionPointer("cfunc_print_str", lib_handle, (void**)&func_print_str)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    }
    std::string arg1{ "Hello world!" };
    std::cout << "cfunc_print_str(\"Hello world!\") = ";
    (*func_print_str)(arg1.c_str());

    if (!GetDynLibFunctionPointer("cfunc_a_plus_b", lib_handle, (void**)&func_a_plus_b)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    }

    std::cout << "cfunc_a_plus_b(2,5) = " << (*func_a_plus_b)(2, 5) << std::endl;

    if (!CloseDynLibPlugIn(lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }

  }

  //1) Open dynamic lib; 
  //2) Create class objects using object generator functions 
  //    (Get "create_object" functions addresses of those libs)
  //3) Close lib handle
  //
  //NOTE: library that provides the class derived from shape must 
  //      provide a way to create objects of the new class.
  {
    LibHandle square_lib_handle;
    LibraryInfo square_argument_struct;
    square_argument_struct.linux_lib_path = "../square/square.so";
    square_argument_struct.windows_lib_path = "../x64/Debug/square.dll";
    if (!OpenDynLibPlugIn(square_argument_struct, &square_lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    LibHandle circle_lib_handle;
    LibraryInfo circle_argument_struct;
    circle_argument_struct.linux_lib_path = "../circle/circle.so";
    circle_argument_struct.windows_lib_path = "../x64/Debug/circle.dll";
    if (!OpenDynLibPlugIn(circle_argument_struct, &circle_lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    LibHandle triangle_lib_handle;
    LibraryInfo triangle_argument_struct;
    triangle_argument_struct.linux_lib_path = "../triangle/triangle.so";
    triangle_argument_struct.windows_lib_path = "../x64/Debug/triangle.dll";
    if (!OpenDynLibPlugIn(triangle_argument_struct, &triangle_lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }


    shape *(*square_maker)();
    if (!GetDynLibFunctionPointer("create_object", square_lib_handle, 
      (void**)&square_maker)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    };
    shape *(*circle_maker)();
    if (!GetDynLibFunctionPointer("create_object", circle_lib_handle, 
      (void**)&circle_maker)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    };
    shape *(*triangle_maker)();
    if (!GetDynLibFunctionPointer("create_object", triangle_lib_handle, 
      (void**)&triangle_maker)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    };

    shape *square_shape = static_cast<shape *>((*square_maker)());
    square_shape->draw();
    shape *circle_shape = static_cast<shape *>((*circle_maker)());
    circle_shape->draw();
    shape *triangle_shape = static_cast<shape *>((*triangle_maker)());
    triangle_shape->draw();

    void(*square_destroyer)(shape *);
    if (!GetDynLibFunctionPointer("destroy_object", square_lib_handle, 
      (void**)&square_destroyer)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    };
    void(*circle_destroyer)(shape *);
    if (!GetDynLibFunctionPointer("destroy_object", circle_lib_handle, 
      (void**)&circle_destroyer)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    };
    void(*triangle_destroyer)(shape *);
    if (!GetDynLibFunctionPointer("destroy_object", triangle_lib_handle, 
      (void**)&triangle_destroyer)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    };

    (*square_destroyer)(square_shape);
    (*circle_destroyer)(circle_shape);
    (*triangle_destroyer)(triangle_shape);


    if (!CloseDynLibPlugIn(square_lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
    if (!CloseDynLibPlugIn(circle_lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
    if (!CloseDynLibPlugIn(triangle_lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
  }


#ifdef _DYNAMICLIBRARY_LINUX
  //1) Open dynamic lib; 
  //2) Create class objects using object generator functions, 
  //   that were registered in "factory" map
  //3) Close lib handle
  //
  //NOTE: library that provides the class derived from shape must 
  //      provide a way to create objects of the new class and register that
  //      "create_object" function with the factory automatically, 
  //      using whatever key value the class designer chooses.
  //      This approach is known as “self-registering objects” 
  //      and was introduced by Jim Beveridge
  //      A proxy class is used solely to register the "create_object". 
  //      The registration occurs in the constructor for the class, 
  //      so we need to create only one instance of the proxy class 
  //      to register the create_object.
  //      It is assumed that factory is a global map exported by the main program.
  //      Using gcc / clang, that requires to link with the -rdynamic option to 
  //      force the main program to export its symbols 
  //      to the libraries loaded with dlopen.
  {
    LibHandle square_lib_handle;
    LibraryInfo square_argument_struct;
    square_argument_struct.linux_lib_path = "../square/square.so";
    square_argument_struct.linux_open_as_rtld_lazy = false;
    square_argument_struct.windows_lib_path = "../x64/Debug/square.dll";
    if (!OpenDynLibPlugIn(square_argument_struct, &square_lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    LibHandle circle_lib_handle;
    LibraryInfo circle_argument_struct;
    circle_argument_struct.linux_lib_path = "../circle/circle.so";
    circle_argument_struct.linux_open_as_rtld_lazy = false;
    circle_argument_struct.windows_lib_path = "../x64/Debug/circle.dll";
    if (!OpenDynLibPlugIn(circle_argument_struct, &circle_lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    LibHandle triangle_lib_handle;
    LibraryInfo triangle_argument_struct;
    triangle_argument_struct.linux_lib_path = "../triangle/triangle.so";
    triangle_argument_struct.linux_open_as_rtld_lazy = false;
    triangle_argument_struct.windows_lib_path = "../x64/Debug/triangle.dll";
    if (!OpenDynLibPlugIn(triangle_argument_struct, &triangle_lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    for (const auto & elem : factory) {
      std::cout << elem.first << ":" << std::endl;
      shape * new_shape = (*(elem.second.first))();
      new_shape->draw();

      (*(elem.second.second))(new_shape);
    }

    if (!CloseDynLibPlugIn(square_lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
    if (!CloseDynLibPlugIn(circle_lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
    if (!CloseDynLibPlugIn(triangle_lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
  }
#endif
  return 0;
}

