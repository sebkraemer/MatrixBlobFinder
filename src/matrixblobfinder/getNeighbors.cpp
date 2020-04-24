#include "matrixblobfinder.hpp"

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
