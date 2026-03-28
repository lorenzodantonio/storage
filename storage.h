#pragma once

#include "component_registry.h"
#include <stdlib.h>

struct storage {
  struct entity_registry *entities;
  struct component_registry *components;
};

struct storage *storage_new(size_t max_entities);
void storage_free(struct storage *s);

static inline size_t storage_register_component(struct storage *storage,
                                                size_t size) {
  return component_registry_add(storage->components, size, 12);
}

static inline void storage_iterator_init(struct storage *storage,
                                         struct iterator *iter,
                                         size_t component_count,
                                         size_t component_ids[]) {
  struct component_pool *pools[64];
  for (size_t i = 0; i < component_count; i++) {
    pools[i] = component_registry_get(storage->components, component_ids[i]);
  }
  iterator_init(iter, component_count, pools);
}
