add_subdirectory(core)
add_subdirectory(image)
add_subdirectory(objects)
add_subdirectory(materials)
add_subdirectory(textures)

add_library(raytracer
  camera.h camera.cpp
  parser.h parser.cpp
  world.h world.cpp
)
target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(raytracer PUBLIC core image objects materials textures)