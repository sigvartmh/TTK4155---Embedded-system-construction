#ifndef OLED_H_
#define OLED_H_

volatile char *oled_cm;
volatile char *oled_dt;

typedef struct {
	char *name;
	uint8_t selected;
} menu_sub_item;

typedef struct {
	char *name;
	uint8_t selected;
	menu_sub_item items[];
} menu_item;

typedef struct {
	char *name;
	uint8_t selected;
	menu_item items[];
} menu;

int OLED_init(void);
//int OLED_home(void);
int OLED_goto_line(int line);
int OLED_clear_line(int line);
int OLED_pos(int row, int column);
int OLED_print_char(char data);
int OLED_printf(char *data);

#endif