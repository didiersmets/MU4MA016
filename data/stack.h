// A Header file for a Stack of integers API
#include <stdbool.h> /* For bool type   */
#include <stddef.h> /* For size_t type */

struct Stack; /* Declaration only of the type : struct Stack*/
typedef struct Stack Stack; /* Alias :
			     * Allows to write Stack instead of struct Stack */

/* Create a new stack */
Stack *stack_init();

/* Pushes a new element (int) on top of the stack */
void stack_push(Stack *s, int value);

/* Pop the top element from the stack */
/* NOTE : stack should NOT be empty   */
int stack_pop(Stack *s);

/* Dispose an existing stack */
void stack_dispose(Stack *s);

/* Check if stack is empty */
bool stack_is_empty(Stack *s);

/* Number of elements in the stack */
size_t stack_size(Stack *s);
