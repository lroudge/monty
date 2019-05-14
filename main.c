#include "monty.h"

char *current_line;

/**
 * monty - helper function for main function
 * @args: pointer to struct of arguments from main
 *
 * Description: opens and reads from the file
 * containing the opcodes, and calls the function
 * that will find the corresponding executing function
 */
void monty(args_t *args)
{
	size_t len = 0;
	int get = 0;
	FILE *fptr;
	char *line = NULL;
	void (*code_func)(stack_t **, unsigned int);
	stack_t *stack = NULL;

	if (args->ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fptr = fopen(args->av, "r");
	if (!fptr)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", args->av);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		args->line_number++;
		get = getline(&line, &len, fptr);
		if (get < 0)
			break;
		while (*line == ' ')
			line++;
		if (strcmp(line, "\n") == 0)
			continue;
		current_line = line;
		code_func = get_func(line);
		if (!code_func)
		{
			dprintf(2, "L%u: unknown instruction %s", args->line_number, line);
			free(line);
			exit(EXIT_FAILURE);
		}
		code_func(&stack, args->line_number);
	}
	fclose(fptr);
	free(stack);
}

/**
 * main - entry point for monty bytecode interpreter
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	args_t args;

	args.av = argv[1];
	args.ac = argc;
	args.line_number = 0;

	monty(&args);

	return (EXIT_SUCCESS);
}
