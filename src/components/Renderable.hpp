#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <memory>

#include <KumaGL/Mesh.hpp>
#include <KumaGL/Shader.hpp>

namespace SSCubes
{
  struct Renderable
  {
    std::shared_ptr<KumaGL::Mesh> mMesh;
    std::shared_ptr<KumaGL::Shader> mShader;
  };
}

#endif