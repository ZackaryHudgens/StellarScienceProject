#include "RenderSystem.hpp"

#include <map>
#include <vector>

#include <KumaECS/Scene.hpp>

#include "Camera.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"

namespace SSCubes
{
  /******************************************************************************/
  void RenderSystem::Operate(KumaECS::Scene &aScene, double dt)
  {
    // Retrieve all cameras in the scene.
    auto cameras = aScene.GetEntitiesWithComponent<Camera>();

    for (auto &&entity : GetEntities())
    {
      auto &renderableComponent = aScene.GetComponentForEntity<Renderable>(entity);
      auto &transformComponent = aScene.GetComponentForEntity<Transform>(entity);
    }
  }
}