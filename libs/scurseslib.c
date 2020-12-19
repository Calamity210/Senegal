#include <ncurses/ncurses.h>

#include "includes/scurseslib.h"
#include "../core/includes/sapi.h"
#include "../src/includes/sparser.h"
#include "../src/includes/sgcobject_utils.h"

GCClass* windowClass;

GCWindow* newWindow(VM* vm, GCClass* class, WINDOW* window) {
  GCWindow* instance = ALLOCATE_GC_OBJ(vm, GCWindow, GC_INSTANCE);

  instance->class = class;
  instance->window = window;

  return instance;
}

static Constant sglInitScr(VM* vm, int arity, Constant* args) {
  expect(0, arity, "initScr");

  WINDOW* window = initscr();

#define SET_NUM_CONSTANT(id, constant)                                        \
  do {                                                                        \
    defineGlobal(vm, id, NUM_CONST(constant));                                \
  } while (0)

  SET_NUM_CONSTANT("ACS_ULCORNER",      (ACS_ULCORNER));
  SET_NUM_CONSTANT("ACS_LLCORNER",      (ACS_LLCORNER));
  SET_NUM_CONSTANT("ACS_URCORNER",      (ACS_URCORNER));
  SET_NUM_CONSTANT("ACS_LRCORNER",      (ACS_LRCORNER));
  SET_NUM_CONSTANT("ACS_LTEE",          (ACS_LTEE));
  SET_NUM_CONSTANT("ACS_RTEE",          (ACS_RTEE));
  SET_NUM_CONSTANT("ACS_BTEE",          (ACS_BTEE));
  SET_NUM_CONSTANT("ACS_TTEE",          (ACS_TTEE));
  SET_NUM_CONSTANT("ACS_HLINE",         (ACS_HLINE));
  SET_NUM_CONSTANT("ACS_VLINE",         (ACS_VLINE));
  SET_NUM_CONSTANT("ACS_PLUS",          (ACS_PLUS));
#if !defined(__hpux) || defined(HAVE_NCURSES_H)
  SET_NUM_CONSTANT("ACS_S1",            (ACS_S1));
  SET_NUM_CONSTANT("ACS_S9",            (ACS_S9));
  SET_NUM_CONSTANT("ACS_DIAMOND",       (ACS_DIAMOND));
  SET_NUM_CONSTANT("ACS_CKBOARD",       (ACS_CKBOARD));
  SET_NUM_CONSTANT("ACS_DEGREE",        (ACS_DEGREE));
  SET_NUM_CONSTANT("ACS_PLMINUS",       (ACS_PLMINUS));
  SET_NUM_CONSTANT("ACS_BULLET",        (ACS_BULLET));
  SET_NUM_CONSTANT("ACS_LARROW",        (ACS_LARROW));
  SET_NUM_CONSTANT("ACS_RARROW",        (ACS_RARROW));
  SET_NUM_CONSTANT("ACS_DARROW",        (ACS_DARROW));
  SET_NUM_CONSTANT("ACS_UARROW",        (ACS_UARROW));
  SET_NUM_CONSTANT("ACS_BOARD",         (ACS_BOARD));
  SET_NUM_CONSTANT("ACS_LANTERN",       (ACS_LANTERN));
  SET_NUM_CONSTANT("ACS_BLOCK",         (ACS_BLOCK));
#endif
  SET_NUM_CONSTANT("ACS_BSSB",          (ACS_ULCORNER));
  SET_NUM_CONSTANT("ACS_SSBB",          (ACS_LLCORNER));
  SET_NUM_CONSTANT("ACS_BBSS",          (ACS_URCORNER));
  SET_NUM_CONSTANT("ACS_SBBS",          (ACS_LRCORNER));
  SET_NUM_CONSTANT("ACS_SBSS",          (ACS_RTEE));
  SET_NUM_CONSTANT("ACS_SSSB",          (ACS_LTEE));
  SET_NUM_CONSTANT("ACS_SSBS",          (ACS_BTEE));
  SET_NUM_CONSTANT("ACS_BSSS",          (ACS_TTEE));
  SET_NUM_CONSTANT("ACS_BSBS",          (ACS_HLINE));
  SET_NUM_CONSTANT("ACS_SBSB",          (ACS_VLINE));
  SET_NUM_CONSTANT("ACS_SSSS",          (ACS_PLUS));

#ifdef ACS_S3
  SET_NUM_CONSTANT("ACS_S3",            (ACS_S3));
#endif
#ifdef ACS_S7
  SET_NUM_CONSTANT("ACS_S7",            (ACS_S7));
#endif
#ifdef ACS_LEQUAL
  SET_NUM_CONSTANT("ACS_LEQUAL",        (ACS_LEQUAL));
#endif
#ifdef ACS_GEQUAL
  SET_NUM_CONSTANT("ACS_GEQUAL",        (ACS_GEQUAL));
#endif
#ifdef ACS_PI
  SET_NUM_CONSTANT("ACS_PI",            (ACS_PI));
#endif
#ifdef ACS_NEQUAL
  SET_NUM_CONSTANT("ACS_NEQUAL",        (ACS_NEQUAL));
#endif
#ifdef ACS_STERLING
  SET_NUM_CONSTANT("ACS_STERLING",      (ACS_STERLING));
#endif

  SET_NUM_CONSTANT("LINES", LINES);
  SET_NUM_CONSTANT("COLS", COLS);

  return GC_OBJ_CONST(newWindow(vm, windowClass, window));
}

static Constant sglCBreak(VM* vm, int arity, Constant* args) {
  expect(0, arity, "cBreak");

  return NUM_CONST(cbreak());
}

static Constant sglNoEcho(VM* vm, int arity, Constant* args) {
  expect(0, arity, "noEcho");

  return NUM_CONST(noecho());
}

Constant initCursesLib(VM* vm, int arity, Constant* args) {
  windowClass = newClass(vm, copyString(vm, NULL, "Window", 6), true);
}
