#include <gtest/gtest.h>

#include "ConvexHull.h"

using namespace std;

//Predeclare, so we can test it.
void OrderArray(std::vector<Point2D>& input, uint32_t lowIndex);

void Validate(const vector<Point2D>& expected, const vector<Point2D>& result)
{
    ASSERT_EQ(expected.size(), result.size());
    for (int i = 0; i < result.size(); i++)
    {
        ASSERT_EQ(expected[i], result[i]) << "Array unequal at index " << i;
    }
}

TEST(ConvexHullTest, OrderArray1) {

    vector<Point2D> test({{1,1},{1,4},{4,4},{4,1},{2,2}});
    vector<Point2D> exresult({{1,1},{4,1},{2,2},{4,4},{1,4}});
    OrderArray(test, 0);
    Validate(exresult, test);
}

TEST(ConvexHullTest, OrderArray2) {

    vector<Point2D> test({{10,10},{10,0},{10,5},{10,7},{0,1},{0,7},{5,5},{9,2},{4,11}});
    vector<Point2D> exresult({{10,0},{10,5},{10,7},{10,10},{9,2},{4,11},{5,5},{0,7},{0,1}});
    OrderArray(test, 1);
    Validate(exresult, test);
}

TEST(ConvexHullTest, Hull1) {

    vector<Point2D> test({{1,1},{1,4},{4,4},{4,1},{2,2}});
    vector<Point2D> exresult({{1,1},{4,1},{4,4},{1,4}});
    auto result = convexhull(test);
    Validate(exresult, result);
}

TEST(ConvexHullTest, Hull2) {

    vector<Point2D> test({{10,10},{10,0},{10,5},{10,7},{0,1},{0,7},{5,5},{9,2},{4,11}});
    vector<Point2D> exresult({{10,0},{10,10},{4,11},{0,7},{0,1}});
    auto result = convexhull(test);
    Validate(exresult, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
