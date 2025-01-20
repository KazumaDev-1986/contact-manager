#ifndef __CM_CONTANT_H__
#define __CM_CONTANT_H__

#include "config.h"
#include "definition.h"
#include <stddef.h>
#include <stdint.h>

__CM__ struct Contact {
  char name[__CM_MAX_LENGTH_CONTACT_FIELD__];
  char email[__CM_MAX_LENGTH_CONTACT_FIELD__];
  char phone[__CM_MAX_LENGTH_CONTACT_FIELD__];
};

__CM__ struct ContactList {
  struct Contact *data;
  size_t size;
};

__CM__ typedef void (*Strategy)(const char *, struct Contact *,
                                struct ContactList *);

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ void include_by_name_strategy(const char *name, struct Contact *contact,
                                     struct ContactList *contactList);

__CM__ void exclude_by_name_strategy(const char *name, struct Contact *contact,
                                     struct ContactList *contactList);

__CM__ bool save_contact(const struct Contact *const contact);

__CM__ bool save_contact_list(const struct ContactList *const contactList);

__CM__ struct ContactList *get_contact_by_strategy(const char *name,
                                                   Strategy strategy);

__CM__ void print_contact_list(const struct ContactList *const contactList);

__CM__ void clear_contact_list_data(struct ContactList *const contactList);

__CM__ void clear_contact_list(struct ContactList **const ptr);

__CM__ bool delete_contact_by_name(const char *name);

#if defined(__cplusplus)
}
#endif

#endif //__CM_CONTANT_H__
