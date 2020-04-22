add_executable(matrix_blob_finder main.cpp)
target_link_libraries(
  matrix_blob_finder PRIVATE project_options project_warnings
                CONAN_PKG::fmt CONAN_PKG::spdlog)
