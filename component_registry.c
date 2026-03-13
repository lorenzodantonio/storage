#include "component_registry.h"
#include <stdint.h>
#include <string.h>

struct component_registry *component_registry_new(size_t capacity) {
  struct component_registry *registry = malloc(sizeof(*registry));
  registry->sizes = malloc(sizeof(size_t) * capacity);
  for (size_t i = 0; i < capacity; i++) {
    registry->sizes[i] = SIZE_MAX;
  }
  registry->count = 0;
  registry->capacity = capacity;
  return registry;
}

void component_registry_free(struct component_registry *registry) {
  free(registry);
}

int component_registry_add(struct component_registry *registry, size_t size) {
  size_t id = registry->count;
  registry->sizes[id] = size;
  registry->count++;
  return id;
}
