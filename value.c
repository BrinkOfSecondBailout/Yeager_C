#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"

#define MAX_OUTPUT 1024
static char outputBuffer[MAX_OUTPUT];
static int outputPos = 0;

void initValueArray(ValueArray *array) {
    array->count = 0;
    array->capacity = 0;
    array->values = NULL;
}

void writeValueArray(ValueArray *array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray *array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void writeOutput(const char *text) {
    int len = strlen(text);
    if (outputPos + len < MAX_OUTPUT - 1) {
        strcpy(outputBuffer + outputPos, text);
        outputPos += len;
    }
}

void resetOutput() {
    outputBuffer[0] = '\0';
    outputPos = 0;
}

void printValue(Value value) {
    switch(value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
        case VAL_NIL: printf("nil"); break;
        case VAL_OBJ: printObject(value); break;
    }
}

bool valuesEqual(Value a, Value b) {
    if (a.type != b.type) return false;
    switch (a.type) {
        case VAL_BOOL:          return AS_BOOL(a) == AS_BOOL(b);
        case VAL_NIL:           return true;
        case VAL_NUMBER:        return AS_NUMBER(a) == AS_NUMBER(b);
        case VAL_OBJ:           return AS_OBJ(a) == AS_OBJ(b);
        default:                return false;
    }
}