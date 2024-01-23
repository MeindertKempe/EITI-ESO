#include "stack.h"
#include <stdlib.h>

#define STACK_ENTRIES 16

typedef union {
#define X(T) T val_##T;
	STACK_TYPES
#undef X
} stack_entry_t;

stack_entry_t stack[STACK_ENTRIES];

// Number of entries used in the stack, index of first empty entry
int stack_size = 0;

#define stack_push(T)                                                          \
	int stack_push_##T(T value) {                                              \
		int error = STACK_OK;                                                  \
		if (stack_is_full()) {                                                 \
			error = STACK_ERROR_FULL;                                          \
		} else {                                                               \
			stack[stack_size].val_##T = value;                                 \
			stack_size               += 1;                                     \
		}                                                                      \
		return error;                                                          \
	}

#define stack_pop(T)                                                           \
	int stack_pop_##T(T *return_value) {                                       \
		int error = STACK_OK;                                                  \
		if (stack_is_empty()) {                                                \
			error = STACK_ERROR_EMPTY;                                         \
		} else {                                                               \
			stack_size   -= 1;                                                 \
			*return_value = stack[stack_size].val_##T;                         \
		}                                                                      \
		return error;                                                          \
	}

#define X(T) stack_push(T)
STACK_TYPES
#undef X

#define X(T) stack_pop(T)
STACK_TYPES
#undef X

bool stack_is_full(void) { return stack_size == STACK_ENTRIES; }

bool stack_is_empty(void) { return stack_size == 0; }
