#define ALECG_TRON_TURN_TIME_MS 250
#define ALECG_TRON_DEATH_FADE_MS 800

enum alecg_player_state {
    PLAYER_STATE_ALIVE = 0,
    PLAYER_STATE_DEAD,
};

bool alecg_is_moveable_location(uint8_t row, uint8_t column, uint8_t player_positons[][10]) {
    if(row > 4 || column > 9) {
        return false;
    } else if(row == 4 && (column == 4 || column == 5)) {
        return false;
    } else if(player_positons[row][column] == 1 || player_positons[row][column] == 2) {
        return false;
    }

    return true;
}

bool alecg_make_next_tron_move(uint8_t player, uint8_t player_positons[][10], uint8_t player_head[]) {
    int direction = rand() % 4;

    for(int move_tries = 0; move_tries < 4; move_tries += 1) {
        // Try left
        if(direction == 0) {
            if(alecg_is_moveable_location(player_head[0], player_head[1] - 1, player_positons)) {
                player_head[1] = player_head[1] - 1;
                return true;
            }

        // Try right
        } else if(direction == 1) {
            if(alecg_is_moveable_location(player_head[0], player_head[1] + 1, player_positons)) {
                player_head[1] = player_head[1] + 1;
                return true;
            }

        // Try up
        } else if(direction == 2) {
            if(alecg_is_moveable_location(player_head[0] - 1, player_head[1], player_positons)) {
                player_head[0] = player_head[0] - 1;
                return true;
            }

        // Try down
        } else if(direction == 3) {
            if(alecg_is_moveable_location(player_head[0] + 1, player_head[1], player_positons)) {
                player_head[0] = player_head[0] + 1;
                return true;
            }
        }

        direction = (direction + 1) % 4;
    }

    return false;
}

