#include "test_datastructure.h"
#include "test_entity_registry.h"

#include <stdio.h>

int main(void) {
  printf("running tests\n");

  // sparse set
  sparse_set_new__initializes_and_returns();
  sparse_set_push__succeds();
  sparse_set_push__fails_if_element_already_exists();

  sparse_set_remove__succeeds_with_last_element();
  sparse_set_remove__swaps_last_dense_array_element();
  sparse_set_remove__fails_if_element_does_not_exist();
  sparse_set_remove__swaps_last_dense_array_element();

  // entity registry
  entity_registry_new__initializes_and_returns();

  entity_registry_delete__succeeds();
  entity_registry_delete__fails_if_entity_does_not_exist();

  entity_registry_next__succeeds();
  entity_registry_next__reuse_last_deleted();

  return 0;
}
