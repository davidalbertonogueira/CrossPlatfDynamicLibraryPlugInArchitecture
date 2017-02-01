#include <iostream>
#include <map>
#include <string>
#include "triangle.h"

void triangle::draw() {
std::cout << "Draw triangle:" << std::endl;
// simple ascii triangle<\n>
std::cout << std::endl;
std::cout << "      *" << std::endl;
std::cout << "     * *" << std::endl;
std::cout << "    *   *" << std::endl;
std::cout << "   *     *" << std::endl;
std::cout << "  *       *" << std::endl;
std::cout << " *         *" << std::endl;
std::cout << "*************" << std::endl;
std::cout << std::endl;
};
triangle::~triangle() {};

EXTERN_C_BEGIN
shape *create_object() {
  return new triangle;
}
void destroy_object(shape * object) {
  delete object;
}

extern std::map <std::string, std::pair<shape*(*)(), void(*)(shape*)> > factory;
class proxy {
public:
  proxy() {
    // register the create_object with the factory
    factory["triangle"] = 
    std::make_pair<shape*(*)(), void(*)(shape*)>(&create_object, &destroy_object);
  }
};
// our one instance of the proxy
proxy p;
EXTERN_C_END