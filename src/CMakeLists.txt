list(APPEND SOURCE_FILES
  main.cpp
  ResourceLoader.cpp
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

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")