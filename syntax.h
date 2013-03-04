/*
 * syntax.h
 *
 * Data structures for analyzing the syntactical structure of a GDL file.
 *
 * Contains data for the post-parsing stage of code generation. We have parsed
 * the GDL file into a parse_node tree, and we now need some structures to be
 * able to use it coherently.
 *
 * Created 2009/06/12
 */

#include "main.h"
#include "parse.h"

/* A symbol is a user defined constant or function. */
struct symbol
{
	BOOL is_fn;
	s32_t arg_count;
	char *name;
};

struct symbol_list
{
	struct symbol **symbols;
	u32_t size;
};

#define FOR_EACH_SYMBOL(t,tk,ls) for ((t)=0;(t)<(ls)->size&&((tk)=(ls)->symbols[t]);(t)++)

/* Global data */
extern struct symbol_list roles[1];
extern struct symbol_list symbols[1];
extern struct symbol_list functions[1];
extern struct symbol_list state_args[1];

/* Prototypes */
void process_syntax(void);
void print_symbol_list(struct symbol_list *symbols);
void process_syntax_roles(struct parse_node *node);
void process_syntax_symbols(struct parse_node *node);
void process_syntax_functions(struct parse_node *node);
void process_syntax_state_args(struct parse_node *node);
void process_syntax_node(struct parse_node *node);
BOOL symbol_list_contains(struct symbol_list *list, char *symbol);
void symbol_list_init(struct symbol_list *list);
void symbol_list_add(struct symbol_list *list, char *symbol, BOOL is_fn,
		s32_t arg_count);
