#ifndef MENU_H_
#define MENU_H_

struct menu_item_t {
	char *name;
	struct menu_item_t *parent_item;
	struct menu_item_t *sub_item; //-> menu_item_t **sub_items;
	uint8_t selected;
};

struct menu_t {
	char *name;
	struct menu_item_t *items[2];
	uint8_t selected;
};

uint8_t item_selected;

void init_menu(void);
uint8_t draw_menu(uint8_t menu_display, uint8_t direction);

#endif