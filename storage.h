#pragma once

#include <stdlib.h>

struct storage {
  struct entity_registry *entities;
  struct component_registry *components;
};

struct storage *storage_new(size_t max_entities);
void storage_free(struct storage *s);

size_t storage_register_component(struct storage *storage, size_t size);
