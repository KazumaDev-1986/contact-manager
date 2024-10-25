#include "../includes/screens/add_contact.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// Internal functions declaration.
// ---------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ struct AddContactScreen *create_add_contact_screen(void) {
  struct AddContactScreen *screen = malloc(sizeof(struct AddContactScreen));
  if (!screen) {
#if defined(__CM_DEBUG__)
    printf("Error to reserve memory: %s\n", strerror(errno));
#endif
    return NULL;
  }

  screen->step = 0;
  screen->nextScreen = VOID_SCREEN;

  return screen;
}

__CM__ void update_add_contact_screen(struct AddContactScreen *const screen) {
  switch (screen->step) {
  case 0:
    scanf("%s", screen->contact.name);
    screen->step = 1;
    break;
  case 1:
    scanf("%s", screen->contact.email);
    screen->step = 2;
    break;
  case 2:
    scanf("%s", screen->contact.phone);
    screen->step = 3;
    break;
  default:
    save_contact(&screen->contact);
    screen->nextScreen = MENU_SCREEN;
    break;
  }
}

__CM__ void
draw_add_contact_screen(const struct AddContactScreen *const screen) {
  printf(""
         "---------------------------------------------------------\n"
         "Ingrese los datos del contacto\n"
         "---------------------------------------------------------"
         "\n");

  switch (screen->step) {
  case 0:
    printf("Ingrese el nombre: ");
    break;
  case 1:
    printf("Ingrese el email: ");
    break;
  case 2:
    printf("Ingrese el teléfono: ");
    break;
  default:
    break;
  }
}

__CM__ void destroy_add_contact_screen(struct AddContactScreen **const ptr) {
  if (ptr) {
    free(*ptr);
    *ptr = NULL;
#if defined(__CM_DEBUG__)
    printf("AddContactScreen deleted successfully.");
#endif
  }
}

__CM__ enum ScreenType
finish_add_contact_screen(const struct AddContactScreen *const screen) {
  return screen->nextScreen;
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
