#pragma once

typedef struct menu_item
{
	char *name;
	uint8_t selected;
	uint8_t children;
	struct menu_item *sub_item;
	struct menu_item *parent;
	void *(*foo) (); //Function pointer;
} menu_t;

void draw_menu();


*menu_item create_item(uint8_t selected, uint8_t children, menu_t *submenu, menu_t *parent){

	menu_t *new_menu_item =malloc(sizeof(menu_t));

	f(new_menu_item == NULL){
		fprintf(uart,"Out of memory!!! (create_node)\n");
		exit(1);
	}

	new_menu_item -> name = name;
	new_menu_item -> selected = selected;
	new_menu_item -> parent = parent;
	new_menu_item -> sub_item = sub_item;

}

sub_item = realloc( NULL , #subitems*sizeof(menu_t) )


foo = printf;


Menu
|-submenu
	|- submenu
		|-
|-submenu
	|- submenu