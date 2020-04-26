#include "matrixblobfinder.hpp"

#include <catch2/catch.hpp>

TEST_CASE("MatrixBlobFinder", "[blobfinder]")
{
    SECTION("Demo")
    {
        // clang-format off
        Matrix testMatrix{ 5, 7, {
            0, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 1, 1, 1, 0,
            1, 1, 0, 1, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 0, 1, 1, 1 }
        };
        // clang-format on

        auto const blobs = findBlobs(testMatrix);
        CHECK(blobs.size() == 3);
        auto blobIndices = getLargestBlob(blobs);
        CHECK(blobIndices.size() == 6);

        // a custom Catch matcher would be nice here..
        for (unsigned expectedBlobIdx : {3u, 10u, 11u, 12u, 17u, 18u})
        {
            CAPTURE(expectedBlobIdx);
            CHECK(!blobIndices.extract(expectedBlobIdx).empty());
        }
    }

    SECTION("1 0 0 0")
    {
        Matrix testMatrix{1, 4, {1, 0, 0, 0}};
        auto const blobs = getLargestBlob(findBlobs(testMatrix));
        CHECK(blobs.size() == 1);
        CHECK(blobs.find(0) != blobs.end()); // first matrix entry is detected
    }
}
