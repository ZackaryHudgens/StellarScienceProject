#include "PhysicsSystem.hpp"

#include <KumaECS/Scene.hpp>

#include "Physics.hpp"
#include "Transform.hpp"

namespace SSCubes
{
  /******************************************************************************/
  void PhysicsSystem::Operate(KumaECS::Scene &aScene, double dt)
  {
    for (auto &&entity : GetEntities())
    {
      auto &physicsComponent = aScene.GetComponentForEntity<Physics>(entity);
      auto &transformComponent = aScene.GetComponentForEntity<Transform>(entity);

      physicsComponent.mVelocity += physicsComponent.mAcceleration * dt;
      transformComponent.mPosition += physicsComponent.mVelocity * dt;
    }
  }
}