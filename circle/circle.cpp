#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <functional>
#include "circle.h"

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


void circle::draw() {
  std::cout << "Draw circle:" << std::endl;
  // simple ascii circle<\n>
  std::cout << std::endl;
  std::cout << "      ****" << std::endl;
  std::cout << "    *      *" << std::endl;
  std::cout << "   *        *" << std::endl;
  std::cout << "   *        *" << std::endl;
  std::cout << "   *        *" << std::endl;
  std::cout << "    *      *" << std::endl;
  std::cout << "      ****" << std::endl;
  std::cout << std::endl;
};
circle::~circle() {};

EXTERN_C_BEGIN
shape *create_object() {
  return new circle;
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
    factory["circle"] = 
      std::make_pair<shape*(*)(), void(*)(shape*)>(&create_object, &destroy_object);
  }
};
// our one instance of the proxy
proxy p;
#endif
EXTERN_C_END