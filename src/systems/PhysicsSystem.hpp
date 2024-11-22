#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <KumaECS/System.hpp>

namespace SSCubes
{
  class PhysicsSystem : KumaECS::System
  {
  public:
    void Operate(KumaECS::Scene &aScene, double dt) override;
  };
}

#endif