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
