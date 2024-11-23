#include <KumaGL/KumaGL.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <random>

#include <KumaECS/Signature.hpp>
#include <KumaECS/Scene.hpp>

#include "Camera.hpp"
#include "Light.hpp"
#include "Physics.hpp"
#include "Transform.hpp"
#include "Renderable.hpp"

#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"

#include "ResourceLoader.hpp"

/******************************************************************************/
void FramebufferSizeCallback(GLFWwindow *aWindow, int aWidth, int aHeight)
{
  glViewport(0, 0, aWidth, aHeight);
}

/******************************************************************************/
void ErrorCallback(int aCode, const char *aDescription)
{
  std::cout << "GLFW error code: " << aCode << std::endl;
  std::cout << "Description: " << aDescription << std::endl;
}

/******************************************************************************/
GLFWwindow *CreateWindow()
{
  GLFWwindow *window = nullptr;

  // Initialize GLFW.
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW!" << std::endl;
    return window;
  }

  // Set the desired OpenGL version to 3.3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Use the core profile only; this removes backwards-compatible features
  // that are no longer needed for the engine.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Enable forward compatibility; this removes all deprecated features
  // in the desired version of OpenGL (3.3).
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  // Enable double buffering.
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

  // Create a new window.
  window = glfwCreateWindow(1280, 720, "cubes", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cout << "Failed to create window!" << std::endl;
    return window;
  }

  // Make the context current.
  glfwMakeContextCurrent(window);

  // Set any GLFW callbacks.
  glfwSetFramebufferSizeCallback(window, &FramebufferSizeCallback);
  glfwSetErrorCallback(&ErrorCallback);

  return window;
}

/******************************************************************************/
bool InitializeGL()
{
  if (!KumaGL::InitKumaGL(glfwGetProcAddress))
  {
    std::cout << "Failed to initialize KumaGL!" << std::endl;
    return false;
  }

  // Set up global OpenGL state.
  glEnable(GL_DEPTH_TEST);

  return true;
}

/******************************************************************************/
SSCubes::Transform CreateRandomTransform(std::random_device &aDevice)
{
  SSCubes::Transform t;

  std::mt19937 generator(aDevice());
  std::uniform_real_distribution<> dist(-25, 25);

  t.mPosition.x = dist(generator);
  t.mPosition.y = dist(generator);
  t.mPosition.z = dist(generator) - 50;

  return t;
}

/******************************************************************************/
float CreateRandomGravity(std::random_device &aDevice)
{
  std::mt19937 generator(aDevice());
  std::uniform_real_distribution<> dist(-9.81, -0.5);

  return dist(generator);
}

/******************************************************************************/
std::unique_ptr<KumaECS::Scene> CreateScene()
{
  auto newScene = std::make_unique<KumaECS::Scene>(10001);

  // Register component types.
  newScene->RegisterComponentType<SSCubes::Camera>(1);
  newScene->RegisterComponentType<SSCubes::Light>(1);
  newScene->RegisterComponentType<SSCubes::Physics>(10000);
  newScene->RegisterComponentType<SSCubes::Transform>(10001);
  newScene->RegisterComponentType<SSCubes::Renderable>(10000);

  // Register systems.
  KumaECS::Signature physicsSignature;
  newScene->AddComponentToSignature<SSCubes::Physics>(physicsSignature);
  newScene->AddComponentToSignature<SSCubes::Transform>(physicsSignature);
  newScene->RegisterSystemType<SSCubes::PhysicsSystem>(physicsSignature);

  KumaECS::Signature renderSignature;
  newScene->AddComponentToSignature<SSCubes::Renderable>(renderSignature);
  newScene->AddComponentToSignature<SSCubes::Transform>(renderSignature);
  newScene->RegisterSystemType<SSCubes::RenderSystem>(renderSignature);

  // Create a bunch of cubes and place them randomly.
  std::random_device rd;
  for (size_t i = 0; i < 9999; i++)
  {
    auto entity = newScene->CreateEntity();

    auto &physics = newScene->AddComponentToEntity<SSCubes::Physics>(entity);
    physics.mAcceleration.y = CreateRandomGravity(rd);

    auto &renderable = newScene->AddComponentToEntity<SSCubes::Renderable>(entity);
    renderable.mDiffuseTexture = SSCubes::ResourceLoader::LoadTexture("resources/textures/diffuse.png");
    renderable.mSpecularTexture = SSCubes::ResourceLoader::LoadTexture("resources/textures/specular.png");
    renderable.mMesh = SSCubes::ResourceLoader::CreateMesh("cube");
    renderable.mShader = SSCubes::ResourceLoader::LoadShader("resources/shaders/CubeShader.vert",
                                                             "resources/shaders/CubeShader.frag");

    auto &transform = newScene->AddComponentToEntity<SSCubes::Transform>(entity);
    transform = CreateRandomTransform(rd);
  }

  // Create and add a camera.
  auto camera = newScene->CreateEntity();
  newScene->AddComponentToEntity<SSCubes::Transform>(camera);

  auto &cameraComponent = newScene->AddComponentToEntity<SSCubes::Camera>(camera);
  cameraComponent.mFOV = 45;
  cameraComponent.mNearPlane = 0.1;
  cameraComponent.mFarPlane = 100;

  // Create and add a light.
  auto light = newScene->CreateEntity();
  auto &lightTransform = newScene->AddComponentToEntity<SSCubes::Transform>(light);
  lightTransform.mPosition = KumaGL::Vec3(10, 10, 0);

  auto &lightComponent = newScene->AddComponentToEntity<SSCubes::Light>(light);
  lightComponent.mColor = KumaGL::Vec3(0.9, 0.9, 0.9);

  return std::move(newScene);
}

/******************************************************************************/
void LoadResources()
{
  auto cubeDiffuse = SSCubes::ResourceLoader::LoadTexture("resources/textures/diffuse.png");
  auto cubeSpecular = SSCubes::ResourceLoader::LoadTexture("resources/textures/specular.png");

  // Use GL_NEAREST to prevent blurring from using a small texture.
  cubeDiffuse->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  cubeDiffuse->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  cubeDiffuse->GenerateMipmap();

  cubeSpecular->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  cubeSpecular->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  cubeSpecular->GenerateMipmap();

  auto cubeShader = SSCubes::ResourceLoader::LoadShader("resources/shaders/CubeShader.vert",
                                                        "resources/shaders/CubeShader.frag");
  cubeShader->SetFloat("shininess", 255);

  auto cubeMesh = SSCubes::ResourceLoader::CreateMesh("cube");
  cubeMesh->InitCube();
}

/******************************************************************************/
int main()
{
  // Create a GLFW window.
  auto window = CreateWindow();
  if (window == nullptr)
  {
    return -1;
  }

  // Initialize OpenGL.
  auto success = InitializeGL();
  if (!success)
  {
    return -1;
  }

  // Create the scene.
  LoadResources();
  auto gameScene = CreateScene();

  // Run until instructed to close.
  double prevTime = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    double currTime = glfwGetTime();
    double dt = currTime - prevTime;
    prevTime = currTime;

    glfwPollEvents();
    glfwSwapBuffers(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gameScene->OperateSystems(dt);
  }

  return 0;
}