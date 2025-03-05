#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"

#define MAX_OUTPUT 1024
char outputBuffer[MAX_OUTPUT];
int outputPos;

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

void writeOutput(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int spaceLeft = MAX_OUTPUT - outputPos - 1;
    if (spaceLeft > 0) {
        int written = vsnprintf(outputBuffer + outputPos, spaceLeft, format, args);
        if (written > 0 && written < spaceLeft) {
            outputPos += written;
        } else if (written >= spaceLeft) {
            outputPos = MAX_OUTPUT - 1;
        }
        outputBuffer[outputPos] = '\0';
    }
    va_end(args);
}

void resetOutput() {
    outputBuffer[0] = '\0';
    outputPos = 0;
}

void printValue(Value value) {
    switch(value.type) {
        case VAL_BOOL:
            writeOutput(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NUMBER: writeOutput("%g", AS_NUMBER(value)); break;
        case VAL_NIL: writeOutput("nil"); break;
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