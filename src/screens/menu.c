#include "../includes/screens/menu.h"
#include "../includes/screen.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ struct MenuScreen *create_menu_screen(void) {
  struct MenuScreen *menu =
      (struct MenuScreen *)malloc(sizeof(struct MenuScreen));
  if (!menu) {
    printf("Error to reserve memory: %s\n", strerror(errno));
    return NULL;
  }
  menu->nextScreen = VOID_SCREEN;
  return menu;
}

__CM__ void update_menu_screen(struct MenuScreen *menu) {
  char value[2];
  char *endptr;

  scanf("%s", value);
  long result = strtol(value, &endptr, 10);
  if (*endptr != '\0') {
    result = -1;
  }

  switch (result) {
  case 1:
    menu->nextScreen = ADD_CONTACT_SCREEN;
    break;
  case 2:
    menu->nextScreen = DELETE_CONTACT_SCREEN;
    break;
  case 3:
    menu->nextScreen = SEARCH_CONTACT_SCREEN;
    break;
  case 4:
    menu->nextScreen = LIST_CONTACT_SCREEN;
    break;
  case 5:
    menu->nextScreen = EXIT_SCREEN;
    break;
  default:
    menu->nextScreen = VOID_SCREEN;
    break;
  }
}

__CM__ void draw_menu_screen(const struct MenuScreen *const menu) {
  printf(""
         "1. Agregar contacto\n"
         "2. Eliminar contacto\n"
         "3. Buscar contacto\n"
         "4. Listar todos los contactos\n"
         "5. Salir\n"
         "");
}

__CM__ void destroy_menu_screen(struct MenuScreen **ptr) {
  if (*ptr) {
    free(*ptr);
    *ptr = NULL;

#if defined(__CM_DEBUG__)
    printf("Menu was destroyed successfuly\n");
#endif
  }
}
__CM__ enum ScreenType finish_menu_screen(const struct MenuScreen *const menu) {
  return menu->nextScreen;
}