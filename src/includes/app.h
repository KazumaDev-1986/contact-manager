#ifndef __APP_H__
#define __APP_H__

#include "config.h"
#include "definition.h"
#include "screen.h"

struct App {
  bool live;
  struct Screen *screen;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct App *create_app(void);

__CM__ void run_app(struct App *const app);

__CM__ void destroy_app(struct App **ptr);

#if defined(__cplusplus)
}
#endif

#endif // __APP_H__
