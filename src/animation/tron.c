#include "ergodox_ez.h"

#define ALECG_TRON_PLAYER_COUNT 4
#define ALECG_TRON_TURN_TIME_MS 450
#define ALECG_TRON_DEATH_FADE_MS 1350

enum alecg_player_state {
    PLAYER_STATE_ALIVE = 0,
    PLAYER_STATE_DEAD,
};

typedef struct PACKED
{
	uint8_t row;
	uint8_t column;
} alecg_tron_position;

typedef struct PACKED
{
	alecg_tron_position head;
	uint8_t id;
	uint8_t state;
	uint16_t time_spent_dead_ms;
} alecg_tron_player;

void alecg_respawn_dead_player(alecg_tron_player *player, uint8_t player_positons[][10]);
void alecg_move_tron_player(alecg_tron_player *player, uint8_t player_positons[][10]);
bool alecg_make_random_move(alecg_tron_player *player, uint8_t player_positons[][10]);
bool alecg_is_moveable_location(uint8_t row, uint8_t column, uint8_t player_positons[][10]);
RGB alecg_get_player_color(uint8_t player_id, uint8_t value);

void alecg_animate_tron(bool initialize_animation, uint16_t elapsed_ms) {
    static uint8_t player_positons[5][10] = {{0}};
    static alecg_tron_player alecg_tron_players[ALECG_TRON_PLAYER_COUNT] = {{{0}}};

    static uint16_t time_since_last_turn;

    if(initialize_animation == true) {
        for(uint8_t row = 0; row < 5; row++) {
            for(uint8_t column = 0; column < 10; column++) {
                player_positons[row][column] = 0;
            }
        }

        for(uint8_t i = 0; i < ALECG_TRON_PLAYER_COUNT; i++) {
            alecg_tron_players[i] = (alecg_tron_player) { .head = {0}, .id = i + 1, .state = PLAYER_STATE_DEAD, .time_spent_dead_ms = 0 };
            alecg_respawn_dead_player(&alecg_tron_players[i], player_positons);
        }

        time_since_last_turn = 0;
    }

    time_since_last_turn += elapsed_ms;

    // Handle players after a turn has elapsed
    if(time_since_last_turn >= ALECG_TRON_TURN_TIME_MS) {
        time_since_last_turn = 0;

        for(uint8_t i = 0; i < ALECG_TRON_PLAYER_COUNT; i++) {
            if(alecg_tron_players[i].state == PLAYER_STATE_ALIVE) {
                alecg_move_tron_player(&alecg_tron_players[i], player_positons);
            } else if(alecg_tron_players[i].state == PLAYER_STATE_DEAD && alecg_tron_players[i].time_spent_dead_ms >= ALECG_TRON_DEATH_FADE_MS) {
                alecg_respawn_dead_player(&alecg_tron_players[i], player_positons);
            }
        }
    }

    // Update dead player fade timer
    for(uint8_t i = 0; i < ALECG_TRON_PLAYER_COUNT; i++) {
        if(alecg_tron_players[i].state == PLAYER_STATE_DEAD) {
            alecg_tron_players[i].time_spent_dead_ms = MIN(alecg_tron_players[i].time_spent_dead_ms + elapsed_ms, ALECG_TRON_DEATH_FADE_MS);
        }
    }

    // Draw board
    uint8_t led_i;
    alecg_tron_player player;
    RGB empty_board_color = (RGB) { .r = 0, .g = 0, .b = 0 };
    RGB player_color;

    for(uint8_t row = 0; row < 5; row++) {
        for(uint8_t column = 0; column < 10; column++) {
            if(row == 4 && (column == 4 || column == 5)) {
                // No LEDs here, skip
                continue;
            } else if(player_positons[row][column] == 0) {
                // Empty board space
                player_color = empty_board_color;
            } else if(player_positons[row][column] <= ALECG_TRON_PLAYER_COUNT) {
                // Board space with player tail
                player = alecg_tron_players[player_positons[row][column] - 1];
                player_color = alecg_get_player_color(player.id, 255);
            } else if(player_positons[row][column] > ALECG_TRON_PLAYER_COUNT) {
                // Board space with dead player tail
                player = alecg_tron_players[(player_positons[row][column] / 10) - 1];
                player_color = alecg_get_player_color(player.id, (1.0 - ((float)MIN(player.time_spent_dead_ms, ALECG_TRON_DEATH_FADE_MS) / (float)ALECG_TRON_DEATH_FADE_MS)) * 255.0);
            }

            led_i = alecg_get_led_by_position(row, column);
            rgb_matrix_set_color(led_i, player_color.r, player_color.g, player_color.b);
        }
    }

    // Draw player heads
    uint8_t head_brightness = ((float)time_since_last_turn / (float)ALECG_TRON_TURN_TIME_MS) * 255.0;

    for(uint8_t i = 0; i < ALECG_TRON_PLAYER_COUNT; i++) {
        if(alecg_tron_players[i].state == PLAYER_STATE_ALIVE) {
            player_color = alecg_get_player_color(alecg_tron_players[i].id, head_brightness);

            led_i = alecg_get_led_by_position(alecg_tron_players[i].head.row, alecg_tron_players[i].head.column);
            rgb_matrix_set_color(led_i, player_color.r, player_color.g, player_color.b);
        }
    }
}

