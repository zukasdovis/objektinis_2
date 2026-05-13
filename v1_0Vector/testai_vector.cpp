#include <gtest/gtest.h>
#include "Vector.h"

// --- Konstruktoriai ---
TEST(VectorTest, DefaultKonstruktorius)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, DydzioKonstruktorius)
{
    Vector<int> v(5, 42);
    EXPECT_EQ(v.size(), 5);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(v[i], 42);
}

TEST(VectorTest, InitializerList)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyKonstruktorius)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2[0], v1[0]);
    v2[0] = 99;
    EXPECT_NE(v1[0], v2[0]); // nepriklausomi
}

TEST(VectorTest, MoveKonstruktorius)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v1.size(), 0); // v1 tuščias
}

// --- Rule of Five ---
TEST(VectorTest, CopyAssignment)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, MoveAssignment)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, SelfAssignment)
{
    Vector<int> v = {1, 2, 3};
    v = v;
    EXPECT_EQ(v.size(), 3);
}

// --- Elementų prieiga ---
TEST(VectorTest, At_Teisingas)
{
    Vector<int> v = {10, 20, 30};
    EXPECT_EQ(v.at(0), 10);
    EXPECT_EQ(v.at(2), 30);
}

TEST(VectorTest, At_IsRibu)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, FrontBack)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 3);
}

// --- Modifikatoriai ---
TEST(VectorTest, PushBack)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, PopBack)
{
    Vector<int> v = {1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, Clear)
{
    Vector<int> v = {1, 2, 3};
    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Resize_Didesnis)
{
    Vector<int> v = {1, 2, 3};
    v.resize(5, 0);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[4], 0);
}

TEST(VectorTest, Resize_Mazesnis)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    v.resize(3);
    EXPECT_EQ(v.size(), 3);
}

TEST(VectorTest, Insert)
{
    Vector<int> v = {1, 2, 3};
    v.insert(v.begin() + 1, 99);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[1], 99);
}

TEST(VectorTest, Erase)
{
    Vector<int> v = {1, 2, 3, 4};
    v.erase(v.begin() + 1);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, EraseInterval)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    v.erase(v.begin() + 1, v.begin() + 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[1], 4);
}

TEST(VectorTest, Swap)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {4, 5};
    v1.swap(v2);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v2.size(), 3);
}

// --- Talpa ---
TEST(VectorTest, Reserve)
{
    Vector<int> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100);
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, ShrinkToFit)
{
    Vector<int> v;
    v.reserve(100);
    v.push_back(1);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}

// --- Lyginimo operatoriai ---
TEST(VectorTest, Lygybe)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 3};
    EXPECT_TRUE(v1 == v2);
}

TEST(VectorTest, Nelygybe)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 4};
    EXPECT_TRUE(v1 != v2);
}

TEST(VectorTest, MazesniUz)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 4};
    EXPECT_TRUE(v1 < v2);
}

// --- Iteratoriai ---
TEST(VectorTest, Iteratoriai)
{
    Vector<int> v = {1, 2, 3};
    int suma = 0;
    for (auto it = v.begin(); it != v.end(); it++)
        suma += *it;
    EXPECT_EQ(suma, 6);
}

TEST(VectorTest, RangeFor)
{
    Vector<int> v = {1, 2, 3};
    int suma = 0;
    for (auto x : v)
        suma += x;
    EXPECT_EQ(suma, 6);
}