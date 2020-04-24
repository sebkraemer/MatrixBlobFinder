add_library(matrixblobfinder
    matrix.cpp
    getNeighbors.cpp
    matrixblobfinder.cpp
    #${CMAKE_SOURCE_DIR}/include/matrix.hpp
    )

set_target_properties(matrixblobfinder PROPERTIES CXX_STANDARD 17)

target_include_directories(matrixblobfinder PUBLIC ${CMAKE_SOURCE_DIR}/include)
