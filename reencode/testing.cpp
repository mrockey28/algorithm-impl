#include <gtest/gtest.h>

#include "BinaryTree.h"
#include "DoubleLinkedList.h"

using namespace std;

TEST(BinaryTreeTest, AssembleTest) 
{
    Node<int> one({27, nullptr, nullptr});
    Node<int> two({35, nullptr, nullptr});
    Node<int> three({37, nullptr, nullptr});
    Node<int> four ({39, nullptr, nullptr});
    Node<int> five ({52, nullptr, nullptr});

    three.left = &one;
    three.right = &five;
    one.right = &two;
    five.left = &four;

    BinaryTree<int> test({37, 27, 35, 52, 39});
    EXPECT_EQ(true, test == &three);
}

TEST(DoubleLinkedListTest, AssembleTest) 
{
    Node<int> one({27, nullptr, nullptr});
    Node<int> two({35, &one, nullptr});
    Node<int> three({37, &two, nullptr});
    Node<int> four ({39, &three, &one});
    one.left = &four;
    one.right = &two;
    two.right = &three;
    three.right = &four;

    DoubleLinkedList<int> test({39, 35, 27, 37});
    EXPECT_EQ(true, test == &one);

}

TEST(DoubleLinkedListTest, ConvertTest) 
{
    auto convertMe = new BinaryTree<int>({35, 26, 29, 37, 10, 45, 36, 34});

    DoubleLinkedList<int> test({10, 26, 29, 34, 35, 36, 37, 45});

    auto testAgainst = test.Convert(convertMe);

    EXPECT_EQ(true, *testAgainst == test);
    delete testAgainst;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
