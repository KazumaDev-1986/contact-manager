#ifndef __CM_LIST_CONTACT__
#define __CM_LIST_CONTACT__

#include "../config.h"
#include "../contact.h"
#include "../screen.h"

struct ListContactScreen {
  struct ContactList *contactList;
  enum ScreenType nextScreen;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ struct ListContactScreen *create_list_contact_screen(void);

__CM__ void update_list_contact_screen(struct ListContactScreen *const screen);

__CM__ void
draw_list_contact_screen(const struct ListContactScreen *const screen);

__CM__ void destroy_list_contact_screen(struct ListContactScreen **ptr);

__CM__ enum ScreenType
finish_list_contact_screen(const struct ListContactScreen *const screen);

#if defined(__cplusplus)
}
#endif

#endif
