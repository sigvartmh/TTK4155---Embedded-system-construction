#ifndef MENU_H_
#define MENU_H_

struct screen {
	char *name;
	struct screen *parent;
	struct screen *child[3];
	int8_t child_selected;
	uint8_t game_on;
};

uint8_t circle_inc, circle_dec, music_on, song_on;

struct screen * init_menu(void);
void draw_screen(struct screen *display_screen, char *direction, uint8_t lives, uint16_t score);
uint8_t menu_get_option_uart(void);
uint8_t menu_get_option_joy(void);

#endif