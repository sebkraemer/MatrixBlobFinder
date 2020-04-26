#include "matrix.hpp"

#include <stdexcept>

Matrix::Matrix(int rows, int cols, std::vector<int> values) : rows_(rows), cols_(cols), values_(values) {
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

std::ostream& operator <<(std::ostream &os, Matrix const& matrix)
{
    auto const& values = matrix.getValues();
    for (int r = 0, idx = 0; r < matrix.getNumRows(); ++r)
    {
        int c = 0;
        for (; c < matrix.getNumCols(); ++c, ++idx)
        {
            os << ' ' << values[r*matrix.getNumCols()+c];
        }
        if(c == matrix.getNumCols())
        {
            os << '\n';
        }
    }
    return os;
}
