//menu system prototype, not finished

#include<stdlib.h>
#include<stdio.h>

typedef struct menu
{
	char *name;
	struct menu *parent;
	struct menu *sub_item;
	int children;
	void *(*functionPointer)();
	//void (*functionPointer)(float, char, char) = NULL;
} menu;

menu* MENU_create_menu(char *name)
{
	menu *new_menu = (menu*)malloc(sizeof(menu));

	if(new_menu == NULL)
    {
        printf("Out of memory!!! (create_menu)\n");
        exit(1);
    }

    new_menu->name = name;
    new_menu->sub_item = NULL;
    new_menu->children = NULL;
    new_menu->functionPointer = NULL;
    
    return new_menu;
}

void print_string(char* string){
	printf("%s\n",string );
}


menu* MENU_create_sub_menu(menu *root_menu,int number_of_subitems){
	root_menu->sub_item = realloc( NULL , number_of_subitems*sizeof(menu));
	root_menu->children = root_menu->children + number_of_subitems;
	return root_menu->sub_item;
}

menu* MENU_insert_sub_menu(menu *root_menu, char *name, int sub_element, void (*functionPointer)()){
	//root_menu->sub_item = realloc( NULL , number_of_subitems*sizeof(menu));
	root_menu->sub_item[sub_element].name = name;
	root_menu->sub_item[sub_element].parent = root_menu;
	root_menu->sub_item[sub_element].functionPointer = (void*)functionPointer;
	return root_menu->sub_item;
}

/*
void MENU_insert_sub_sub_menu(struct menu *root_menu, char *name, int sub_element, void (*functionPointer)()){
	root_menu.sub_item[sub_element].name = name;
	root_menu.sub_item[sub_element].parent = root_menu;
	root_menu.sub_item[sub_element].functionPointer = (void*)functionPointer;
}
*/
int add(int x){
	printf("%i\n",x+x);
	return x;
}

int main(){
	menu* menu = MENU_create_menu("Menu");
	MENU_insert_sub_menu(menu, "| - menu 1",0,&print_string);
}

/*
int main(){

	//char *c = "Menu";
	//int i = 0;
	
	menu* menu = MENU_create_menu("Menu");
	MENU_insert_sub_menu(menu, "| - menu 1",0,&print_string);
	
	/*
	MENU_create_sub_menu(menu,3);
	//MENU_create_sub_menu(menu->sub_item[0].sub_item,3);
	MENU_insert_sub_menu(menu, "|- menu 1",0, &print_string);
	MENU_insert_sub_menu(menu, "|- menu 2",1, &print_string);
	
	//int number_of_subitems = 2;
	//menu->sub_item[0].sub_item = realloc( NULL , number_of_subitems*sizeof(menu));
	//menu->sub_item[1].sub_item = realloc( NULL , number_of_subitems*sizeof(menu));

	//MENU_create_sub_menu(menu->sub_item[0].sub_item,3);
	//menu->sub_item[1].sub_item = MENU_create_sub_menu(menu->sub_item,3);
	menu->sub_item[0].sub_item[0].name=" |-Sub menu";
	menu->sub_item[0].sub_item[0].parent = &menu->sub_item[0];
	menu->sub_item[0].sub_item[0].functionPointer = &add;
	menu->sub_item[1].sub_item[0].name = " |-Sub menu 2";
	//menu->sub_item[1].sub_item[0].name=" |-Sub menu 2";

	//menu->sub_item[0].sub_item[0] = MENU_insert_sub_menu(menu->sub_item, "sub menu add",0, &add);
	//MENU_create_sub_menu(menu->sub_item,2);
	//MENU_insert_sub_sub_menu(menu->sub_item[0], "  |- menu 1",0, &add);
	//MENU_insert_sub_sub_menu(menu->sub_item[1], "  |- menu 2",1, &add);	

	printf("%s\n", menu->name);
	printf("%s\n", menu->sub_item[0].name);
	printf("%s\n", menu->sub_item[0].sub_item[0].name);
	menu->sub_item[0].sub_item[0].functionPointer(62);
	printf("%s\n", menu->sub_item[1].name);
	printf("%s\n", menu->sub_item[1].sub_item[0].name);
	printf("\n");
	printf("Parent menu 1: %s\n", menu->sub_item[0].parent->name);
	printf("Parent sub menu: %s\n", menu->sub_item[0].sub_item[0].parent->name);
	//printf("%s\n", menu->sub_item[0].sub_item[0].parent->name);
	//printf("%s\n", menu->sub_item[0].sub_item[0].name);
	//printf("%s\n", menu->sub_item[0].sub_item[1].name);


	printf("\n");
	menu->sub_item[0].functionPointer ("Hello there");
	menu->sub_item[1].functionPointer("WTF");
	//menu->sub_item[2].functionPointer(3);
	//menu->sub_item[0]->sub_item[0].functionPointer(6);
	return 0;

}*/