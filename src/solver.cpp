#include <algorithm>
#include <iostream>
#include "solver.h"
#include "globals.h"

Solver::Solver(const int fieldSizeIn, const int winningSizeIn) : winningSize(winningSizeIn), fieldSize(fieldSizeIn)
{
    if (winningSizeIn > fieldSizeIn || winningSizeIn < 2)
    {
        throw std::invalid_argument(GAME_FIELD_ERROR);
    }

    gameField = std::vector<FieldType>(fieldSizeIn * fieldSizeIn, FieldType::EMPTY);
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

int Solver::solve(std::vector<FieldType> &gameFieldIn, const FieldType type)
{

    int finalState = -1;
    bool emptyFieldFound = false;

    for (int i = 0; i < gameFieldIn.size(); i++)
    {

        if (isEmptyField(gameFieldIn, i))
        {
            emptyFieldFound = true;

            if (isWinningField(gameFieldIn, i, type))
            {

                return i;
            }
            else
            {

                std::vector<FieldType> adjustedField = std::vector<FieldType>(gameFieldIn);
                adjustedField[i] = type;

                int result = -1 * solve(adjustedField, flipType(type));

                if (result > finalState)
                {

                    return result;
                }
                else
                {
                    finalState = result;
                }
            }
        }
    }

    if (!emptyFieldFound)
    {
        return 1;
    }
    else
    {
        return finalState;
    }
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