#include "matrixblobfinder.hpp"

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

//! @brief helper method to generate list of which neighbors to check
std::vector<Point> getNeighbors(IndexType row, IndexType col, IndexType maxRows, IndexType maxCols)
{
    std::vector<Point> neighbors;

    // full 9-neighborhood for entries not at the border
    if (row > 0 && row < maxRows - 1 && col > 0 && col < maxCols - 1)
    {
        neighbors.push_back({row - 1, col - 1});
        neighbors.push_back({row - 1, col });
        neighbors.push_back({row - 1, col + 1});
        neighbors.push_back({row, col - 1});
        neighbors.push_back({row, col + 1});
        neighbors.push_back({row + 1, col - 1});
        neighbors.push_back({row + 1, col });
        neighbors.push_back({row + 1, col + 1});
    }

    // border cases

    // top left corner
    else if (row == 0 && col == 0)
    {
        if (row < maxRows - 1)
        {
            neighbors.push_back({row + 1, col});
            if (col < maxCols - 1)
            {
                neighbors.push_back({row + 1, col + 1});
            }
        }
        if (col < maxCols - 1)
        {
            neighbors.push_back({row, col + 1});
        }
    }

    // top center
    else if (row == 0 && col < maxCols - 1)
    {
        if (row < maxRows - 1)
        {
            neighbors.push_back({row + 1, col - 1});
            neighbors.push_back({row + 1, col});
            neighbors.push_back({row + 1, col + 1});
        }
        neighbors.push_back({row, col - 1});
        neighbors.push_back({row, col + 1});
    }
    // top right
    else if (row == 0 && col == maxCols - 1)
    {
        if (row < maxRows - 1)
        {
            neighbors.push_back({row + 1, col - 1});
            neighbors.push_back({row + 1, col});
        }
        neighbors.push_back({row, col - 1});
    }

    // middle
    else if (row > 0 && row < maxRows - 1)
    {
        if (col == 0)
        {
            if (maxCols > 1)
            {
                neighbors.push_back({row - 1, col + 1});
                neighbors.push_back({row, col + 1});
                neighbors.push_back({row + 1, col + 1});
            }
        }
        else  // col == maxCols - 1
        {
            neighbors.push_back({row - 1, col - 1});
            neighbors.push_back({row, col - 1});
            neighbors.push_back({row + 1, col - 1});
        }
        // left and right
        neighbors.push_back({row - 1, col});
        neighbors.push_back({row + 1, col});
    }

    // left bottom
    else if (row == maxRows - 1 && col == 0)
    {
        if (row > 0)
        {
            neighbors.push_back({row - 1, col});
            if (col < maxCols - 1)
            {
                neighbors.push_back({row - 1, col + 1});
            }
        }
        if (col < maxCols - 1)
        {
            neighbors.push_back({row, col + 1});
        }
    }

    // center bottom
    else if (row == maxRows - 1 && col < maxCols - 1)
    {
        if (row > 0)
        {
            neighbors.push_back({row - 1, col - 1});
            neighbors.push_back({row - 1, col});
            neighbors.push_back({row - 1, col + 1});
        }
        neighbors.push_back({row, col - 1});
        neighbors.push_back({row, col + 1});
    }

    // right bottom
    else if (row == maxRows - 1 && col == maxCols - 1)
    {
        if (row > 0)
        {
            if (col > 0)
            {
                neighbors.push_back({row - 1, col - 1});
            }
            neighbors.push_back({row - 1, col});
        }
        if (col > 0)
        {
            neighbors.push_back({row, col - 1});
        }
    }

    return neighbors;
}

std::vector<Blob_t> findBlobs(Matrix const& inputMatrix)
{
    constexpr int shapeValue = 1;  // we are looking for shapes marked by 1s

    auto const& inputValues = inputMatrix.getValues();
    std::vector<int> labels(inputValues.size(), 0);
    std::vector<bool> visited(inputValues.size(), false);

    std::vector<std::vector<int>> matrixVec;
    std::vector<std::vector<bool>> visitedValues;
    std::vector<std::vector<int>> labelValues;
    for (IndexType row = 0; row < inputMatrix.getNumRows(); ++row)
    {
        matrixVec.emplace_back(inputMatrix.getNumCols(), 0);
        labelValues.emplace_back(inputMatrix.getNumCols(), 0);
        visitedValues.emplace_back(inputMatrix.getNumCols(), false);
    }

    for (IndexType row = 0, idx = 0; row < inputMatrix.getNumRows(); ++row)
    {
        if (row == 0)
        {
        }
        for (IndexType col = 0; col < inputMatrix.getNumCols(); ++col, ++idx)
        {
            // transfer matrix input values to vector (todo: maybe get rid of other matrix..)
            matrixVec[row][col] = inputValues[idx];
        }
    }

    unsigned currentLabel = 0;
    for (IndexType row = 0; row < inputMatrix.getNumRows(); ++row)
    {
        for (IndexType col = 0; col < inputMatrix.getNumCols(); ++col)
        {
            if (false == visitedValues[row][col] && shapeValue == matrixVec[row][col])
            {
                labelValues[row][col] = ++currentLabel;
                visitedValues[row][col] = true;

                std::queue<Point> visitNeighbors;
                visitNeighbors.push({row, col});

                while (!visitNeighbors.empty())
                {
                    // check all neighbors of the candidates and add these to the queue eventually, building a candidate chain
                    auto const [visitRow, visitCol] = visitNeighbors.front();
                    visitNeighbors.pop();

                    auto const neighbors = getNeighbors(visitRow, visitCol, inputMatrix.getNumRows(), inputMatrix.getNumCols());
                    for (auto const& neighbor : neighbors)
                    {
                        if (false == visitedValues[neighbor.row][neighbor.col] && shapeValue == matrixVec[neighbor.row][neighbor.col])
                        {
                            visitedValues[neighbor.row][neighbor.col] = true;
                            labelValues[neighbor.row][neighbor.col] = currentLabel;
                            // add this one for further checking with current label!
                            visitNeighbors.push(neighbor);
                        }
                    }
                }
            }
        }
    }

    if (currentLabel == 0)
    {
        return std::vector<Blob_t>{};  // nothing found
    }

    std::vector<Blob_t> blobs(currentLabel);
    for (IndexType row = 0, idx = 0; row < inputMatrix.getNumRows(); ++row)
    {
        for (IndexType col = 0; col < inputMatrix.getNumCols(); ++col, ++idx)
        {
            // insert index of the matrix value to its blob with the right label
            // label 0 means it the matrix value does not belong to any shape
            // otherwise it is the "name"/index of the shape
            auto const labelValue = labelValues[row][col];
            if (0 != labelValue)
            {
                blobs[labelValue-1].insert(idx);
            }
        }
    }
    return blobs;
}

Blob_t const& getLargestBlob(std::vector<Blob_t> const& blobs)
{
    // clang-format off
    return *std::max_element(blobs.cbegin(), blobs.cend(), [](auto const& blob1, auto const& blob2) {
        return blob1.size() < blob2.size();
    });
    // clang-format on
}
