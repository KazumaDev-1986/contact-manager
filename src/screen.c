#include "includes/screen.h"
#include "includes/screens/menu.h"
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
    break;
  case DELETE_CONTACT_SCREEN:
    break;
  case SEARCH_CONTACT_SCREEN:
    break;
  case LIST_CONTACT_SCREEN:
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
    break;
  case DELETE_CONTACT_SCREEN:
    break;
  case SEARCH_CONTACT_SCREEN:
    break;
  case LIST_CONTACT_SCREEN:
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
      break;
    case DELETE_CONTACT_SCREEN:
      break;
    case SEARCH_CONTACT_SCREEN:
      break;
    case LIST_CONTACT_SCREEN:
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
    break;
  case DELETE_CONTACT_SCREEN:
    break;
  case SEARCH_CONTACT_SCREEN:
    break;
  case LIST_CONTACT_SCREEN:
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
    break;
  case DELETE_CONTACT_SCREEN:
    break;
  case SEARCH_CONTACT_SCREEN:
    break;
  case LIST_CONTACT_SCREEN:
    break;
  default:
    break;
  }
  return screen;
}