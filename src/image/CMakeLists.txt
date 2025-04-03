add_library(image
  pixels.h pixels.cpp
  lodepng.h lodepng.cpp
)
target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(image PUBLIC core)
