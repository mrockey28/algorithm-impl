#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include "QuickSort.h"
#include "PriorityQueue.h"

using namespace std;

template <typename T>
vector<T> ReadInFile(const string& filename)
{
    ifstream ifile;
    ifile.open(filename.c_str());

    vector<T> returnVec;
    while (!ifile.eof())
    {
        T in;
        ifile >> in;
        returnVec.push_back(in);
    }

    return returnVec;
}

template <typename T>
void TestQuickSort(vector<T>& unsorted)
{
    vector<T> sorted = unsorted;
    std::sort(sorted.begin(), sorted.end());
    QuickSort<T>(unsorted);

    EXPECT_EQ(unsorted.size(), sorted.size()) << "Vectors are not same size!";
    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(sorted[i], unsorted[i]) << "Mismatch at index " << i;
    }
}

template <typename T>
void TestQuickSort(const string& filename)
{
    vector<T> unsorted = ReadInFile<T>(filename);
    TestQuickSort<T>(unsorted);
}

template <typename T>
void TestPriorityQueue(vector<T>& unsorted)
{
    vector<T> sorted = unsorted;
    std::sort(sorted.begin(), sorted.end());

    PriorityQueue<T, T> test;
    for (auto &itr : unsorted)
    {
        test.push({itr, itr});
    }
    int index = 0;
    while (!test.empty())
    {
        ASSERT_FALSE(index == sorted.size());
        ASSERT_TRUE(test.top() != nullptr);
        EXPECT_EQ(sorted[index], test.top()->key) << "Mismatch at index " << index;
        index++;
        test.pop();
    }
    ASSERT_TRUE(index == sorted.size());
}

template <typename T>
void TestPriorityQueue(const string& filename)
{
    vector<T> unsorted = ReadInFile<T>(filename);
    TestPriorityQueue<T>(unsorted);
}

TEST(QuickSortTest, QuickSort10) {
    vector<int> vec10({9,2,3,1,8,7,4,5});
    TestQuickSort<int>(vec10);
}

TEST(QuickSortTest, QuickSort100) {
    TestQuickSort<int>(string("testing/100.txt"));
}

TEST(QuickSortTest, QuickSort1000) {
    TestQuickSort<int>(string("testing/1000.txt"));
}

TEST(QuickSortTest, QuickSort10000) {
    TestQuickSort<int>(string("testing/10000.txt"));
}

TEST(PriorityQueueTest, PriorityQueue10) {
    vector<int> vec10({9,2,3,1,8,7,4,5});
    TestPriorityQueue<int>(vec10);
}

TEST(PriorityQueueTest, PriorityQueue100) {
    TestPriorityQueue<int>(string("testing/100.txt"));
}

TEST(PriorityQueueTest, PriorityQueue1000) {
    TestPriorityQueue<int>(string("testing/1000.txt"));
}

TEST(PriorityQueueTest, PriorityQueue10000) {
    TestPriorityQueue<int>(string("testing/10000.txt"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
