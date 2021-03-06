# Matrix blob finder

Finds largest connected shape in a matrix.

Given a matrix of (m x n), containing values of 0 and 1, determines the largest
shape that contains entirely values of 1. The shape must not intersect other
shapes, so all contour lines must be surrounded by 0 values.

Example matrix:

```0 0 0 1 0 0 0
0 1 0 1 1 1 0
1 1 0 1 1 0 0
0 0 0 0 0 0 1
0 0 0 0 1 1 1
```

Here the top right shape is the largest one, containing the most values of 1.

The implmentation is based on labelling algorithm known from computer vision.

"Interesting" files:
* `src/matrixblobfinder/matrixblobfinder.cpp`
* `src/main.cpp`
* `tests/main.cpp`
* `build/test/test.log`

# To see it in action

Before running cmake, make sure `conan` is installed:  `pip install conan` 

Build with cmake as usual, then  run `build/bin/demo` or `ctest` inside the build directory.


# CI status

Travis-CI: [![Build Status](https://travis-ci.com/sebkraemer/MatrixBlobFinder.svg?token=QswUpSbkRSWizBQQEcJT&branch=master)](https://travis-ci.com/sebkraemer/MatrixBlobFinder)

<!-- .. from cpp_starter_project. This does not reflect the this project but
I'd like to add integrate the stats for it.

[![Build status](https://ci.appveyor.com/api/projects/status/ro4lbfoa7n0sy74c/branch/master?svg=true)](https://ci.appveyor.com/project/lefticus/cpp-starter-project/branch/master)

[![codecov](https://codecov.io/gh/lefticus/cpp_starter_project/branch/master/graph/badge.svg)](https://codecov.io/gh/lefticus/cpp_starter_project)

-->
