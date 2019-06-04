// main.cpp

#include "aux_header.hpp"
#include "functions.hpp"

using namespace Functions;

int main()
{
    std::srand(std::time(0));
    user_action_t user_action = 0;
    field_t field_user = nullptr;
    field_t field_dase = nullptr;
    game_result_t game_result = {0, 0, 0};
    int size_x = 0;
    int size_y = 0;
    int size_xy = 0;
    int cell_x = 0;
    int cell_y = 0;
    int cell_index = 0;
    int bombs_total = 0;
    int bombs_left = 0;
    bool is_end_game = false;
    PrintSceneDelimiter();
    PrintSimpleText(" SAPPER (console version)!\n\n");
    PrintSimpleText(" Field size X (1-20) = ");
    size_x = InputValue(1, 20);
    PrintSimpleText(" Field size Y (1-20) = ");
    size_y = InputValue(1, 20);
    size_xy = size_x * size_y;
    PrintCustomText(" Bombs (0-%d) = ", size_xy);
    bombs_total = InputValue(0, size_xy);
    bombs_left = bombs_total;
    AllocationMemory(field_user, size_xy);
    AllocationMemory(field_dase, size_xy);
    InitField(field_user, size_xy, CELL_HIDE);
    InitField(field_dase, size_xy, CELL_0);
    SetRandomBombs(field_dase, size_xy, bombs_total);
    SetHintNumbers(field_dase, size_x, size_y);

    do
    {
        is_end_game = CheckEndGame(field_user, field_dase, size_xy);

        if (true == is_end_game)
        {
            UpdateGameResult(game_result, field_user, size_xy);
            PrintSceneDelimiter();
            PrintSimpleText(" Game over!\n\n");
            PrintField(field_user, size_x, size_y);
            PrintField(field_dase, size_x, size_y);
            PrintGameResult(game_result, bombs_total);
            PrintSceneDelimiter();
            ClearMemory(field_user);
            ClearMemory(field_dase);
            ExitDelay();

            return 0;
        }

        PrintSceneDelimiter();
        PrintCustomText(" Bombs: %d\n\n", bombs_left);
        PrintField(field_user, size_x, size_y);
        // PrintField(field_dase, size_x, size_y);
        PrintSimpleText(" 1 - Activate cell\n");
        PrintSimpleText(" 2 - Put flag\n");
        PrintSimpleText(" 3 - Erase flag\n");
        PrintSimpleText(" 0 - Exit\n\n");
        PrintSimpleText(" => ");
        user_action = InputValue();

        if (user_action == UA_ACTIVATE_CELL)
        {
            PrintSimpleText("\n Activate cell (x, y):\n");
            PrintCustomText(" x (1-%d) = ", size_x);
            cell_x = InputValue(1, size_x) - 1;
            PrintCustomText(" y (1-%d) = ", size_y);
            cell_y = InputValue(1, size_y) - 1;
            cell_index = cell_y * size_x + cell_x;

            if (field_user[cell_index] == CELL_HIDE)
            {
                if (field_dase[cell_index] != CELL_BOMB)
                {
                    field_user[cell_index] = field_dase[cell_index];

                    if (field_user[cell_index] == CELL_0)
                    {
                        UpdateZeroCells(field_user, field_dase, size_x, size_y, cell_x, cell_y);
                    }
                }
                else
                {
                    field_user[cell_index] = CELL_ERROR;
                    UpdateErrorCells(field_user, field_dase, size_xy);
                    UpdateGameResult(game_result, field_user, size_xy);
                    PrintSceneDelimiter();
                    PrintSimpleText(" Game over!\n\n");
                    PrintField(field_user, size_x, size_y);
                    PrintField(field_dase, size_x, size_y);
                    PrintGameResult(game_result, bombs_total);
                    PrintSceneDelimiter();
                    ClearMemory(field_user);
                    ClearMemory(field_dase);
                    ExitDelay();

                    return 0;
                }
            }
        }
        else if (user_action == UA_PUT_FLAG)
        {
            PrintSimpleText("\n Put flag (x, y):\n");
            PrintCustomText(" x (1-%d) = ", size_x);
            cell_x = InputValue(1, size_x) - 1;
            PrintCustomText(" y (1-%d) = ", size_y);
            cell_y = InputValue(1, size_y) - 1;
            cell_index = cell_y * size_x + cell_x;

            if (field_user[cell_index] == CELL_HIDE)
            {
                field_user[cell_index] = CELL_FLAG;
                bombs_left -= 1;
            }
        }
        else if (user_action == UA_ERASE_FLAG)
        {
            PrintSimpleText("\n Erase flag (x, y):\n");
            PrintCustomText(" x (1-%d) = ", size_x);
            cell_x = InputValue(1, size_x) - 1;
            PrintCustomText(" y (1-%d) = ", size_y);
            cell_y = InputValue(1, size_y) - 1;
            cell_index = cell_y * size_x + cell_x;

            if (field_user[cell_index] == CELL_FLAG)
            {
                field_user[cell_index] = CELL_HIDE;
                bombs_left += 1;
            }
        }
    }
    while (user_action != UA_EXIT);

    UpdateErrorCells(field_user, field_dase, size_xy);
    UpdateGameResult(game_result, field_user, size_xy);
    PrintSceneDelimiter();
    PrintSimpleText(" Game over!\n\n");
    PrintField(field_user, size_x, size_y);
    PrintField(field_dase, size_x, size_y);
    PrintGameResult(game_result, bombs_total);
    PrintSceneDelimiter();
    ClearMemory(field_user);
    ClearMemory(field_dase);
    ExitDelay();

    return 0;
}
