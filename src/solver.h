#ifndef TIC_TAC_TOE_SOLVER_H
#define TIC_TAC_TOE_SOLVER_H

#include <vector>
#include <stdexcept>

#include "globals.h"

class Solver
{
private:
    int winningIndex;
    std::vector<int> winningIndices;
    const int winningSize{WINNING_SIZE};
    const int fieldSize{FIELD_SIZE};
    std::vector<FieldType> gameField;
    FieldType flipType(FieldType type);
    void dumpGameField(std::vector<FieldType> &gameFieldIn);

public:
    Solver();
    bool isWinningField(std::vector<FieldType> &gameFieldIn, const int index, const FieldType type);
    bool isWinningField(const int index, const FieldType type);

    bool isEmptyField(const int index);
    bool isEmptyField(const std::vector<FieldType> &gameFieldIn, const int index);
    void setFieldValue(const int index, const FieldType type);

    bool containsWinningSize(const std::vector<FieldType> &gameField, const FieldType type, int row, int col, const int rowIncrement, const int colIncrement);
    bool isInField(int row, int col);

    int solve(const FieldType type, const int moveCount);
    int solve(std::vector<FieldType> &gameField, const FieldType type, int moveCount);

    FieldType getFieldState(const int index);

    int getWinningIndex();

    const std::vector<int> &getWinningIndices();

    const std::vector<FieldType> &getGameField();
};

#endif