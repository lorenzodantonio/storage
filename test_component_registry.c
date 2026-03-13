#include "test_component_registry.h"
#include "assert.h"
#include "component_registry.h"
#include <stdint.h>

void component_registry_new__succeeds(void) {
  size_t capacity = 8;
  struct component_registry *registry = component_registry_new(capacity);

  assert(registry->count == 0);
  assert(registry->capacity == capacity);
  for (size_t i = 0; i < registry->capacity; i++) {
    assert(registry->sizes[i] == SIZE_MAX);
  }

  component_registry_free(registry);
}

void component_registry_add__succeeds(void) {
  struct component_registry *registry = component_registry_new(8);
  size_t component_size = sizeof(struct x { int y; });
  int component_id = component_registry_add(registry, component_size);

  assert(component_id == 0);
  assert(registry->sizes[component_id] == component_size);

  component_registry_free(registry);
}
