#include "component_registry.h"
#include "entity_registry.h"
#include "storage.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
  int x;
  int y;
} Position;

size_t position_id;

int main(void) {
  struct storage *storage = storage_new(16);
  position_id = component_registry_add(storage->components, sizeof(Position));

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
