#include <algorithm>
#include <iostream>
#include <vector>
#include "solver.h"

Solver::Solver(const int fieldSizeIn, const int winningSizeIn) : winningSize(winningSizeIn),
                                                                 fieldSize(fieldSizeIn)
{
    if (winningSizeIn > fieldSizeIn || winningSizeIn < 2)
    {
        throw std::invalid_argument(GAME_FIELD_ERROR);
    }
    gameField = std::vector<FieldType>(fieldSizeIn * fieldSizeIn, FieldType::EMPTY);
}

int Solver::getWinningIndex()
{
    return winningIndex;
}

bool Solver::isWinningField( const int index, const FieldType type) {
return isWinningField(gameField, index, type);
}

bool Solver::isWinningField(std::vector<FieldType> &gameFieldIn, const int index, const FieldType type)
{
    int offset = fieldSize;
    int row = index / offset;
    int col = index % offset;
    bool isWinningField = false;

    // set value
    gameFieldIn[index] = type;

    bool winsHorizontal = containsWinningSize(gameFieldIn, type, row, 0, 0, 1);
    bool winsVertical = containsWinningSize(gameFieldIn, type, 0, col, 1, 0);
    int rowIndexTop = (col - row >= 0) ? 0 : std::abs(col - row);
    int colIndexTop = (col - row >= 0) ? col - row : 0;

    bool winsDiagTop = containsWinningSize(gameFieldIn, type, rowIndexTop, colIndexTop, 1, 1);

    int rowIndexBottom = (row + col <= fieldSize - 1) ? col + row : fieldSize - 1;
    int colIndexBottom = (row + col <= fieldSize - 1) ? 0 : col - (fieldSize - 1) + row;

    bool winsDiagBot = containsWinningSize(gameFieldIn, type, rowIndexBottom, colIndexBottom, -1, 1);

    isWinningField = (winsHorizontal | winsVertical | winsDiagTop | winsDiagBot);

    //re-set to empty
    gameFieldIn[index] = FieldType::EMPTY;

    return isWinningField;
}

bool Solver::containsWinningSize(const std::vector<FieldType> &gameFieldIn, const FieldType type,
                                 int row, int col, const int rowIncrement, const int colIncrement)
{

    int count = 0;
    int index = 0;

    while (isInField(row, col))
    {
        index = row * fieldSize + col;
        if (gameFieldIn[index] == type)
        {
            count++;
        }
        else
        {
            count = 0;
        }

        if (count == winningSize)
        {
            return true;
        }
        row = row + rowIncrement;
        col = col + colIncrement;
    }

    return false;
}

bool Solver::isEmptyField(const int index)
{

    return isEmptyField(gameField, index);
}

bool Solver::isEmptyField(const std::vector<FieldType> &gameFieldIn, const int index)
{

    return (gameFieldIn[index] == FieldType::EMPTY);
}

void Solver::setFieldValue(const int index, const FieldType type)
{
    gameField[index] = type;
}

bool Solver::isInField(int row, int col)
{
    if (col >= 0 && row >= 0 && col < fieldSize && row < fieldSize)
    {
        return true;
    }
    return false;
}

int Solver::solve(const FieldType type, const int moveCount)
{
    return solve(gameField, type, moveCount);
}

/*
 * Negative minmax based on
 * http://blog.gamesolver.org/solving-connect-four/03-minmax/
 */
int Solver::solve(std::vector<FieldType> &gameFieldIn, const FieldType type, int moveCount)
{

    for (int i = 0; i < gameFieldIn.size(); i++)
    {
        if (isEmptyField(gameFieldIn, i) && isWinningField(gameFieldIn, i, type))
        {
            winningIndex = i;
            int finalScore = ((fieldSize * fieldSize) - moveCount);

            //dumpGameField(gameFieldIn);

            return -finalScore; // the less moves the better
        }
    }

    int bestScore = -(fieldSize * fieldSize);

    for (int i = 0; i < gameFieldIn.size(); i++)
    {

        if (isEmptyField(gameFieldIn, i))
        {

            std::vector<FieldType> adjustedField = std::vector<FieldType>(gameFieldIn);
            adjustedField[i] = type;

            int score = -solve(adjustedField, flipType(type), moveCount + 1);

            if (score > bestScore)
            {
                bestScore = score;
            }
        }
    }

    return bestScore;
}

FieldType Solver::getFieldState(const int index)
{
    return gameField[index];
}

/* PRIVATE  */
FieldType Solver::flipType(FieldType type)
{
    if (type == FieldType::CROSS)
    {
        return FieldType::CIRCLE;
    }
    else
    {
        return FieldType::CROSS;
    }
}

void Solver::dumpGameField(std::vector<FieldType> &gameFieldIn)
{

    std::cout << " Game Field In \n";
    for (int i = 0; i < gameFieldIn.size(); i++)
    {
        auto type = gameFieldIn[i];
        if (type == FieldType::CROSS)
        {
            std::cout << " X ";
        }
        else if (type == FieldType::CIRCLE)
        {
            std::cout << " O ";
        }
        else
        {
            std::cout << " E ";
        }
        if ((i + 1) % fieldSize == 0)
        {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}