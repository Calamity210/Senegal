#include <stdio.h>
#include <stdlib.h>
#include "includes/sapi.h"
#include "includes/stable_utils.h"
#include "includes/sparser.h"

void expect(int expected, int actual, char *name) {
  if (actual != expected) {
    printf("%s expected %d args, but found %d", name, expected, actual);
    exit(1);
  }
}

void defineClassNativeFunc(VM* vm, const char* id, NativeFunc function, GCClass* class) {
  push(vm, GC_OBJ_CONST(copyString(vm, NULL, id, (int)strlen(id))));
  push(vm, GC_OBJ_CONST(newNative(vm, function)));
  tableInsert(vm, &class->methods, AS_STRING(vm->coroutine->stack[0]), vm->coroutine->stack[1]);
  pop(vm);
  pop(vm);
}

void defineClassNativeField(VM* vm, const char* id, Constant field, GCClass* class) {
  push(vm, GC_OBJ_CONST(copyString(vm, NULL, id, (int)strlen(id))));
  tableInsert(vm, &class->fields, AS_STRING(vm->coroutine->stack[0]), field);
  pop(vm);
}

void defineClassNativeStaticFunc(VM* vm, const char* id, NativeFunc function, GCClass* class) {
  push(vm, GC_OBJ_CONST(copyString(vm, NULL, id, (int)strlen(id))));
  push(vm, GC_OBJ_CONST(newNative(vm, function)));
  tableInsert(vm, &class->staticMethods, AS_STRING(vm->coroutine->stack[0]), vm->coroutine->stack[1]);
  pop(vm);
  pop(vm);
}

void defineClassNativeStaticField(VM* vm, const char* id, Constant field, GCClass* class) {
  push(vm, GC_OBJ_CONST(copyString(vm, NULL, id, (int)strlen(id))));
  tableInsert(vm, &class->staticFields, AS_STRING(vm->coroutine->stack[0]), field);
  pop(vm);
}

void defineGlobal(VM* vm, const char* id, Constant field) {
  push(vm, GC_OBJ_CONST(copyString(vm, NULL, id, (int)strlen(id))));
  tableInsert(vm, &vm->globals, AS_STRING(vm->coroutine->stack[0]), field);
  pop(vm);
}

void defineGlobalFunc(VM* vm, const char* id, NativeFunc function) {
  push(vm, GC_OBJ_CONST(copyString(vm, NULL, id, (int)strlen(id))));
  push(vm, GC_OBJ_CONST(newNative(vm, function)));
  tableInsert(vm, &vm->globals, AS_STRING(vm->coroutine->stack[0]), vm->coroutine->stack[1]);
  pop(vm);
  pop(vm);
}

Constant assertApi(VM* vm, int arity, Constant *args) {
  if (arity < 2) {
    printf("assert expected two arguments, but found  %d", arity);
    exit(1);
  }

  /// assert(arg1, arg2, "MSGs"...);
  if (!areEqual(args[0], args[1])) {
    if (arity >= 3) {
      for (int i = 1; i < arity; i++)
        printConstant(args[i]);

      printf("\n");
    } else {
      printf("ASSERT(");
      printConstant(args[0]);
      printf(" != ");
      printConstant(args[1]);
      printf(")");
    }

    exit(1);
  }

  return NULL_CONST;
}

Constant printApi(VM* vm, int arity, Constant* args) {
  for (int i = 0; i < arity; i++)
    printConstant(args[i]);

  return NULL_CONST;
}

Constant printlnApi(VM* vm, int arity, Constant* args) {

  for (int i = 0; i < arity; i++)
    printConstant(args[i]);

  printf("\n");

  return NULL_CONST;
}