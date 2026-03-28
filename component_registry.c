#include "component_registry.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct component_registry *component_registry_new(size_t capacity) {
  struct component_registry *registry =
      malloc(sizeof(*registry) + (sizeof(*(registry->pools)) * capacity));

  registry->count = 0;
  registry->capacity = capacity;
  return registry;
}

void component_registry_free(struct component_registry *registry) {
  free(registry);
}

size_t component_registry_add(struct component_registry *registry,
                              size_t component_size, size_t capacity) {
  size_t id = registry->count++;
  struct component_pool *pool = &registry->pools[id];
  pool->id = id; // maybe just calculate from address?
  pool->component_size = component_size;
  pool->data = malloc(component_size * capacity);
  pool->count = 0;
  sparse_set_init(&pool->sparse_set, capacity);
  return id;
}

void component_registry_print(struct component_registry *registry) {
  for (size_t i = 0; i < registry->count; i++) {
    struct component_pool pool = registry->pools[i];
    printf("component_size:\t%zu\n", pool.component_size);
    printf("count\t%zu\n", pool.count);
    printf("sparse set\n");
    sparse_set_print(pool.sparse_set);
  }
}

void iterator_init(struct iterator *iter, size_t component_count,
                   struct component_pool **pools) {
  size_t i = 0;
  struct component_pool *leader = pools[i];

  for (i++; i < component_count; i++) {
    if (pools[i]->count < leader->count) {
      iter->followers[i - 1] = leader;
      leader = pools[i];
    } else {
      iter->followers[i - 1] = pools[i];
    }
  }
  iter->leader = leader;
  iter->entity = SIZE_MAX;
  iter->cursor = 0;
  iter->component_count = component_count;
}

int iterator_next(struct iterator *iter) {
  size_t cursor;
  size_t entity = SIZE_MAX;

  int match = 0;
  while (!match && iter->cursor < iter->leader->count) {
    entity = iter->leader->sparse_set.dense[iter->cursor];

    int inner_match = 1;
    size_t j = 0;
    while (inner_match && j < iter->component_count - 1) {
      struct component_pool *f = iter->followers[j++];
      inner_match = inner_match && f->sparse_set.sparse[entity] != SIZE_MAX;
    }
    match = inner_match;
    cursor = iter->cursor++;
  }

  if (!match) {
    return 0;
  }

  iter->entity = entity;

  iter->data[iter->leader->id] =
      component_pool_get_by_position(iter->leader, cursor);
  for (size_t k = 0; k < iter->component_count - 1; k++) {
    iter->data[iter->followers[k]->id] =
        component_pool_get_by_entity(iter->followers[k], entity);
  }

  return match;
}
