// A source file for an array based implementation of a Stack of integers
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "data/stack.h"

struct Stack { /* Definition of struct Stack */
	size_t size; /* Number of elements in the stack        */
	size_t capacity; /* Capacity of the array holding elements */
	int *data; /* The data array itself                  */
};

Stack *stack_init()
{
	Stack *s = malloc(sizeof(Stack));
	if (s != NULL) {
		s->size = 0;
		s->capacity = 0;
		s->data = NULL;
	}
	return (s);
}

void stack_push(Stack *s, int value)
{
	assert(s != NULL);
	if (s->size >= s->capacity) {
		size_t new_cap = s->capacity == 0 ? 1 : 2 * s->capacity;
		int *new_data = realloc(s->data, new_cap * sizeof(int));
		if (new_data != NULL) {
			s->data = new_data;
			s->capacity = new_cap;
		} else {
			return;
		}
	}
	s->data[s->size] = value;
	s->size++;
}

int stack_pop(Stack *s)
{
	assert(s != NULL && s->size > 0);
	s->size--;
	return (s->data[s->size]);
}

void stack_dispose(Stack *s)
{
	if (s == NULL) {
		return;
	}
	free(s->data);
	free(s);
}

bool stack_is_empty(Stack *s)
{
	assert(s != NULL);
	return (s->size == 0);
}

size_t stack_size(Stack *s)
{
	assert(s != NULL);
	return (s->size);
}

