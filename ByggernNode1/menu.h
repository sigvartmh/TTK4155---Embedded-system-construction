#pragma once

/*
typedef struct menu_item
{
	char *name;
	uint8_t selected;
	uint8_t children;
	struct menu_item *sub_item;
	struct menu_item *parent;
	void *(*foo) (); //Function pointer;
} menu_t;*/

void draw_menu();
int main_menu(int direction, int pos, int select);

