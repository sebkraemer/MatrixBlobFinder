add_subdirectory(matrixblobfinder)

add_executable(demo main.cpp)
target_link_libraries(
  demo PRIVATE matrixblobfinder project_options project_warnings
  )
