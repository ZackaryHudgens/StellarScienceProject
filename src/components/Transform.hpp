#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <KumaGL/Vec3.hpp>

namespace SSCubes
{
  struct Transform
  {
    KumaGL::Vec3 mPosition;
    KumaGL::Vec3 mRotation;
    KumaGL::Vec3 mScale = KumaGL::Vec3(1, 1, 1);
  };
}

#endif