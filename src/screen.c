#include "includes/screen.h"
#include "includes/screens/add_contact.h"
#include "includes/screens/delete_contact.h"
#include "includes/screens/list_contact.h"
#include "includes/screens/menu.h"
#include "includes/screens/search_contact.h"

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

__CM__ static void *create_screen_by_type(enum ScreenType type);

#if defined(__cplusplus)
}
#endif

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ struct Screen *create_screen(enum ScreenType type) {
  struct Screen *screen = (struct Screen *)malloc(sizeof(struct Screen));
  if (!screen) {
#if defined(__CM_DEBUG__)
    printf("Error to reserve memory: %s\n", strerror(errno));
#endif
    return NULL;
  }

  screen->value = create_screen_by_type(type);
  if (!screen->value) {
    free(screen);
    screen = NULL;
    return NULL;
  }
  screen->type = type;

  return screen;
}

__CM__ void update_screen(struct Screen *screen) {
  switch (screen->type) {
  case MENU_SCREEN:
    update_menu_screen((struct MenuScreen *)screen->value);
    break;
  case ADD_CONTACT_SCREEN:
    update_add_contact_screen((struct AddContactScreen *)screen->value);
    break;
  case DELETE_CONTACT_SCREEN:
    update_delete_contact_screen((struct DeleteContactScreen *)screen->value);
    break;
  case SEARCH_CONTACT_SCREEN:
    update_search_contact_screen((struct SearchContactScreen *)screen->value);
    break;
  case LIST_CONTACT_SCREEN:
    update_list_contact_screen((struct ListContactScreen *)screen->value);
    break;
  default:
    break;
  }
}

__CM__ void draw_screen(const struct Screen *const screen) {
  switch (screen->type) {
  case MENU_SCREEN:
    draw_menu_screen((struct MenuScreen *)screen->value);
    break;
  case ADD_CONTACT_SCREEN:
    draw_add_contact_screen((struct AddContactScreen *)screen->value);
    break;
  case DELETE_CONTACT_SCREEN:
    draw_delete_contact_screen((struct DeleteContactScreen *)screen->value);
    break;
  case SEARCH_CONTACT_SCREEN:
    draw_search_contact_screen((struct SearchContactScreen *)screen->value);
    break;
  case LIST_CONTACT_SCREEN:
    draw_list_contact_screen((struct ListContactScreen *)screen->value);
    break;
  default:
    break;
  }
}

__CM__ void destroy_screen(struct Screen **ptr) {
  if (*ptr) {
    switch ((*ptr)->type) {
    case MENU_SCREEN:
      destroy_menu_screen((struct MenuScreen **)&((*ptr)->value));
      break;
    case ADD_CONTACT_SCREEN:
      destroy_add_contact_screen((struct AddContactScreen **)&(*ptr)->value);
      break;
    case DELETE_CONTACT_SCREEN:
      destroy_delete_contact_screen(
          (struct DeleteContactScreen **)&(*ptr)->value);
      break;
    case SEARCH_CONTACT_SCREEN:
      destroy_search_contact_screen(
          (struct SearchContactScreen **)&(*ptr)->value);
      break;
    case LIST_CONTACT_SCREEN:
      destroy_list_contact_screen((struct ListContactScreen **)&(*ptr)->value);
      break;
    default:
      break;
    }

    free(*ptr);
    *ptr = NULL;
  }
}

__CM__ enum ScreenType next_screen(const struct Screen *const screen) {
  enum ScreenType type = VOID_SCREEN;

  switch (screen->type) {
  case MENU_SCREEN:
    type = finish_menu_screen((const struct MenuScreen *const)screen->value);
    break;
  case ADD_CONTACT_SCREEN:
    type = finish_add_contact_screen(
        (const struct AddContactScreen *const)screen->value);
    break;
  case DELETE_CONTACT_SCREEN:
    type = finish_delete_contact_screen(
        (const struct DeleteContactScreen *const)screen->value);
    break;
  case SEARCH_CONTACT_SCREEN:
    type = finish_search_contact_screen(
        (const struct SearchContactScreen *const)screen->value);
    break;
  case LIST_CONTACT_SCREEN:
    type = finish_list_contact_screen(
        (const struct ListContactScreen *const)screen->value);
    break;
  default:
    break;
  }

  return type;
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
__CM__ static void *create_screen_by_type(enum ScreenType type) {
  void *screen = NULL;
  switch (type) {
  case MENU_SCREEN:
    screen = create_menu_screen();
    break;
  case ADD_CONTACT_SCREEN:
    screen = create_add_contact_screen();
    break;
  case DELETE_CONTACT_SCREEN:
    screen = create_delete_contact_screen();
    break;
  case SEARCH_CONTACT_SCREEN:
    screen = create_search_contact_screen();
    break;
  case LIST_CONTACT_SCREEN:
    screen = create_list_contact_screen();
    break;
  default:
    break;
  }
  return screen;
}