void alecg_animate_tron(bool initialize_animation, uint16_t elapsed_ms) {
    static uint8_t player_positons[5][10] = {{0}};

    static uint8_t player_one_head[2] = {0};
    static uint8_t player_one_state;
    static uint16_t time_since_player_one_died;

    static uint8_t player_two_head[2] = {0};
    static uint8_t player_two_state;
    static uint16_t time_since_player_two_died;

    static uint16_t time_since_last_turn;

    if(initialize_animation == true) {
        for(uint8_t row = 0; row < 5; row++) {
            for(uint8_t column = 0; column < 10; column++) {
                player_positons[row][column] = 0;
            }
        }

        player_one_state = PLAYER_STATE_ALIVE;
        player_one_head[0] = 0;
        player_one_head[1] = 0;
        player_positons[player_one_head[0]][player_one_head[1]] = 1;

        player_two_state = PLAYER_STATE_ALIVE;
        player_two_head[0] = 4;
        player_two_head[1] = 9;
        player_positons[player_two_head[0]][player_two_head[1]] = 2;

        time_since_last_turn = 0;
    }

    time_since_last_turn += elapsed_ms;

    if(time_since_last_turn >= ALECG_TRON_TURN_TIME_MS) {
        time_since_last_turn = 0;

        // Player 1 Movement
        if(player_one_state == PLAYER_STATE_ALIVE) {
            bool player_one_moved = alecg_make_next_tron_move(1, player_positons, player_one_head);

            if(player_one_moved) {
                player_positons[player_one_head[0]][player_one_head[1]] = 1;
            } else {
                player_one_state = PLAYER_STATE_DEAD;
                time_since_player_one_died = 0;

                for(uint8_t row = 0; row < 5; row++) {
                    for(uint8_t column = 0; column < 10; column++) {
                        if(player_positons[row][column] == 1) {
                            player_positons[row][column] = 3;
                        }
                    }
                }
            }
        }

        // Player 2 Movement
        if(player_two_state == PLAYER_STATE_ALIVE) {
            bool player_two_moved = alecg_make_next_tron_move(2, player_positons, player_two_head);
            if(player_two_moved) {
                player_positons[player_two_head[0]][player_two_head[1]] = 2;
            } else {
                player_two_state = PLAYER_STATE_DEAD;
                time_since_player_two_died = 0;

                for(uint8_t row = 0; row < 5; row++) {
                    for(uint8_t column = 0; column < 10; column++) {
                        if(player_positons[row][column] == 2) {
                            player_positons[row][column] = 4;
                        }
                    }
                }
            }
        }
    }

    if(player_one_state == PLAYER_STATE_DEAD) {
        time_since_player_one_died += elapsed_ms;
        bool reset_player_position = false;

        if(time_since_player_one_died > ALECG_TRON_DEATH_FADE_MS) {
            for(uint8_t row = 0; row < 5; row++) {
                for(uint8_t column = 0; column < 10; column++) {
                    if(player_positons[row][column] == 3) {
                        player_positons[row][column] = 0;
                    }

                    if(!reset_player_position && player_positons[row][column] == 0) {
                        player_one_head[0] = row;
                        player_one_head[1] = column;
                        player_positons[row][column] = 1;
                        reset_player_position = true;
                    }
                }
            }
        }

        if(reset_player_position) {
            player_one_state = PLAYER_STATE_ALIVE;
        }
    }

    if(player_two_state == PLAYER_STATE_DEAD) {
        time_since_player_two_died += elapsed_ms;
        bool reset_player_position = false;

        if(time_since_player_two_died > ALECG_TRON_DEATH_FADE_MS) {
            for(int8_t column = 9; column >= 0; column--) {
                for(int8_t row = 4; row >= 0; row--) {
                    if(player_positons[row][column] == 4) {
                        player_positons[row][column] = 0;
                    }

                    if(!reset_player_position && player_positons[row][column] == 0) {
                        player_two_head[0] = row;
                        player_two_head[1] = column;
                        player_positons[row][column] = 2;
                        reset_player_position = true;
                    }
                }
            }
        }

        if(reset_player_position) {
            player_two_state = PLAYER_STATE_ALIVE;
        }
    }

    // Draw board
    rgb_matrix_set_color_all(0, 0, 0);

    HSV player_one_hsv = { .h = 27, .s = 255, .v = 255 };
    RGB player_one_rgb = hsv_to_rgb(player_one_hsv);

    HSV player_one_dead_hsv = { .h = player_one_hsv.h, .s = player_one_hsv.s, .v = (1.0 - ((float)time_since_player_one_died / (float)ALECG_TRON_DEATH_FADE_MS)) * 255.0};
    RGB player_one_dead_rgb = hsv_to_rgb(player_one_dead_hsv);

    HSV player_two_hsv = { .h = 125, .s = 255, .v = 255 };
    RGB player_two_rgb = hsv_to_rgb(player_two_hsv);

    HSV player_two_dead_hsv = { .h = player_two_hsv.h, .s = player_two_hsv.s, .v = (1.0 - ((float)time_since_player_two_died / (float)ALECG_TRON_DEATH_FADE_MS)) * 255.0};
    RGB player_two_dead_rgb = hsv_to_rgb(player_two_dead_hsv);

    // Draw player tails
    uint8_t led_i, row, column;

    for(row = 0; row < 5; row++) {
        for(column = 0; column < 10; column++) {
            if(player_positons[row][column] == 1) {
                led_i = alecg_get_led_by_position(row, column);
                rgb_matrix_set_color(led_i, player_one_rgb.r, player_one_rgb.g, player_one_rgb.b);
            } else if(player_positons[row][column] == 2) {
                led_i = alecg_get_led_by_position(row, column);
                rgb_matrix_set_color(led_i, player_two_rgb.r, player_two_rgb.g, player_two_rgb.b);
            } else if(player_positons[row][column] == 3) {
                led_i = alecg_get_led_by_position(row, column);
                rgb_matrix_set_color(led_i, player_one_dead_rgb.r, player_one_dead_rgb.g, player_one_dead_rgb.b);
            } else if(player_positons[row][column] == 4) {
                led_i = alecg_get_led_by_position(row, column);
                rgb_matrix_set_color(led_i, player_two_dead_rgb.r, player_two_dead_rgb.g, player_two_dead_rgb.b);
            }
        }
    }

    // Draw player heads
    uint8_t head_i, head_brightness;
    head_brightness = ((float)time_since_last_turn / (float)ALECG_TRON_TURN_TIME_MS) * 255.0;

    if(player_one_state == PLAYER_STATE_ALIVE) {
        player_one_hsv.v = head_brightness;
        player_one_rgb = hsv_to_rgb(player_one_hsv);
        head_i = alecg_get_led_by_position(player_one_head[0], player_one_head[1]);
        rgb_matrix_set_color(head_i, player_one_rgb.r, player_one_rgb.g, player_one_rgb.b);
    }

    if(player_two_state == PLAYER_STATE_ALIVE) {
        player_two_hsv.v = head_brightness;
        player_two_rgb = hsv_to_rgb(player_two_hsv);
        head_i = alecg_get_led_by_position(player_two_head[0], player_two_head[1]);
        rgb_matrix_set_color(head_i, player_two_rgb.r, player_two_rgb.g, player_two_rgb.b);
    }
}
