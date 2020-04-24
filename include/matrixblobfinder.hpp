#pragma once

#include "matrix.hpp"

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using Blob_t = std::set<int>;
using IndexType = std::vector<std::vector<int>>::size_type;

struct Point
{
    const IndexType row, col;
};

//! @brief helper method to generate list of which neighbors to check
std::vector<Point> getNeighbors(IndexType row, IndexType col, IndexType maxRows, IndexType maxCols);

//! @brief finds shapes and puts them in sets; the sets contain matrix index values
std::vector<Blob_t> findBlobs(Matrix const& inputMatrix);

//! @brief returns larges blob
Blob_t const& getLargestBlob(std::vector<Blob_t> const& blobs);