void alecg_respawn_dead_player(alecg_tron_player *player, uint8_t player_positons[][10]) {
    bool was_player_position_reset = false;
    uint8_t row, column;
    uint8_t random_row_offset = rand() % 5;
    uint8_t random_column_offset = rand() % 10;

    for(uint8_t row_counter = 0; row_counter < 5; row_counter++) {
        for(uint8_t column_counter = 0; column_counter < 10; column_counter++) {
            row = (row_counter + random_row_offset) % 5;
            column = (column_counter + random_column_offset) % 10;

            if((player_positons[row][column] == player->id) || (player_positons[row][column] == (player->id * 10))) {
                player_positons[row][column] = 0;
            }

            if(!was_player_position_reset && player_positons[row][column] == 0) {
                player->head = (alecg_tron_position) { .row = row, .column = column };
                player->state = PLAYER_STATE_ALIVE;
                player->time_spent_dead_ms = 0;

                player_positons[row][column] = player->id;
                was_player_position_reset = true;
            }
        }
    }
}

void alecg_move_tron_player(alecg_tron_player *player, uint8_t player_positons[][10]) {
    bool player_moved = alecg_make_random_move(player, player_positons);

    if(player_moved) {
        player_positons[player->head.row][player->head.column] = player->id;
    } else {
        player->state = PLAYER_STATE_DEAD;
        player->time_spent_dead_ms = 0;

        for(uint8_t row = 0; row < 5; row++) {
            for(uint8_t column = 0; column < 10; column++) {
                if(player_positons[row][column] == player->id) {
                    player_positons[row][column] = player->id * 10;
                }
            }
        }
    }
}

bool alecg_make_random_move(alecg_tron_player *player, uint8_t player_positons[][10]) {
    int direction = rand() % 4;

    for(int move_tries = 0; move_tries < 4; move_tries += 1) {
        // Try left
        if(direction == 0) {
            if(alecg_is_moveable_location(player->head.row, player->head.column - 1, player_positons)) {
                player->head.column = player->head.column - 1;
                return true;
            }

        // Try right
        } else if(direction == 1) {
            if(alecg_is_moveable_location(player->head.row, player->head.column + 1, player_positons)) {
                player->head.column = player->head.column + 1;
                return true;
            }

        // Try up
        } else if(direction == 2) {
            if(alecg_is_moveable_location(player->head.row - 1, player->head.column, player_positons)) {
                player->head.row = player->head.row - 1;
                return true;
            }

        // Try down
        } else if(direction == 3) {
            if(alecg_is_moveable_location(player->head.row + 1, player->head.column, player_positons)) {
                player->head.row = player->head.row + 1;
                return true;
            }
        }

        direction = (direction + 1) % 4;
    }

    return false;
}

bool alecg_is_moveable_location(uint8_t row, uint8_t column, uint8_t player_positons[][10]) {
    if(row > 4 || column > 9) {
        return false;
    } else if(row == 4 && (column == 4 || column == 5)) {
        return false;
    } else if(player_positons[row][column] > 0 && player_positons[row][column] <= ALECG_TRON_PLAYER_COUNT) {
        return false;
    }

    return true;
}

RGB alecg_get_player_color(uint8_t player_id, uint8_t value) {
    HSV hsv = { .h = 0, .s = 255, .v = value };

    if(player_id == 1) {
        hsv.h = 27;
    } else if(player_id == 2) {
        hsv.h = 125;
    } else if(player_id == 3) {
        hsv.h = 80;
    } else if(player_id == 4) {
        hsv.h = 215;
    }

    return hsv_to_rgb(hsv);
}
