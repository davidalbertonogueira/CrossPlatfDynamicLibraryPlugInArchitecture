#include <iostream>
#include <map>
#include <string>
#include "square.h"

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
EXTERN_C_END