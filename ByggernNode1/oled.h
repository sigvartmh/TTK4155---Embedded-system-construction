#ifndef OLED_H_
#define OLED_H_

volatile char *oled_cm;
volatile char *oled_dt;

typedef struct {
	char *name;
	menu_item[] items;
	uint8_t selected;
} menu;

typedef struct {
	char *name;
	menu_sub_item[] items;
	uint8_t selected;
} menu_item;

typedef struct {
	char *name;
	menu_sub_item[] items;
	uint8_t selected;
} menu_sub_item;

int OLED_init(void);
//int OLED_home(void);
int OLED_goto_line(int line);
int OLED_clear_line(int line);
//int OLED_pos(int row, int column);
int OLED_print_char(char data);
int OLED_printf(char *data);

#endif