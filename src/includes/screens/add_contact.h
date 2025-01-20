#ifndef __CM_ADD_CONTACT__
#define __CM_ADD_CONTACT__

#include "../config.h"
#include "../contact.h"
#include "../screen.h"
#include <stdint.h>

__CM__ struct AddContactScreen {
  struct Contact contact;
  int8_t step;
  enum ScreenType nextScreen;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct AddContactScreen *create_add_contact_screen(void);

__CM__ void update_add_contact_screen(struct AddContactScreen *const screen);

__CM__ void
draw_add_contact_screen(const struct AddContactScreen *const screen);

__CM__ void destroy_add_contact_screen(struct AddContactScreen **const ptr);

__CM__ enum ScreenType
finish_add_contact_screen(const struct AddContactScreen *const screen);

#if defined(__cplusplus)
}
#endif

#endif // __CM_ADD_CONTACT__
