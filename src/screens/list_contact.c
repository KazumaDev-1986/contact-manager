#include "../includes/screens/list_contact.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *const EXIT_TOKEN = "salir";

// ---------------------------------------------------------
// Internal functions declaration.
// ---------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

__CM__ static void
draw_list_contact(const struct ContactList *const contactList);

__CM__ static void set_next_screen(struct ListContactScreen *const screen,
                                   char *const value);

#if defined(__cplusplus)
}
#endif

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ struct ListContactScreen *create_list_contact_screen(void) {
  struct ListContactScreen *screen =
      (struct ListContactScreen *)malloc(sizeof(struct ListContactScreen));
  if (!screen) {
#if defined(__CM_DEBUG__)
    printf("Error to reserve memory: %s\n", strerror(errno));
#endif
    return NULL;
  }

  screen->nextScreen = VOID_SCREEN;
  screen->contactList = get_contact_by_name(NULL);

  return screen;
}

__CM__ void update_list_contact_screen(struct ListContactScreen *const screen) {
  char value[10];
  scanf("%s", value);
  set_next_screen(screen, value);
}

__CM__ void
draw_list_contact_screen(const struct ListContactScreen *const screen) {
  printf(""
         "---------------------------------------------------------\n"
         "Listado de los contactos\n"
         "---------------------------------------------------------"
         "\n");

  draw_list_contact(&screen->contactList);
  printf("\nEscriba 'salir' para regresar al menu principal: ");
}

__CM__ void destroy_list_contact_screen(struct ListContactScreen **ptr) {
  if (*ptr) {
    free(*ptr);
    *ptr = NULL;
#if defined(__CM_DEBUG__)
    printf("ListContactScreen deleted successfully.");
#endif
  }
}

__CM__ enum ScreenType
finish_list_contact_screen(const struct ListContactScreen *const screen) {
  return screen->nextScreen;
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
__CM__ static void
draw_list_contact(const struct ContactList *const contactList) {
  if (contactList->size > 0) {
    for (size_t i = 0; i < contactList->size; ++i) {
      const struct Contact *contact = &contactList->data[i];
      printf("nombre: %s\nemail: %s\ntelefono: %s\n\n", contact->name,
             contact->email, contact->phone);
    }
  } else {
    printf("No hay contactos almacenados.\n");
  }
}

__CM__ static void set_next_screen(struct ListContactScreen *const screen,
                                   char *const value) {
  if (strcmp(value, EXIT_TOKEN) == 0) {
    screen->nextScreen = MENU_SCREEN;
  }
}
