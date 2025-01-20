#ifndef __CM_DELETE_CONTACT_H__
#define __CM_DELETE_CONTACT_H__

#include "../config.h"
#include "../definition.h"
#include "../screen.h"
#include <stdint.h>

__CM__ struct DeleteContactScreen {
  char contactName[__CM_MAX_LENGTH_CONTACT_FIELD__];
  int8_t step;
  bool isDeleted;
  enum ScreenType nextScreen;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct DeleteContactScreen *create_delete_contact_screen(void);

__CM__ void
update_delete_contact_screen(struct DeleteContactScreen *const screen);

__CM__ void
draw_delete_contact_screen(const struct DeleteContactScreen *const screen);

__CM__ void
destroy_delete_contact_screen(struct DeleteContactScreen **const ptr);

__CM__ enum ScreenType
finish_delete_contact_screen(const struct DeleteContactScreen *const screen);

#if defined(__cplusplus)
}
#endif

#endif // __CM_DELETE_CONTACT_H__
