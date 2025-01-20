#include "../includes/screens/search_contact.h"
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

__CM__ struct SearchContactScreen *create_search_contact_screen(void) {
  struct SearchContactScreen *screen =
      malloc(sizeof(struct SearchContactScreen));

  if (!screen) {
#if defined(__CM_DEBUG__)
    printf("Error to reserve memory: %s\n", strerror(errno));
#endif
    return NULL;
  }

  screen->nextScreen = VOID_SCREEN;
  screen->step = 0;
  screen->contactList = NULL;

  return screen;
}

__CM__ void
update_search_contact_screen(struct SearchContactScreen *const screen) {
  switch (screen->step) {
  case 0:
    scanf("%s", screen->contactName);
    screen->contactList =
        get_contact_by_strategy(screen->contactName, include_by_name_strategy);
    if (screen->contactList) {
      screen->step = 1;
    } else {
      screen->step = 2;
    }
    break;
  case 1:;
    char value[10];
    scanf("%s", value);
    if (strcmp(value, __EXIT_TOKEN__) == 0) {
      screen->step = 2;
    }
    break;
  case 2:
    screen->nextScreen = MENU_SCREEN;
    break;
  default:
    break;
  }
}

__CM__ void
draw_search_contact_screen(const struct SearchContactScreen *const screen) {
  printf(""
         "---------------------------------------------------------\n"
         "Search contacts by name\n"
         "---------------------------------------------------------"
         "\n");

  switch (screen->step) {
  case 0:
    printf("Enter the contact name: ");
    break;
  case 1:
    if (screen->contactList) {
      print_contact_list(screen->contactList);
    }

    printf("\nType 'exit' to return to the main menu: ");
    break;
  default:
    break;
  }
}

__CM__ void destroy_search_contact_screen(struct SearchContactScreen **ptr) {
  if (ptr) {
    if ((*ptr)->contactList) {
      clear_contact_list_data((*ptr)->contactList);
      free((*ptr)->contactList);
      (*ptr)->contactList = NULL;
    }

    free(*ptr);
    *ptr = NULL;
#if defined(__CM_DEBUG__)
    printf("SearchContactScreen deleted successfully.\n");
#endif
  }
}

__CM__ enum ScreenType
finish_search_contact_screen(const struct SearchContactScreen *const screen) {
  return screen->nextScreen;
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
