#include "RenderSystem.hpp"

#include <map>
#include <vector>
#include <iostream>

#include <KumaGL/Mat4.hpp>
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

    // set shader transforms;
    // TODO: make this use the camera position
    KumaGL::Mat4 view;
    view.LookAt(KumaGL::Vec3(0, 0, 0), KumaGL::Vec3(0, 0, -1),
                KumaGL::Vec3(0, 1, 0));

    KumaGL::Mat4 proj;
    proj.Perspective(45, 1280, 720, 0.1, 100);

    // Map each renderable component to a list of matching entities.
    std::map<Renderable, std::vector<KumaECS::Entity>> renderMap;
    for (auto &&entity : GetEntities())
    {
      auto &renderableComponent = aScene.GetComponentForEntity<Renderable>(entity);
      renderMap[renderableComponent].emplace_back(entity);
    }

    for (auto &&renderPair : renderMap)
    {
      // Store each entity's transformation matrix in a vector.
      std::vector<KumaGL::Mat4> matrices;
      for (auto &&entity : renderPair.second)
      {
        auto &transform = aScene.GetComponentForEntity<Transform>(entity);
        KumaGL::Mat4 matrix;
        matrix.Translate(transform.mPosition);
        matrix.Rotate(transform.mRotation);
        matrix.Scale(transform.mScale);
        matrices.emplace_back(matrix);
      }

      // Copy the matrix data into the mesh's instance buffer.
      renderPair.first.mMesh->mInstanceBuffer.CopyData(
          GL_ARRAY_BUFFER,
          matrices.size() * sizeof(KumaGL::Mat4),
          matrices.data(),
          GL_DYNAMIC_DRAW);

      // Bind the shader and draw the mesh using instanced rendering.
      renderPair.first.mShader->SetMat4("viewMatrix", view);
      renderPair.first.mShader->SetMat4("projectionMatrix", proj);

      renderPair.first.mShader->Bind();
      renderPair.first.mMesh->DrawInstanced(matrices.size());
      renderPair.first.mShader->Unbind();
    }
  }
}