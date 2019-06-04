// aux_header.hpp

#ifndef AUX_HEADER_H
#define AUX_HEADER_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

// aliases

typedef char user_action_t;
typedef const char * text_t;
typedef char cell_t;
typedef cell_t * field_t;

// structs

struct game_result_t
{
    int hide_count;
    int flag_count;
    int error_count;
};

// constants

const cell_t CELL_BOMB = 'B';
const cell_t CELL_0 = '0';
const cell_t CELL_1 = '1';
const cell_t CELL_2 = '2';
const cell_t CELL_3 = '3';
const cell_t CELL_4 = '4';
const cell_t CELL_5 = '5';
const cell_t CELL_6 = '6';
const cell_t CELL_7 = '7';
const cell_t CELL_8 = '8';
const cell_t CELL_HIDE = '-';
const cell_t CELL_FLAG = 'F';
const cell_t CELL_ERROR = 'X';

const user_action_t UA_EXIT = '0';
const user_action_t UA_ACTIVATE_CELL = '1';
const user_action_t UA_PUT_FLAG = '2';
const user_action_t UA_ERASE_FLAG = '3';

#endif // AUX_HEADER_H
