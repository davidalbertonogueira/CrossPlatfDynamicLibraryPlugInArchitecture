#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>

#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

class shape {
public:
  shape() {};
  virtual ~shape() {};
  virtual void draw() = 0;
};


#endif 