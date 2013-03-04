/*
 * syntax.c
 *
 * Functions for analyzing the syntactical structure of a GDL file.
 *
 * Once we've parsed the GDL file, we need to process it into a form that's a
 * bit more usable for us. Process the parse tree into some syntactical
 * structures to do this.
 *
 * Created 2009/06/12
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "syntax.h"
#include "parse.h"

struct symbol_list roles[1];
struct symbol_list symbols[1];
struct symbol_list functions[1];
struct symbol_list state_args[1];

/* We've parsed the GDL file, create some better structures for it. */
void process_syntax(void)
{
	symbol_list_init(symbols);

	process_syntax_roles(root_node);
	process_syntax_symbols(root_node);
	process_syntax_functions(root_node);
	process_syntax_state_args(root_node);

	/* print out symbols */
	printf("roles:");
	print_symbol_list(roles);

	printf("symbols:");
	print_symbol_list(symbols);

	printf("func:");
	print_symbol_list(functions);

	printf("state:");
	print_symbol_list(state_args);
}

void print_symbol_list(struct symbol_list *symbols)
{
	int t;

	for (t = 0; t < symbols->size; t++)
		printf(" %s", symbols->symbols[t]->name);
	printf("\n\n");
}

#define PARSE_TREE_FUNC(name, body) \
	void name(struct parse_node *node) \
{ \
	struct parse_node *child; \
	int c; \
	{body} \
	FOR_EACH_CHILD(c, node, child) { \
		name(child); \
	} \
}

PARSE_TREE_FUNC(process_syntax_roles,
		{
		if (node->parent && node->parent->type == PARSE_ROLE &&
			node->type == PARSE_CONST)
		symbol_list_add(roles, node->name, FALSE, 0);
		});

PARSE_TREE_FUNC(process_syntax_symbols,
		{
		if (node->type == PARSE_CONST &&
			!symbol_list_contains(roles, node->name))
		symbol_list_add(symbols, node->name, FALSE, 0);
		});

PARSE_TREE_FUNC(process_syntax_functions,
		{
		if (node->type == PARSE_FUNCTION &&
			!symbol_list_contains(roles, node->name))
		symbol_list_add(functions, node->name, TRUE, node->child_count);
		});

PARSE_TREE_FUNC(process_syntax_state_args,
		{
		if (node->parent &&
			(node->parent->type == PARSE_INIT ||
			 node->parent->type == PARSE_NEXT))
		symbol_list_add(state_args, node->name, FALSE, 0);
		});

BOOL symbol_list_contains(struct symbol_list *list, char *symbol)
{
	int t;

	if (list->symbols != NULL) {
		for (t = 0; t < list->size; t++)
			if (strcmp(list->symbols[t]->name, symbol) == 0)
				return TRUE;
	}

	return FALSE;
}

void symbol_list_init(struct symbol_list *list)
{
	/* XXX ??? */
	if (list->symbols != NULL)
		free(list->symbols);

	list->symbols = NULL;
	list->size = 0;
}

void symbol_list_add(struct symbol_list *list, char *symbol, BOOL is_fn,
		s32_t arg_count)
{
	/* First, check to make sure the symbol isn't already there. */
	if (symbol_list_contains(list, symbol))
		return;

	/* The symbol isn't in the list yet, so add a new entry. */
	if (list->symbols == NULL) {
		list->size = 1;
		list->symbols = malloc(1 * sizeof(struct symbol *));
	}
	else {
		list->size++;
		list->symbols = realloc(list->symbols, list->size *
				sizeof(struct symbol *));
	}

	list->symbols[list->size - 1] = malloc(sizeof(struct symbol));
	list->symbols[list->size - 1]->name = symbol;
	list->symbols[list->size - 1]->is_fn = is_fn;
	list->symbols[list->size - 1]->arg_count = arg_count;
}
