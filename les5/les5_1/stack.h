#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define STACK_OK          0
#define STACK_ERROR       -1
#define STACK_ERROR_FULL  -10
#define STACK_ERROR_EMPTY -11

#define STACK_TYPES                                                            \
	X(char)                                                                    \
	X(int)                                                                     \
	X(double)

#define X(T) int stack_push_##T(T value);
STACK_TYPES
#undef X

#define X(T) int stack_pop_##T(T *return_value);
STACK_TYPES
#undef X

bool stack_is_empty(void);
bool stack_is_full(void);

#endif
