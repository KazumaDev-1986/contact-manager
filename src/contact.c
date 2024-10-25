#include "includes/contact.h"
#include "includes/config.h"
#include <stdio.h>

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ bool save_contact(const struct Contact *const contact) {
  FILE *file = NULL;
  bool result = false;

  file = fopen(__CM_FILE_NAME, "wb");
  if (file) {
    fwrite(contact, sizeof(struct Contact), 1, file);
    fclose(file);
    result = true;
#if defined(__CM_DEBUG__)
    printf("Contact saved successfully.");
#endif
  }

  return result;
}

__CM__ struct Contact *get_contact_by_name(const char *name) { return NULL; }

__CM__ struct Contact **list_contact(void) { return NULL; }

__CM__ void delete_contact_by_name(const char *name) {
  // TODO
}
