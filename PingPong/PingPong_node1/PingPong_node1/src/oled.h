#ifndef OLED_H_
#define OLED_H_

int OLED_init(void);

int OLED_home(void);

int OLED_goto_line(int line);
int OLED_pos(int row, int column);

int OLED_clear_line(int line);
int OLED_clear();

int OLED_print_char(char data);
int OLED_print(char *data);

int OLED_draw_mario(void);
int OLED_draw_circle(uint8_t x, uint8_t y, uint8_t r);

#endif