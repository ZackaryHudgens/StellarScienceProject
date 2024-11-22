#include "ResourceLoader.hpp"

namespace SSCubes
{
  /******************************************************************************/
  std::map<std::string, std::shared_ptr<KumaGL::Texture>> ResourceLoader::mTextureMap = std::map<std::string, std::shared_ptr<KumaGL::Texture>>();
  std::map<std::string, std::shared_ptr<KumaGL::Shader>> ResourceLoader::mShaderMap = std::map<std::string, std::shared_ptr<KumaGL::Shader>>();
  std::map<std::string, std::shared_ptr<KumaGL::Mesh>> ResourceLoader::mMeshMap = std::map<std::string, std::shared_ptr<KumaGL::Mesh>>();

  /******************************************************************************/
  std::shared_ptr<KumaGL::Texture> ResourceLoader::LoadTexture(const std::string &aPath)
  {
    if (mTextureMap.count(aPath) > 0)
    {
      return mTextureMap.at(aPath);
    }

    auto tex = std::make_shared<KumaGL::Texture>();
    tex->LoadFromFile(aPath);
    mTextureMap.emplace(aPath, tex);
    return tex;
  }

  /******************************************************************************/
  std::shared_ptr<KumaGL::Shader> ResourceLoader::LoadShader(const std::string &aVertexPath, const std::string &aFragmentPath)
  {
    if (mShaderMap.count(aVertexPath) > 0)
    {
      return mShaderMap.at(aVertexPath);
    }

    auto shader = std::make_shared<KumaGL::Shader>();
    shader->LoadFromFiles(aVertexPath, aFragmentPath);
    mShaderMap.emplace(aVertexPath, shader);
    return shader;
  }

  /******************************************************************************/
  std::shared_ptr<KumaGL::Mesh> ResourceLoader::CreateMesh(const std::string &aName)
  {
    if (mMeshMap.count(aName) > 0)
    {
      return mMeshMap.at(aName);
    }

    auto mesh = std::make_shared<KumaGL::Mesh>();
    mMeshMap.emplace(aName, mesh);
    return mesh;
  }
}