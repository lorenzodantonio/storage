#include "entity_registry.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct storage {
  struct entity_registry *entities;
};

struct storage *storage_new(size_t max_entities) {
  struct storage *storage = malloc(sizeof(*storage));
  if (!storage) {
    return NULL;
  }

  storage->entities = entity_registry_new(max_entities);
  if (!storage->entities) {
    return NULL;
  }

  return storage;
}

void storage_free(struct storage *s) {
  entity_registry_free(s->entities);
  free(s);
}

int main(void) {
  struct storage *storage = storage_new(16);
  size_t id0 = entity_registry_next(storage->entities);
  size_t id1 = entity_registry_next(storage->entities);
  entity_registry_next(storage->entities);
  entity_registry_delete(storage->entities, id1);
  entity_registry_delete(storage->entities, id0);
  entity_registry_delete(storage->entities, id0);
  sparse_set_print(&storage->entities->freed);
  printf("new id %zu\n", entity_registry_next(storage->entities));
  storage_free(storage);
  return 0;
}
