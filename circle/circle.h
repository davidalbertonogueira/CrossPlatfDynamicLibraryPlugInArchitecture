#ifndef CIRCLE_H
#define CIRCLE_H
#include <TargetApplication/shape.h>

class circle : public shape {
public:
  circle() {};
  ~circle();
  void draw();
};
#endif 