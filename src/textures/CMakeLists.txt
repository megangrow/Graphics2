add_library(textures
        image.h image.cpp
        solid.h solid.cpp
        gradient.h gradient.cpp
        checkerboard.h checkerboard.cpp
        normal.h normal.cpp
        custom.h custom.cpp
)
target_include_directories(textures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(textures PUBLIC core)
