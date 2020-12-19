#ifndef SENEGAL_SCURSESLIB_H
#define SENEGAL_SCURSESLIB_H

#include "../../src/includes/svm.h"
#include <ncurses/ncurses.h>

typedef struct {
    GCObject gc;

    GCClass* class;
    WINDOW* window;
} GCWindow;

#define AS_WINDOW(c) ((GCWindow*)AS_GC_OBJ(c))

Constant initCursesLib(VM* vm, int arity, Constant* args);

#endif //SENEGAL_SCURSESLIB_H
