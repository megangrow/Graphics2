add_library(objects
  sphere.h sphere.cpp
  triangle.h triangle.cpp
)
target_include_directories(objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(objects PUBLIC core)
