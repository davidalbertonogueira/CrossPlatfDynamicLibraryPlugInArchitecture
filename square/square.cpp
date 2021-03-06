#include <iostream>
#include <map>
#include <string>
#include "square.h"

//#ifdef _DYNAMICLIBRARY_WINDOWS
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


void square::draw() {
std::cout << "Draw square:" << std::endl;
// simple ascii square<\n>
std::cout << std::endl;
std::cout << " ***********" << std::endl;
std::cout << " *         *" << std::endl;
std::cout << " *         *" << std::endl;
std::cout << " *         *" << std::endl;
std::cout << " *         *" << std::endl;
std::cout << " *         *" << std::endl;
std::cout << " ***********" << std::endl;
std::cout << std::endl;
};
square::~square() {};

EXTERN_C_BEGIN
shape *create_object() {
  return new square;
}
void destroy_object(shape * object) {
  delete object;
}

#ifdef _DYNAMICLIBRARY_LINUX
extern std::map <std::string, std::pair<shape*(*)(), void(*)(shape*)> > factory;
class proxy {
public:
  proxy() {
    // register the create_object with the factory
    factory["square"] =
      std::make_pair<shape*(*)(), void(*)(shape*)>(&create_object, &destroy_object);
  }
};
// our one instance of the proxy
proxy p;
#endif
EXTERN_C_END