#include "RenderSystem.hpp"

#include <map>
#include <vector>
#include <iostream>

#include <KumaGL/Mat4.hpp>
#include <KumaECS/Scene.hpp>

#include "Camera.hpp"
#include "Light.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"

namespace SSCubes
{
  /******************************************************************************/
  void RenderSystem::Operate(KumaECS::Scene &aScene, double dt)
  {
    // Retrieve the first camera in the scene.
    KumaECS::Signature cameraSignature;
    aScene.AddComponentToSignature<Camera>(cameraSignature);
    aScene.AddComponentToSignature<Transform>(cameraSignature);

    auto cameras = aScene.GetEntitiesWithSignature(cameraSignature);
    KumaECS::Entity camera = -1;
    for (auto &&entity : cameras)
    {
      camera = entity;
      break;
    }

    // Retrieve the first light in the scene (the shader only allows for one light).
    KumaECS::Signature lightSignature;
    aScene.AddComponentToSignature<Light>(lightSignature);
    aScene.AddComponentToSignature<Transform>(lightSignature);

    auto lights = aScene.GetEntitiesWithSignature(lightSignature);
    KumaECS::Entity light = -1;
    for (auto &&entity : lights)
    {
      light = entity;
      break;
    }

    // Calculate view and projection matrices, as well as the camera's position.
    KumaGL::Mat4 view;
    KumaGL::Mat4 proj;
    KumaGL::Vec3 cameraPosition;
    if (camera >= 0)
    {
      // Set the view and projection matrices.
      auto &cameraTransform = aScene.GetComponentForEntity<Transform>(camera);
      auto &cameraComponent = aScene.GetComponentForEntity<Camera>(camera);
      view.LookAt(cameraTransform.mPosition,
                  cameraTransform.mPosition + KumaGL::Vec3(0, 0, -1),
                  KumaGL::Vec3(0, 1, 0));

      proj.Perspective(cameraComponent.mFOV,
                       1280,
                       720,
                       cameraComponent.mNearPlane,
                       cameraComponent.mFarPlane);

      cameraPosition = cameraTransform.mPosition;
    }

    // Retrieve the light properties.
    KumaGL::Vec3 lightPosition;
    KumaGL::Vec3 lightColor;
    if (light >= 0)
    {
      // Set the view and projection matrices.
      auto &lightTransform = aScene.GetComponentForEntity<Transform>(light);
      auto &lightComponent = aScene.GetComponentForEntity<Light>(light);

      lightPosition = lightTransform.mPosition;
      lightColor = lightComponent.mColor;
    }

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

      // Bind textures.
      renderPair.first.mDiffuseTexture->Bind(GL_TEXTURE0);
      renderPair.first.mSpecularTexture->Bind(GL_TEXTURE1);

      // Set shader uniforms.
      renderPair.first.mShader->SetMat4("viewMatrix", view);
      renderPair.first.mShader->SetMat4("projectionMatrix", proj);
      renderPair.first.mShader->SetInt("diffuseTexture", 1);
      renderPair.first.mShader->SetInt("specularTexture", 0);
      renderPair.first.mShader->SetVec3("viewPos", cameraPosition);
      renderPair.first.mShader->SetVec3("lightColor", lightColor);
      renderPair.first.mShader->SetVec3("lightPos", lightPosition);

      // Draw the mesh using instanced rendering.
      renderPair.first.mShader->Bind();
      renderPair.first.mMesh->DrawInstanced(matrices.size());
      renderPair.first.mShader->Unbind();
    }
  }
}