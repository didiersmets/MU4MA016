// A source file for a pointer based implementation of a Stack of integers
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "data/stack.h"

struct StackNode { /* Declaration and Definition of a struct StackNode */
	struct StackNode *next;
	int value;
};
typedef struct StackNode StackNode;

struct Stack { /* Definition of struct Stack */
	struct StackNode *head;
	size_t size;
};

Stack *stack_init()
{
	Stack *s = malloc(sizeof(Stack));
	if (s != NULL) {
		s->head = NULL;
		s->size = 0;
	}
	return (s);
}

void stack_push(Stack *s, int value)
{
	assert(s != NULL);
	StackNode *new_node = malloc(sizeof(StackNode));
	if (new_node == NULL) {
		/* Fail silently */
		return;
	}
	new_node->next = s->head;
	new_node->value = value;
	s->head = new_node;
	s->size++;
}

int stack_pop(Stack *s)
{
	assert(s != NULL && s->size != 0);
	int res = s->head->value;
	StackNode *next_head = s->head->next;
	free(s->head);
	s->head = next_head;
	s->size--;

	return (res);
}

void stack_dispose(Stack *s)
{
	if (s == NULL) {
		return;
	}
	/* First free stack nodes if any */
	while (s->head != NULL) {
		StackNode *old_head = s->head;
		s->head = s->head->next;
		free(old_head);
	}
	/* Then free s itself */
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

