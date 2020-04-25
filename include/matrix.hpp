#pragma once

#include <iostream>
#include <vector>

class Matrix {
public:
    //! @brief defines a matrix; values are given as row-major
    Matrix(int cols, int rows, std::vector<int> values);

    std::vector<int> const& getValues() const;
    int getNumCols() const;
    int getNumRows() const;

    friend std::ostream& operator <<(std::ostream &os, Matrix const& matrix);

private:
    int const cols_;
    int const rows_;
    std::vector<int> const values_;
};
