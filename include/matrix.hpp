#pragma once

#include <iostream>
#include <vector>

class Matrix {
public:
    //! @brief defines a matrix; values are given as row-major
    Matrix(int rows, int cols, std::vector<int> values);

    std::vector<int> const& getValues() const;
    int getNumCols() const;
    int getNumRows() const;

    friend std::ostream& operator <<(std::ostream &os, Matrix const& matrix);

private:
    int const rows_;
    int const cols_;
    std::vector<int> const values_;
};
