#ifndef MENU_H_
#define MENU_H_

typedef struct menu_item
{
	char *name;
	uint8_t selected;
	uint8_t children;
	struct menu_item *sub_item;
	struct menu_item *parent;
	//void *foo (const *void); Function pointer;
} menu_t;

void draw_menu();

#endif MENU_H_