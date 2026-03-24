#include "entity_registry.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int entity_registry_exists(struct entity_registry *registry, size_t entity) {
  if (registry->freed.sparse[entity] != SIZE_MAX) {
    return 0;
  }
  return entity < registry->count;
}

struct entity_registry *entity_registry_new(size_t capacity) {
  struct entity_registry *registry = malloc(sizeof(*registry));
  if (!registry) {
    return NULL;
  }

  sparse_set_init(&registry->freed, capacity);

  registry->capacity = capacity;
  registry->head = 0;
  registry->count = 0;
  return registry;
}

void entity_registry_free(struct entity_registry *registry) {
  free(registry->freed.dense);
  free(registry->freed.sparse);
  free(registry);
}

size_t entity_registry_next(struct entity_registry *registry) {
  size_t id;
  if (registry->freed.count > 0) {
    id = registry->freed.dense[--(registry->freed.count)];
    registry->freed.sparse[id] = SIZE_MAX;
    registry->freed.count--;
  } else {
    id = registry->head++;
  }
  registry->count++;
  return id;
}

int entity_registry_delete(struct entity_registry *registry, size_t entity) {
  if (entity >= registry->count) {
    return -1;
  }

  if (registry->freed.sparse[entity] != SIZE_MAX) {
    return -1;
  }

  sparse_set_push(&registry->freed, entity);
  return 0;
}
