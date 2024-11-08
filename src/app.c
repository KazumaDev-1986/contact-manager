#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "includes/app.h"
#include "includes/screen.h"

// ---------------------------------------------------------
// Internal functions declaration.
// ---------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

__CM__ static void update_app(struct App *const app);
__CM__ static void draw_app(const struct App *const app);
__CM__ static void clear_background(void);
__CM__ static void change_screen_app(struct App *const app,
                                     enum ScreenType type);
__CM__ static void verify_screen_app(struct App *const app);
#if defined(__cplusplus)
}
#endif

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ struct App *create_app(void) {
  struct App *app = (struct App *)malloc(sizeof(struct App));
  if (!app) {
#if defined(__CM_DEBUG__)
    printf("Error to reserve memory: %s\n", strerror(errno));
#endif
    return NULL;
  }

  app->screen = create_screen(MENU_SCREEN);
  if (!app->screen) {
    free(app);
    app = NULL;
    return NULL;
  }
  app->live = true;

  return app;
}

__CM__ void run_app(struct App *const app) {
  while (app->live) {
    clear_background();
    draw_app(app);
    update_app(app);
  }
}

__CM__ void destroy_app(struct App **ptr) {
  if (ptr) {
    destroy_screen(&(*ptr)->screen);
    free(*ptr);
    *ptr = NULL;

#if defined(__CM_DEBUG__)
    printf("App destroy successfully");
#endif
  }
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
__CM__ static void clear_background(void) { system("clear"); }

__CM__ static void update_app(struct App *const app) {
  sleep(1);
  update_screen(app->screen);

  enum ScreenType type = next_screen(app->screen);
  if (type == EXIT_SCREEN) {
    app->live = false;
  } else if (type != VOID_SCREEN) {
    change_screen_app(app, type);
    verify_screen_app(app);
  }
}

__CM__ static void draw_app(const struct App *const app) {
  draw_screen(app->screen);
}

__CM__ static void change_screen_app(struct App *const app,
                                     enum ScreenType type) {
  destroy_screen(&app->screen);
  app->screen = create_screen(type);
}

__CM__ static void verify_screen_app(struct App *const app) {
  if (!app->screen) {
#if defined(__CM_DEBUG__)
    printf("Error to asign screen memory.");
#endif
    app->live = false;
  }
}
