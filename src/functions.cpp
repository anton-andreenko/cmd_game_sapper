// functions.cpp

#include "functions.hpp"

void Functions::ClearStdInBuffer()
{
    char value = 0;

    do
    {
        value = std::getchar();
    }
    while ((value != '\n') && (value != EOF));
}

user_action_t Functions::InputValue()
{
    char value = 0;
    std::scanf("%c", &value);
    ClearStdInBuffer();

    return static_cast<user_action_t>(value);
}

int Functions::InputValue(int left_limit, int right_limit)
{
    int value = 0;

    if (left_limit <= right_limit)
    {
        do
        {
            std::scanf("%d", &value);
            ClearStdInBuffer();
        }
        while ((value < left_limit) || (value > right_limit));
    }

    return value;
}

void Functions::AllocationMemory(field_t & arg, int size_xy)
{
    arg = static_cast<field_t>(std::malloc(sizeof(cell_t) * size_xy));
}

void Functions::ClearMemory(field_t & arg)
{
    std::free(arg);
    arg = nullptr;
}

void Functions::InitField(field_t field_1, int size_xy, cell_t cell_value)
{
    // field_1 -- field_user, field_dase

    for (int i = 0; (i < size_xy); i++)
    {
        field_1[i] = cell_value;
    }
}

void Functions::SetRandomBombs(field_t field_1, int size_xy, int bombs_total)
{
    // field_1 -- field_dase

    std::vector<int> v_indexes;
    int random_index = 0;

    for (int i = 0; (i < size_xy); i++)
    {
        v_indexes.push_back(i);
    }

    for (int i = 0; (i < bombs_total); i++)
    {
        random_index = std::rand() % v_indexes.size();
        field_1[v_indexes[random_index]] = CELL_BOMB;
        v_indexes.erase(v_indexes.begin() + random_index);
    }
}

void Functions::SetHintNumbers(field_t field_1, int size_x, int size_y)
{
    // field_1 -- field_dase

    int bombs_around = 0;
    int px = 0;
    int nx = 0;
    int py = 0;
    int ny = 0;
    bool is_up_left = false;
    bool is_up = false;
    bool is_up_right = false;
    bool is_left = false;
    bool is_right = false;
    bool is_down_left = false;
    bool is_down = false;
    bool is_down_right = false;

    for (int y = 0; (y < size_y); y++)
    {
        py = y + 1;
        ny = y - 1;

        for (int x = 0; (x < size_x); x++)
        {
            px = x + 1;
            nx = x - 1;

            if (field_1[y * size_x + x] != CELL_BOMB)
            {
                is_up_left = (y > 0) && (x > 0) && (field_1[ny * size_x + nx] == CELL_BOMB);
                is_up = (y > 0) && (field_1[ny * size_x + x] == CELL_BOMB);
                is_up_right = (y > 0) && (x < (size_x - 1)) && (field_1[ny * size_x + px] == CELL_BOMB);
                is_left = (x > 0) && (field_1[y * size_x + nx] == CELL_BOMB);
                is_right = (x < (size_x - 1)) && (field_1[y * size_x + px] == CELL_BOMB);
                is_down_left = (y < (size_y - 1)) && (x > 0) && (field_1[py * size_x + nx] == CELL_BOMB);
                is_down = (y < (size_y - 1)) && (field_1[py * size_x + x] == CELL_BOMB);
                is_down_right = (y < (size_y - 1)) && (x < (size_x - 1)) && (field_1[py * size_x + px] == CELL_BOMB);
                bombs_around =
                    static_cast<int>(is_up_left) +
                    static_cast<int>(is_up) +
                    static_cast<int>(is_up_right) +
                    static_cast<int>(is_left) +
                    static_cast<int>(is_right) +
                    static_cast<int>(is_down_left) +
                    static_cast<int>(is_down) +
                    static_cast<int>(is_down_right);

                if (bombs_around == 0)
                {
                    field_1[y * size_x + x] = CELL_0;
                }
                else if (bombs_around == 1)
                {
                    field_1[y * size_x + x] = CELL_1;
                }
                else if (bombs_around == 2)
                {
                    field_1[y * size_x + x] = CELL_2;
                }
                else if (bombs_around == 3)
                {
                    field_1[y * size_x + x] = CELL_3;
                }
                else if (bombs_around == 4)
                {
                    field_1[y * size_x + x] = CELL_4;
                }
                else if (bombs_around == 5)
                {
                    field_1[y * size_x + x] = CELL_5;
                }
                else if (bombs_around == 6)
                {
                    field_1[y * size_x + x] = CELL_6;
                }
                else if (bombs_around == 7)
                {
                    field_1[y * size_x + x] = CELL_7;
                }
                else if (bombs_around == 8)
                {
                    field_1[y * size_x + x] = CELL_8;
                }
            }
        }
    }
}

