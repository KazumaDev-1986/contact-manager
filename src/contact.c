#include "includes/contact.h"
#include "includes/config.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// Internal functions declaration.
// ---------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

__CM__ static void copy_field(char *const origin, char *const dest);

#if defined(__cplusplus)
}
#endif

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ bool save_contact(const struct Contact *const contact) {
  FILE *file = NULL;
  bool result = false;

  file = fopen(__CM_FILE_NAME__, "wb");
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

__CM__ struct Contact *get_contact_by_name(const char *name) {
  struct Contact *contact = NULL;

  FILE *file = NULL;
  file = fopen(__CM_FILE_NAME__, "rb");
  if (file) {

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    size_t contactCount = fileSize / sizeof(struct Contact);

    struct Contact *contacts =
        (struct Contact *)malloc(sizeof(struct Contact) * contactCount);
    size_t read = fread(contacts, sizeof(struct Contact), contactCount, file);
    if (read != contactCount) {
#if defined(__CM_DENBUG__)
      printf("Error to open de file: %s\n", __CM_FILE_NAME__);
#endif
      free(contacts);
      contacts = NULL;
      fclose(file);
      return NULL;
    }

    for (size_t i = 0; i < contactCount; ++i) {
      if (strcmp(contacts[i].name, name) == 0) {
        contact = (struct Contact *)malloc(sizeof(struct Contact));
        copy_field(contacts[i].name, contact->name);
        copy_field(contacts[i].email, contact->email);
        copy_field(contacts[i].phone, contact->phone);
      }
    }

    free(contacts);
    contacts = NULL;

    fclose(file);
  }

  return contact;
}

__CM__ struct Contact **list_contact(void) { return NULL; }

__CM__ void delete_contact_by_name(const char *name) {
  // TODO
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
__CM__ static void copy_field(char *const origin, char *const dest) {
  strncpy(dest, origin, sizeof(dest) - 1);
  dest[__CM_MAX_LENGTH_CONTACT_FIELD__ - 1] = '\0';
}
