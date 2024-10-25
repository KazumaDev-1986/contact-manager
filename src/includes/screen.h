#ifndef __CM_SCREEN_H__
#define __CM_SCREEN_H__

#include "config.h"

enum ScreenType {
  VOID_SCREEN = -1,
  EXIT_SCREEN = 0,
  MENU_SCREEN,
  ADD_CONTACT_SCREEN,
  DELETE_CONTACT_SCREEN,
  SEARCH_CONTACT_SCREEN,
  LIST_CONTACT_SCREEN,
};

struct Screen {
  void *value;
  enum ScreenType type;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct Screen *create_screen(enum ScreenType type);

__CM__ void update_screen(struct Screen *screen);

__CM__ void draw_screen(const struct Screen *const screen);

__CM__ void destroy_screen(struct Screen **ptr);

__CM__ enum ScreenType next_screen(const struct Screen *const screen);

#if defined(__cplusplus)
}
#endif

#endif
