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
    std::shared_ptr<KumaGL::Texture> mTexture;
    std::shared_ptr<KumaGL::Mesh> mMesh;
    std::shared_ptr<KumaGL::Shader> mShader;

    bool operator<(const Renderable &r) const
    {
      return r.mTexture < mTexture && r.mMesh < mMesh && r.mShader < mShader;
    }
  };
}

#endif