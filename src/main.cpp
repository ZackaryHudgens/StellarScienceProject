#include <KumaGL/KumaGL.hpp>

#include <GLFW/glfw3.h>

#include <KumaGL/Shader.hpp>
#include <KumaECS/Scene.hpp>

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

  // Run until instructed to close.
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glfwSwapBuffers(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  return 0;
}