#ifndef __CM_SEARCH_CONTACT__
#define __CM_SEARCH_CONTACT__

#include "../config.h"
#include "../contact.h"
#include "../screen.h"
#include <stdint.h>

__CM__ struct SearchContactScreen {
  int8_t step;
  char contactName[__CM_MAX_LENGTH_CONTACT_FIELD__];
  enum ScreenType nextScreen;
  struct ContactList *contactList;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct SearchContactScreen *create_search_contact_screen(void);

__CM__ void
update_search_contact_screen(struct SearchContactScreen *const screen);

__CM__ void
draw_search_contact_screen(const struct SearchContactScreen *const screen);

__CM__ void destroy_search_contact_screen(struct SearchContactScreen **ptr);

__CM__ enum ScreenType
finish_search_contact_screen(const struct SearchContactScreen *const screen);

#if defined(__cplusplus)
}
#endif

#endif // __CM_SEARCH_CONTACT__
