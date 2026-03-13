#pragma once

void entity_registry_new__initializes_and_returns(void);

void entity_registry_delete__succeeds(void);
void entity_registry_delete__fails_if_entity_does_not_exist(void);

void entity_registry_next__succeeds(void);
void entity_registry_next__reuse_last_deleted(void);
