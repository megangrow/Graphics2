add_library(materials
  diffuse.h diffuse.cpp
  disperse.h disperse.cpp
  glass.h glass.cpp
  lambertian.h lambertian.cpp
  metallic.h metallic.cpp
  specular.h specular.cpp
  isotropic.h isotropic.cpp
)
target_include_directories(materials PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(materials PUBLIC core)
