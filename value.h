#ifndef value_h
#define value_h

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

#define MAX_OUTPUT 1024
extern char outputBuffer[MAX_OUTPUT];
extern int outputPos;

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj *obj;
    } as;
} Value;

#define IS_BOOL(value)              ((value).type == VAL_BOOL)
#define IS_NIL(value)               ((value).type == VAL_NIL)
#define IS_NUMBER(value)            ((value).type == VAL_NUMBER)
#define IS_OBJ(value)               ((value).type == VAL_OBJ)

#define AS_OBJ(value)               ((value).as.obj)
#define AS_BOOL(value)              ((value).as.boolean)
#define AS_NUMBER(value)            ((value).as.number)

#define OBJ_VAL(object)             ((Value){VAL_OBJ, {.obj = (Obj*)object}})
#define BOOL_VAL(value)             ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL                     ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value)           ((Value){VAL_NUMBER, {.number = value}})

typedef struct {
    int count;
    int capacity;
    Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
void writeOutput(const char *format, ...);
void resetOutput();
void printValue(Value value);
bool valuesEqual(Value a, Value b);

#endif