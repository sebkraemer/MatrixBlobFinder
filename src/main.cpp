#include "matrix.hpp"
#include "matrixblobfinder.hpp"

namespace {
// clang-format off
  // Matrix testMatrix{ 6, 3, {
  //   0, 0, 1, 1, 0, 0,
  //   0, 1, 0, 1, 0, 0,
  //   0, 0, 0, 0, 0, 1 }
  //   };

  Matrix testMatrix{ 7, 5, {
    0, 0, 0, 1, 0, 0, 0,
    0, 1, 0, 1, 1, 1, 0,
    1, 1, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 1, 1, 1 }
   };

// clang-format on
}  // namespace

int main(int, const char **) {
    auto const blob = getLargestBlob(findBlobs(testMatrix));
}
