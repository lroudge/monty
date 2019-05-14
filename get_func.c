#include "monty.h"

/**
 * get_func - selects the right function
 * @line: line from the bytecode file passed to main
 *
 * Return: pointer to the selected function, or NULL on failure
 */
void (*get_func(char *line))(stack_t **, unsigned int)
{
	instruction_t func_arr[] = {
		{"push", push_handler},
		{"pall", pall_handler}
	};

	int codes = 2, i;

	for (i = 0; i < codes; i++)
	{
		if (strncmp(func_arr[i].opcode, line, 4) == 0)
			return (func_arr[i].f);
	}
	return (NULL);
}

/**
 * push_handler - handles the push instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void push_handler(stack_t **stack, unsigned int line_number)
{
	stack_t *new;
	int num = 0, i;
	char *bcode = strtok(current_line, " ");

	if (strcmp(bcode, "push") != 0)
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n", line_number, bcode);
		return;
	}

	bcode = strtok(NULL, " ");
	for (i = 0; bcode[i]; i++)
	{
		if (isalpha(bcode[i]) != 0)
		{
			dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}

	num = atoi(bcode);

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		return;
	}

	new->n = num;
	new->next = *stack;
	new->prev = NULL;

	if (*stack)
		(*stack)->prev = new;
	*stack = new;
}

/**
 * pall_handler - handles the pall instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void pall_handler(stack_t **stack, unsigned int line_number)
{
	stack_t *h;
	char *bcode = strtok(current_line, " ");

	if (strncmp(bcode, "pall", 4) != 0)
	{
		dprintf(2, "L%u: unknown instruction %s\n", line_number, bcode);
		return;
	}

	h = *stack;

	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
}
