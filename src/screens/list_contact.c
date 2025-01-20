#include "../includes/screens/list_contact.h"
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
  screen->contactList = get_contact_by_strategy(NULL, include_by_name_strategy);
  if (!screen->contactList) {
    free(screen);
    screen = NULL;
    return NULL;
  }

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
         "List of contacts\n"
         "---------------------------------------------------------"
         "\n");

  print_contact_list(screen->contactList);
  printf("\nType 'exit' to return to the main menu: ");
}

__CM__ void destroy_list_contact_screen(struct ListContactScreen **ptr) {
  if (ptr && *ptr) {
    if ((*ptr)->contactList->data) {
      clear_contact_list_data((*ptr)->contactList);

      free((*ptr)->contactList);
      (*ptr)->contactList = NULL;
    }

    free(*ptr);
    *ptr = NULL;
#if defined(__CM_DEBUG__)
    printf("ListContactScreen deleted successfully.\n");
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
__CM__ static void set_next_screen(struct ListContactScreen *const screen,
                                   char *const value) {
  if (strcmp(value, __EXIT_TOKEN__) == 0) {
    screen->nextScreen = MENU_SCREEN;
  }
}
