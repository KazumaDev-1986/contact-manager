#ifndef __CM_CONTANT_H__
#define __CM_CONTANT_H__

#include "config.h"
#include "definition.h"
#include <stddef.h>
#include <stdint.h>

struct Contact {
  char name[__CM_MAX_LENGTH_CONTACT_FIELD__];
  char email[__CM_MAX_LENGTH_CONTACT_FIELD__];
  char phone[__CM_MAX_LENGTH_CONTACT_FIELD__];
};

struct ContactList {
  struct Contact *data;
  size_t size;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ bool save_contact(const struct Contact *const contact);

__CM__ struct ContactList get_contact_by_name(const char *name);

__CM__ void delete_contact_by_name(const char *name);

#if defined(__cplusplus)
}
#endif

#endif //__CM_CONTANT_H__
