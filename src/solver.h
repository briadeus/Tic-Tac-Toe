#ifndef TIC_TAC_TOE_SOLVER_H
#define TIC_TAC_TOE_SOLVER_H

#include <vector>
#include <stdexcept>

enum FieldType
{
    EMPTY,
    CROSS,
    CIRCLE
};

class Solver
{
private:
    const int winningSize;
    const int fieldSize;
    std::vector<FieldType> gameField;
    FieldType flipType(FieldType type);

public:
    Solver(const int fieldSizeIn, const int winningSizeIn);
    bool isWinningField(std::vector<FieldType> &gameFieldIn,const int index, const FieldType type);
    bool isEmptyField(const std::vector<FieldType> &gameFieldIn,const int index);
    void setFieldValue(const int index, const FieldType type);

    bool containsWinningSize(const std::vector<FieldType> &gameField, const FieldType type, int row, int col, const int rowIncrement, const int colIncrement);
    bool isInField(int row, int col);

    int solve(std::vector<FieldType> &gameField, const FieldType type);
};

#endif