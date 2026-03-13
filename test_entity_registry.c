#include "entity_registry.h"
#include <assert.h>

void entity_registry_new__initializes_and_returns(void) {
  struct entity_registry *r = entity_registry_new(16);
  assert(r->count == 0);
  assert(r->head == 0);
  assert(r->capacity == 16);
  entity_registry_free(r);
}

void entity_registry_delete__succeeds(void) {
  struct entity_registry *r = entity_registry_new(16);
  size_t e = entity_registry_next(r);
  entity_registry_delete(r, e);
  assert(entity_registry_exists(r, e) == 0);
  entity_registry_free(r);
}

void entity_registry_delete__fails_if_entity_does_not_exist(void) {
  struct entity_registry *r = entity_registry_new(16);
  entity_registry_next(r);
  int res = entity_registry_delete(r, 100);
  assert(res == -1);
  entity_registry_free(r);
}

void entity_registry_next__succeeds(void) {
  struct entity_registry *r = entity_registry_new(16);
  size_t id = entity_registry_next(r);
  assert(id == 0);
  entity_registry_free(r);
}

void entity_registry_next__reuse_last_deleted(void) {
  struct entity_registry *r = entity_registry_new(16);
  size_t old = entity_registry_next(r);
  entity_registry_delete(r, old);
  size_t new = entity_registry_next(r);
  assert(old == new);

  entity_registry_free(r);
}

void entity_registry_exists__finds_id_if_exists(void) {
  struct entity_registry *r = entity_registry_new(16);
  size_t id = entity_registry_next(r);
  assert(entity_registry_exists(r, id) == 0);
  entity_registry_free(r);
}
