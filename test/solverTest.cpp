#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../src/globals.h"
#include "../src/solver.cpp"

TEST(SolverTest, testConstructsWithProperArguments)
{

    try
    {
        Solver s1{1, 1};
    }
    catch (std::invalid_argument const &excpt)
    {
        EXPECT_EQ(excpt.what(), GAME_FIELD_ERROR);
    }

    try
    {
        Solver s2{2, 3};
    }
    catch (std::invalid_argument const &excpt)
    {
        EXPECT_EQ(excpt.what(), GAME_FIELD_ERROR);
    }
}

TEST(SolverTest, testIsEmpty)
{
    Solver s{2, 2};
    std::vector<FieldType> v1{FieldType::CIRCLE, FieldType::EMPTY};

    EXPECT_TRUE(s.isEmptyField(v1, 1));
}

TEST(SolverTest, testHasWinningSizeHorizontal)
{
    Solver s{5, 3};

    std::vector<FieldType> v1{FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY, FieldType::CIRCLE, FieldType::CIRCLE};

    EXPECT_FALSE(s.containsWinningSize(v1, FieldType::CIRCLE, 0, 0, 0, 1));

    std::vector<FieldType> v2{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY};

    EXPECT_FALSE(s.containsWinningSize(v2, FieldType::CIRCLE, 1, 0, 0, 1));

    std::vector<FieldType> v3{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS, FieldType::EMPTY};

    EXPECT_TRUE(s.containsWinningSize(v3, FieldType::CROSS, 1, 0, 0, 1));

    std::vector<FieldType> v4{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS};

    EXPECT_FALSE(s.containsWinningSize(v4, FieldType::CROSS, 1, 0, 0, 1));
    EXPECT_TRUE(s.containsWinningSize(v4, FieldType::CROSS, 2, 0, 0, 1));
    EXPECT_FALSE(s.containsWinningSize(v4, FieldType::CIRCLE, 2, 0, 0, 1));
}

TEST(SolverTest, testHasWinningSizeVertical)
{
    const int fieldSize = 5;
    Solver s{fieldSize, 3};

    std::vector<FieldType> v4{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS};

    EXPECT_TRUE(s.containsWinningSize(v4, FieldType::CIRCLE, 0, 3, 1, 0));
    EXPECT_FALSE(s.containsWinningSize(v4, FieldType::CIRCLE, 0, 2, 1, 0));
    EXPECT_FALSE(s.containsWinningSize(v4, FieldType::CROSS, 0, 3, 1, 0));

    std::vector<FieldType> v1{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS};
    EXPECT_TRUE(s.containsWinningSize(v1, FieldType::CROSS, 0, 4, 1, 0));

    std::vector<FieldType> v2{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::CIRCLE, FieldType::EMPTY, FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS};
    EXPECT_TRUE(s.containsWinningSize(v2, FieldType::CIRCLE, 0, 0, 1, 0));

    std::vector<FieldType> v3{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::CIRCLE, FieldType::EMPTY, FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS};
    EXPECT_FALSE(s.containsWinningSize(v4, FieldType::CIRCLE, 0, 4, 1, 0));
}

TEST(SolverTest, testHasWinningSizeDiagonal)
{
    const int fieldSize = 5;
    Solver s{fieldSize, 3};
    std::vector<FieldType> v1{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE, FieldType::EMPTY,
                              FieldType::CIRCLE, FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CROSS, FieldType::CROSS};
    EXPECT_TRUE(s.containsWinningSize(v1, FieldType::CIRCLE, 0, 0, 1, 1));
    EXPECT_TRUE(s.containsWinningSize(v1, FieldType::CROSS, 0, 1, 1, 1));
    EXPECT_TRUE(s.containsWinningSize(v1, FieldType::CROSS, 1, 0, 1, 1));
    EXPECT_TRUE(s.containsWinningSize(v1, FieldType::CROSS, 4, 2, -1, 1));
}

TEST(SolverTest, testIsInField)
{
    const int fieldSize = 5;
    Solver s{fieldSize, 3};

    EXPECT_FALSE(s.isInField(0, fieldSize));
    EXPECT_FALSE(s.isInField(0, fieldSize));
    EXPECT_FALSE(s.isInField(-1, 0));
    EXPECT_FALSE(s.isInField(2, -1));

    EXPECT_TRUE(s.isInField(0, fieldSize - 1));
    EXPECT_TRUE(s.isInField(fieldSize - 1, 0));
}

TEST(SolverTest, testIsWinningField)
{

    Solver s{3, 3};
    std::vector<FieldType> v1{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE,
                              FieldType::EMPTY, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::CROSS, FieldType::CROSS, FieldType::EMPTY};

    EXPECT_FALSE(s.isWinningField(v1, 3, FieldType::CIRCLE));

    EXPECT_TRUE(s.isWinningField(v1, 8, FieldType::CIRCLE));
    EXPECT_TRUE(s.isWinningField(v1, 8, FieldType::CROSS));

    std::vector<FieldType> v2{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE,
                              FieldType::EMPTY, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::EMPTY, FieldType::CROSS, FieldType::EMPTY};

    EXPECT_TRUE(s.isWinningField(v2, 6, FieldType::CIRCLE));

    Solver s4{4, 3};
    std::vector<FieldType> v3{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE, FieldType::CIRCLE,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS, FieldType::CIRCLE,
                              FieldType::CROSS, FieldType::CROSS, FieldType::EMPTY, FieldType::CIRCLE,
                              FieldType::CROSS, FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE};

    EXPECT_TRUE(s4.isWinningField(v3, 10, FieldType::CIRCLE));
    EXPECT_TRUE(s4.isWinningField(v3, 5, FieldType::CROSS));
    EXPECT_TRUE(s4.isWinningField(v3, 4, FieldType::CROSS));
}

TEST(SolverTest, testSolving)
{
    Solver s{3, 3};
    std::vector<FieldType> v1{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE,
                              FieldType::CIRCLE, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::CROSS, FieldType::CROSS, FieldType::EMPTY};

    EXPECT_EQ(8, s.solve(v1, FieldType::CROSS));
    EXPECT_EQ(8, s.solve(v1, FieldType::CIRCLE));

    std::vector<FieldType> v2{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE,
                              FieldType::EMPTY, FieldType::EMPTY, FieldType::CROSS,
                              FieldType::CROSS, FieldType::CROSS, FieldType::EMPTY};
    EXPECT_EQ(4, s.solve(v2, FieldType::CROSS));

    std::vector<FieldType> v3{FieldType::CIRCLE, FieldType::CROSS, FieldType::CIRCLE,
                              FieldType::EMPTY, FieldType::CIRCLE, FieldType::CROSS,
                              FieldType::CROSS, FieldType::CROSS, FieldType::CIRCLE};
    EXPECT_LT(s.solve(v3, FieldType::CROSS), 0); // losing game
}