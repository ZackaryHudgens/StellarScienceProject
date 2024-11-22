#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <KumaECS/System.hpp>

namespace SSCubes
{
  class RenderSystem : public KumaECS::System
  {
  public:
    void Operate(KumaECS::Scene &aScene, double dt) override;
  };
}

#endif