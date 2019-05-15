#include "monty.h"
#include "lists.h"

/**
 * pchar_handler - handles the pchar instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void pchar_handler(stack_t **stack, unsigned int line_number)
{
	stack_t *node = get_dnodeint_at_index(*stack, 0);
	int c = node->n;

	if (!stack)
	{
		dprintf(STDERR_FILENO, PCHAR_FAIL, line_number);
		free_all(1);
		exit(EXIT_FAILURE);
	}

	if (c < 0 || c > 127)
	{
		dprintf(STDERR_FILENO, PCHAR_RANGE, line_number);
		free_all(1);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", c);
}
