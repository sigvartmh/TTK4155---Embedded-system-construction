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

//void OLED_start_scroll(void);


#endif