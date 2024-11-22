#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <KumaGL/Vec3.hpp>

namespace SSCubes
{
  struct Physics
  {
    KumaGL::Vec3 mVelocity;
    KumaGL::Vec3 mAcceleration;
  };
}

#endif