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

__CM__ static bool add_contact_list(struct ContactList *ptr,
                                    struct Contact *const contact);

__CM__ static long get_contact_count(FILE *file);

#if defined(__cplusplus)
}
#endif

// ---------------------------------------------------------
// Public functions definition.
// ---------------------------------------------------------
__CM__ void include_by_name_strategy(const char *name, struct Contact *contact,
                                     struct ContactList *contactList) {
  if (name == NULL || strstr(contact->name, name) != NULL) {
    add_contact_list(contactList, contact);
  }
}

__CM__ void exclude_by_name_strategy(const char *name, struct Contact *contact,
                                     struct ContactList *contactList) {
  if (name && strstr(contact->name, name) == NULL) {
    add_contact_list(contactList, contact);
  }
}

__CM__ bool save_contact(const struct Contact *const contact) {
  FILE *file = NULL;
  bool result = false;

  file = fopen(__CM_FILE_NAME__, "ab");
  if (file) {
    fwrite(contact, sizeof(struct Contact), 1, file);
    fclose(file);
    result = true;
#if defined(__CM_DEBUG__)
    printf("Contact saved successfully.\n");
#endif
  }

  return result;
}

__CM__ bool save_contact_list(const struct ContactList *const contactList) {
  bool result = false;
  FILE *file = NULL;

  file = fopen(__CM_FILE_NAME__, "ab");
  if (file) {
    struct Contact *contact = NULL;
    for (size_t i = 0; i < contactList->size; ++i) {
      contact = &contactList->data[i];
      fwrite(contact, sizeof(struct Contact), 1, file);
#if defined(__CM_DEBUG__)
      printf("ContactList saved successfully.\n");
#endif
    }
    result = true;
    fclose(file);
  }

  return result;
}

__CM__ struct ContactList *get_contact_by_strategy(const char *name,
                                                   Strategy strategy) {

  struct ContactList *contactList =
      (struct ContactList *)malloc(sizeof(struct ContactList));
  if (!contactList) {
#if defined(__CM_DEBUG__)
    printf("Error to init ContactList pointer.\n");
#endif
    return NULL;
  }

  FILE *file = NULL;
  file = fopen(__CM_FILE_NAME__, "rb");
  if (file) {

    long contactCount = get_contact_count(file);
    struct Contact *contacts = NULL;
    if (contactCount > 0) {
      contacts =
          (struct Contact *)malloc(sizeof(struct Contact) * contactCount);
      size_t read = fread(contacts, sizeof(struct Contact), contactCount, file);
      if (read == contactCount) {
        for (size_t i = 0; i < contactCount; ++i) {
          strategy(name, &contacts[i], contactList);
        }
      }
    }

    else {
#if defined(__CM_DENBUG__)
      printf("Error to open de file: %s\n", __CM_FILE_NAME__);
#endif
    }

    free(contacts);
    contacts = NULL;
    fclose(file);
  }

  return contactList;
}

__CM__ void print_contact_list(const struct ContactList *const contactList) {
  if (contactList->size > 0) {
    for (size_t i = 0; i < contactList->size; ++i) {
      const struct Contact *contact = &contactList->data[i];
      printf("nombre: %s\nemail: %s\ntelefono: %s\n\n", contact->name,
             contact->email, contact->phone);
    }
  } else {
    printf("No hay contactos almacenados.\n");
  }
}

__CM__ void clear_contact_list_data(struct ContactList *const contactList) {
  if (contactList && contactList->data) {
    free(contactList->data);
    contactList->data = NULL;
    contactList->size = 0;
  }
}

__CM__ void clear_contact_list(struct ContactList **const ptr) {
  if (ptr && *ptr) {
    if ((*ptr)->data) {
      clear_contact_list_data(*ptr);
    }

    free(*ptr);
    *ptr = NULL;
  }
}

__CM__ bool delete_contact_by_name(const char *name) {
  bool result = false;

  struct ContactList *contactList =
      get_contact_by_strategy(name, include_by_name_strategy);

  printf("ES NULL: %d\n", contactList == NULL);
  if (contactList && contactList->data) {
    clear_contact_list(&contactList);
    contactList = get_contact_by_strategy(name, exclude_by_name_strategy);

    if (contactList && remove(__CM_FILE_NAME__) == 0) {
      result = save_contact_list(contactList);
    }
  }

  clear_contact_list(&contactList);
  return result;
}

// ---------------------------------------------------------
// Internal functions definition.
// ---------------------------------------------------------
__CM__ static void copy_field(char *const dest, char *const source) {
  strncpy(dest, source, __CM_MAX_LENGTH_CONTACT_FIELD__ - 1);
  dest[__CM_MAX_LENGTH_CONTACT_FIELD__ - 1] = '\0';
}

__CM__ static bool add_contact_list(struct ContactList *ptr,
                                    struct Contact *const contact) {
  bool result = 1;
  struct Contact *temp = NULL;
  size_t size = ptr->size + 1;

  // TODO: improve memory assign.
  if (ptr->data == NULL) {
    temp = (struct Contact *)malloc(sizeof(struct Contact));
  } else {
    temp = (struct Contact *)realloc(ptr->data, size * sizeof(struct Contact));
  }

  if (temp) {
    result = 0;
    ptr->data = temp;
    ptr->data[ptr->size] = (struct Contact){0};
    copy_field(ptr->data[ptr->size].name, contact->name);
    copy_field(ptr->data[ptr->size].email, contact->email);
    copy_field(ptr->data[ptr->size].phone, contact->phone);

    ptr->size = size;
  }

  return result;
}

__CM__ static long get_contact_count(FILE *file) {
  long count = 0;

  if (file) {
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    if (fileSize > 0) {
      count = fileSize / sizeof(struct Contact);
    }
  }

  return count;
}