void Functions::UpdateZeroCells(field_t field_1, const field_t field_2, int size_x, int size_y, int cell_x, int cell_y)
{
    // field_1 -- field_user
    // field_2 -- field_dase

    int cell_index = cell_y * size_x + cell_x;
    int x = cell_x;
    int px = cell_x + 1;
    int nx = cell_x - 1;
    int y = cell_y;
    int py = cell_y + 1;
    int ny = cell_y - 1;
    bool is_up_left = (y > 0) && (x > 0) && (field_1[ny * size_x + nx] == CELL_HIDE);
    bool is_up = (y > 0) && (field_1[ny * size_x + x] == CELL_HIDE);
    bool is_up_right = (y > 0) && (x < (size_x - 1)) && (field_1[ny * size_x + px] == CELL_HIDE);
    bool is_left = (x > 0) && (field_1[y * size_x + nx] == CELL_HIDE);
    bool is_right = (x < (size_x - 1)) && (field_1[y * size_x + px] == CELL_HIDE);
    bool is_down_left = (y < (size_y - 1)) && (x > 0) && (field_1[py * size_x + nx] == CELL_HIDE);
    bool is_down = (y < (size_y - 1)) && (field_1[py * size_x + x] == CELL_HIDE);
    bool is_down_right = (y < (size_y - 1)) && (x < (size_x - 1)) && (field_1[py * size_x + px] == CELL_HIDE);
    field_1[cell_index] = field_2[cell_index];

    if (field_1[cell_index] == CELL_0)
    {
        if (true == is_up_left)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, nx, ny);
        }

        if (true == is_up)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, x, ny);
        }

        if (true == is_up_right)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, px, ny);
        }

        if (true == is_left)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, nx, y);
        }

        if (true == is_right)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, px, y);
        }

        if (true == is_down_left)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, nx, py);
        }

        if (true == is_down)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, x, py);
        }

        if (true == is_down_right)
        {
            UpdateZeroCells(field_1, field_2, size_x, size_y, px, py);
        }
    }
}

void Functions::UpdateErrorCells(field_t field_1, const field_t field_2, int size_xy)
{
    // field_1 -- field_user
    // field_2 -- field_dase

    for (int i = 0; (i < size_xy); i++)
    {
        if ((field_1[i] == CELL_FLAG) && (field_2[i] != CELL_BOMB))
        {
            field_1[i] = CELL_ERROR;
        }
    }
}

void Functions::UpdateGameResult(game_result_t & r_game_result, const field_t field_1, int size_xy)
{
    // field_1 -- field_user

    r_game_result.hide_count = 0;
    r_game_result.flag_count = 0;
    r_game_result.error_count = 0;

    for (int i = 0; (i < size_xy); i++)
    {
        if (field_1[i] == CELL_HIDE)
        {
            r_game_result.hide_count += 1;
        }
        else if (field_1[i] == CELL_FLAG)
        {
            r_game_result.flag_count += 1;
        }
        else if (field_1[i] == CELL_ERROR)
        {
            r_game_result.error_count += 1;
        }
    }
}

void Functions::PrintSceneDelimiter()
{
    std::printf("====================================================================\n");
}

void Functions::PrintSimpleText(text_t text)
{
    std::printf(text);
}

void Functions::PrintCustomText(text_t text, int arg)
{
    std::printf(text, arg);
}

void Functions::PrintField(const field_t field_1, int size_x, int size_y)
{
    // field_1 -- field_user, field_dase

    char c_buffer[256] = {};
    std::string s_buffer;

    // line: 1

    s_buffer.append(" +--+");

    for (int x = 0; (x < size_x); x++)
    {
        s_buffer.append("---");
    }

    s_buffer.append("-+\n");

    // line: 2

    s_buffer.append(" |  |");

    for (int x = 0; (x < size_x); x++)
    {
        std::sprintf(c_buffer, "%3d", (x + 1));
        s_buffer.append(c_buffer);
    }

    s_buffer.append(" |\n");

    // line: 3

    s_buffer.append(" +--+");

    for (int x = 0; (x < size_x); x++)
    {
        s_buffer.append("---");
    }

    s_buffer.append("-+\n");

    // lines: 4 to N-1

    for (int y = 0; (y < size_y); y++)
    {
        std::sprintf(c_buffer, " |%2d|", (y + 1));
        s_buffer.append(c_buffer);

        for (int x = 0; (x < size_x); x++)
        {
            std::sprintf(c_buffer, "%3c", field_1[y * size_x + x]);
            s_buffer.append(c_buffer);
        }

        s_buffer.append(" |\n");

        if (y < (size_y - 1))
        {
            s_buffer.append(" |  |");

            for (int x = 0; (x < size_x); x++)
            {
                s_buffer.append("   ");
            }

            s_buffer.append(" |\n");
        }
    }

    // line: N

    s_buffer.append(" +--+");

    for (int x = 0; (x < size_x); x++)
    {
        s_buffer.append("---");
    }

    s_buffer.append("-+\n");

    // end of lines

    std::printf("%s\n", s_buffer.c_str());
}

void Functions::PrintGameResult(const game_result_t & r_game_result, int bombs_total)
{
    std::printf(" [-] - Hidden cell (%d)\n", r_game_result.hide_count);
    std::printf(" [F] - Correct flag (%d/%d)\n", r_game_result.flag_count, bombs_total);
    std::printf(" [X] - Error (%d)\n", r_game_result.error_count);
    std::printf(" [0, 1, 2, 3, 4, 5, 6, 7, 8] - Hint number\n");
    std::printf(" [B] - Bomb\n");
}

bool Functions::CheckEndGame(const field_t field_1, const field_t field_2, int size_xy)
{
    // field_1 -- field_user
    // field_2 -- field_dase

    bool result = true;

    for (int i = 0; ((true == result) && (i < size_xy)); i++)
    {
        if (field_1[i] == CELL_HIDE)
        {
            result = false;
        }
        else if ((field_1[i] == CELL_FLAG) && (field_2[i] != CELL_BOMB))
        {
            result = false;
        }
    }

    return result;
}

void Functions::ExitDelay()
{
    std::printf("Press \"Enter\" to exit...");
    std::getchar();
}
