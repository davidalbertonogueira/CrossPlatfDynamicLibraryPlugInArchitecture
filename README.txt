Work based on:
http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
http://www.linuxjournal.com/article/3687

USAGE:

```cpp
int main(int argc, char **argv) {

  //1) Open dynamic lib; 
  //2) Get functions addresses of that lib and run them
  //3) Close lib handle
  {
    LibHandle lib_handle{ nullptr };
     int(*func_a_plus_b)(int const & a, int const & b) { nullptr };

    LibraryInfo library_info;
    //Use whatever you need for your SO
    library_info.linux_lib_path = "../genericlib/genericlib.so";
    library_info.windows_lib_path = "../x64/Debug/genericlib.dll";

    if (!OpenDynLibPlugIn(library_info, &lib_handle)) {
      std::cerr << "Error opening" << std::endl; return -1;
    }

    if (!GetDynLibFunctionPointer("cfunc_a_plus_b", lib_handle, (void**)&func_a_plus_b)) {
      std::cerr << "Error getting function" << std::endl; return -1;
    }

    std::cout << "cfunc_a_plus_b(2,5) = " << (*func_a_plus_b)(2, 5) << std::endl;

    if (!CloseDynLibPlugIn(lib_handle)) {
      std::cerr << "Error closing" << std::endl; return -1;
    }
  }
  ```
