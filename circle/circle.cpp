#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <functional>
#include "circle.h"

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
EXTERN_C_END