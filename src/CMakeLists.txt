list(APPEND SOURCE_FILES
  main.cpp
  systems/PhysicsSystem.cpp
  systems/RenderSystem.cpp
)

add_executable(StellarScienceCubes ${SOURCE_FILES})
target_link_libraries(StellarScienceCubes PRIVATE
  glfw
  KumaGL
  KumaECS
)
target_include_directories(StellarScienceCubes PUBLIC
  systems
  components
)