#ifndef __CM_CONTANT_H__
#define __CM_CONTANT_H__

#include "config.h"
#include "definition.h"
#include <stdint.h>

struct Contact {
  char name[100];
  char email[100];
  char phone[100];
};

struct ListContact {
  struct Contact *contact;
  int32_t length;
};

#if defined(__cplusplus)
extern "C" {
#endif

__CM__ bool save_contact(const struct Contact *const contact);

__CM__ struct Contact *get_contact_by_name(const char *name);

__CM__ struct Contact **list_contact(void);

__CM__ void delete_contact_by_name(const char *name);

#if defined(__cplusplus)
}
#endif

#endif //__CM_CONTANT_H__
