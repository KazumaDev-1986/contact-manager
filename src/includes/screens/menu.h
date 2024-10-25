#ifndef __MENU_H__
#define __MENU_H__

#include "../config.h"
#include "../screen.h"

__CM__ struct MenuScreen {
  enum ScreenType nextScreen;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct MenuScreen *create_menu_screen(void);

__CM__ void update_menu_screen(struct MenuScreen *menu);

__CM__ void draw_menu_screen(const struct MenuScreen *const menu);

__CM__ void destroy_menu_screen(struct MenuScreen **ptr);

__CM__ enum ScreenType finish_menu_screen(const struct MenuScreen *const menu);

#if defined(__cplusplus)
}
#endif

#endif // __MENU_H__
