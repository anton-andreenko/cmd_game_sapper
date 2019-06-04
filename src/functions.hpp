// functions.hpp

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "aux_header.hpp"

namespace Functions
{
    void ClearStdInBuffer();
    user_action_t InputValue();
    int InputValue(int left_limit, int right_limit);
    void AllocationMemory(field_t & arg, int size_xy);
    void ClearMemory(field_t & arg);
    void InitField(field_t field_1, int size_xy, cell_t cell_value);
    void SetRandomBombs(field_t field_1, int size_xy, int bombs_total);
    void SetHintNumbers(field_t field_1, int size_x, int size_y);
    void UpdateZeroCells(field_t field_1, const field_t field_2, int size_x, int size_y, int cell_x, int cell_y);
    void UpdateErrorCells(field_t field_1, const field_t field_2, int size_xy);
    void UpdateGameResult(game_result_t & r_game_result, const field_t field_1, int size_xy);
    void PrintSceneDelimiter();
    void PrintSimpleText(text_t text);
    void PrintCustomText(text_t text, int arg);
    void PrintField(const field_t field_1, int size_x, int size_y);
    void PrintGameResult(const game_result_t & r_game_result, int bombs_total);
    bool CheckEndGame(const field_t field_1, const field_t field_2, int size_xy);
    void ExitDelay();
}

#endif // FUNCTIONS_H
