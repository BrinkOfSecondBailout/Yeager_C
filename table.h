#ifndef table_h
#define table_h

#include "value.h"

typedef struct {
    ObjString *key;
    Value value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableSet(Table *table, ObjString *key, Value value);
bool tableDelete(Table *table, ObjString *key);
void tableAddAll(Table *from, Table *to);
bool tableGet(Table *table, ObjString *key, Value *value);
ObjString *tableFindString(Table *table, const char *chars, int length, uint32_t hash);
void tableRemoveWhite(Table* table);
void markTable(Table *table);

#endif