cmake_minimum_required(VERSION 3.14)
project(StellarScienceProject
  VERSION 0.0.1
  LANGUAGES CXX
)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Retrieve GLFW.
FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw3)

# Retrieve KumaGL.
FetchContent_Declare(
  KumaGL
  GIT_REPOSITORY https://github.com/ZackaryHudgens/KumaGL
)
FetchContent_MakeAvailable(KumaGL)

# Retrieve KumaECS.
FetchContent_Declare(
  KumaECS
  GIT_REPOSITORY https://github.com/ZackaryHudgens/KumaECS
)
FetchContent_MakeAvailable(KumaECS)

# Add subdirectories.
add_subdirectory(src)