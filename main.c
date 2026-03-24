#include "component_registry.h"
#include "entity_registry.h"
#include "storage.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  float vx, vy;
} Velocity;

size_t position_id;
size_t velocity_id;

void initialize(struct storage *storage) {
  position_id = storage_register_component(storage, sizeof(Position));
  velocity_id = storage_register_component(storage, sizeof(Velocity));
}

void update_position(struct storage *storage, float dt) {
  (void)dt;
  struct component_pool *pool =
      component_registry_get(storage->components, position_id);

  for (size_t i = 0; i < pool->count; i++) {
    Position *pos = component_pool_get_by_position(pool, i);
    pos->x++;
    pos->y--;
  }
}

int main(void) {
  struct storage *storage = storage_new(16);
  initialize(storage);

  size_t id0 = entity_registry_next(storage->entities);
  size_t id1 = entity_registry_next(storage->entities);
  entity_registry_delete(storage->entities, id0);
  entity_registry_delete(storage->entities, id1);

  struct component_pool *velocities =
      component_registry_get(storage->components, velocity_id);

  size_t id2 = entity_registry_next(storage->entities);
  size_t id3 = entity_registry_next(storage->entities);

  Velocity *vel1 = component_pool_emplace(velocities, id2);
  vel1->vx = 12.0f;
  vel1->vy = 23.0f;

  Velocity *vel2 = component_pool_emplace(velocities, id3);
  vel2->vx = 13.0f;
  vel2->vy = 24.0f;

  struct component_pool *positions =
      component_registry_get(storage->components, position_id);

  Position *pos1 = component_pool_emplace(positions, id0);
  pos1->x = 3;
  pos1->y = 4;

  Position *pos2 = component_pool_emplace(positions, id3);
  pos2->x = 23;
  pos2->y = 43;

  for (size_t i = 0; i < 100; i++) {
    update_position(storage, 0);
  }
  component_registry_print(storage->components);
  fflush(stdout);

  storage_free(storage);
  return 0;
}
