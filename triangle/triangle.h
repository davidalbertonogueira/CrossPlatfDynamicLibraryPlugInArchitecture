#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <TargetApplication/shape.h>

class triangle : public shape {
public:
  triangle() {};
  ~triangle();
  void draw();
};
#endif 