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

FetchContent_GetProperties(glfw3)
if(NOT glfw3_POPULATED)
  FetchContent_Populate(glfw3)
  add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Retrieve KumaGL.
FetchContent_Declare(
  KumaGL
  GIT_REPOSITORY https://github.com/ZackaryHudgens/KumaGL
)

FetchContent_GetProperties(KumaGL)
if(NOT KumaGL_POPULATED)
  FetchContent_Populate(KumaGL)
  add_subdirectory(${KumaGL_SOURCE_DIR} ${KumaGL_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Retrieve KumaECS.
FetchContent_Declare(
  KumaECS
  GIT_REPOSITORY https://github.com/ZackaryHudgens/KumaECS
)

FetchContent_GetProperties(KumaECS)
if(NOT KumaECS_POPULATED)
  FetchContent_Populate(KumaECS)
  add_subdirectory(${KumaECS_SOURCE_DIR} ${KumaECS_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Add subdirectories.
add_subdirectory(src)