#include "../includes/screens/delete_contact.h"
#include "../includes/contact.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// Internal functions declaration.
// ---------------------------------------------------------

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------

__CM__ struct DeleteContactScreen *create_delete_contact_screen(void) {
  struct DeleteContactScreen *screen =
      (struct DeleteContactScreen *)malloc(sizeof(struct DeleteContactScreen));
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

__CM__ void
update_delete_contact_screen(struct DeleteContactScreen *const screen) {
  switch (screen->step) {
  case 0:
    scanf("%s", screen->contactName);
    screen->isDeleted = delete_contact_by_name(screen->contactName);
    screen->step = 1;
    break;
  case 1:;
    char key[10];
    scanf("%s", key);
    if (strcmp(key, __EXIT_TOKEN__) == 0) {
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
draw_delete_contact_screen(const struct DeleteContactScreen *const screen) {
  printf(""
         "---------------------------------------------------------\n"
         "Delete contact\n"
         "---------------------------------------------------------"
         "\n");
  switch (screen->step) {
  case 0:
    printf("\nEnter the contact name: ");
    break;
  case 1:
    if (screen->isDeleted) {
      printf("\nThe user with the name '%s' has been deleted\n",
             screen->contactName);
    } else {
      printf("\nThe user with the name '%s' was not found\n",
             screen->contactName);
    }

    printf("\nType 'exit' to return to the main menu: ");
    break;
  default:
    break;
  }
}

__CM__ void
destroy_delete_contact_screen(struct DeleteContactScreen **const ptr) {
  if (ptr && (*ptr)) {
    free((*ptr));
    (*ptr) = NULL;
#if defined(__CM_DEBUG__)
    printf("DeleteContactScreen deleted successfully.\n");
#endif
  }
}

__CM__ enum ScreenType
finish_delete_contact_screen(const struct DeleteContactScreen *const screen) {
  return screen->nextScreen;
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
