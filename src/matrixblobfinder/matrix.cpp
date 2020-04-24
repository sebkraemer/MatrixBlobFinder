#include "matrix.hpp"

#include <stdexcept>

Matrix::Matrix(int cols, int rows, std::vector<int> values) : cols_(cols), rows_(rows), values_(values) {
    if (cols * rows != values.size()) {
        throw std::runtime_error("invalid number of matrix values given");
    }
}

std::vector<int> const& Matrix::getValues() const {
    return values_;
}

int Matrix::getNumCols() const{
    return cols_;
}

int Matrix::getNumRows() const {
    return rows_;
}
