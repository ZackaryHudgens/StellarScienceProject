#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include <string>
#include <map>
#include <memory>

#include <KumaGL/Texture.hpp>
#include <KumaGL/Mesh.hpp>
#include <KumaGL/Shader.hpp>

namespace SSCubes
{
  class ResourceLoader
  {
  public:
    static std::shared_ptr<KumaGL::Texture> LoadTexture(const std::string &aPath);
    static std::shared_ptr<KumaGL::Shader> LoadShader(const std::string &aVertexPath, const std::string &aFragmentPath);
    static std::shared_ptr<KumaGL::Mesh> CreateMesh(const std::string &aName);

  private:
    static std::map<std::string, std::shared_ptr<KumaGL::Texture>> mTextureMap;
    static std::map<std::string, std::shared_ptr<KumaGL::Shader>> mShaderMap;
    static std::map<std::string, std::shared_ptr<KumaGL::Mesh>> mMeshMap;
  };

  std::map<std::string, std::shared_ptr<KumaGL::Texture>> ResourceLoader::mTextureMap = std::map<std::string, std::shared_ptr<KumaGL::Texture>>();
  std::map<std::string, std::shared_ptr<KumaGL::Shader>> ResourceLoader::mShaderMap = std::map<std::string, std::shared_ptr<KumaGL::Shader>>();
  std::map<std::string, std::shared_ptr<KumaGL::Mesh>> ResourceLoader::mMeshMap = std::map<std::string, std::shared_ptr<KumaGL::Mesh>>();
}

#endif