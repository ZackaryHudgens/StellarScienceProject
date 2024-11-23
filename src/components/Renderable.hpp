#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <memory>

#include <KumaGL/Texture.hpp>
#include <KumaGL/Mesh.hpp>
#include <KumaGL/Shader.hpp>

namespace SSCubes
{
  struct Renderable
  {
    std::shared_ptr<KumaGL::Texture> mDiffuseTexture;
    std::shared_ptr<KumaGL::Texture> mSpecularTexture;
    std::shared_ptr<KumaGL::Mesh> mMesh;
    std::shared_ptr<KumaGL::Shader> mShader;

    bool operator<(const Renderable &r) const
    {
      return r.mDiffuseTexture < mDiffuseTexture &&
             r.mSpecularTexture < mSpecularTexture &&
             r.mMesh < mMesh &&
             r.mShader < mShader;
    }
  };
}

#endif