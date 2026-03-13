#pragma once

#include <stdlib.h>

struct component_registry {
  size_t *sizes;
  size_t count;
  size_t capacity;
};

struct component_registry *component_registry_new(size_t capacity);
void component_registry_free(struct component_registry *registry);

int component_registry_add(struct component_registry *registry, size_t size);
