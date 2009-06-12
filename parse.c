#include <stdio.h>
#include <stdlib.h>

#include "parse.h"

extern FILE *yyin;
extern char *yytext;
const char *error_str;
struct parse_node *root_node;

extern int yyparse(void);

int node_count = 0;

void *gdl_read(char *filename)
{
	int r;
	FILE *file;

	file = fopen(filename, "r");
	if (file == NULL) {
		perror("fopen");
		return NULL;
	}
	yyin = file;
	r = yyparse();
	fclose(file);
	if (!r) {
		return NULL;
	} else
		return NULL;
}

int yywrap(void)
{
	return 1;
}

void yyerror(const char *s)
{
	error_str = s;
	fprintf(stderr, "%s: line near \"%s\"\n", s, yytext);
}

/* Recursively print out a parsing tree by node. */
void print_node(struct parse_node *node, int depth, int cmask)
{
	int mask;
	int s;
	int c;

	/*
	for (s = 0; s < depth; s++) {
		if ((1 << s) & cmask)
			printf("| ");
		else
			printf("  ");
	}
	printf("|\n");
	*/

	for (s = 0; s < depth; s++) {
		if ((1 << s) & cmask)
			printf("| ");
		else
			printf("  ");
	}

	if (node->child_count > 0)
		printf("+-+>");
	else
		printf("+-->");

	printf(" t=%i n='%s' c=%i\n", node->type, node->name, node->child_count);

	for (c = 0; c < node->child_count; c++) {
		/* Create a mask saying whether this depth has any more children. */
		mask = (c < node->child_count - 1) << depth + 1;
		print_node(node->children[c], depth + 1, cmask | mask);
	}
}

/*
 * Parser functions--used inside the yacc-generated parser
 */

/* Basics */
struct parse_node *new_variable(char *name)
{
	return new_node(PARSE_VAR, name);
}

struct parse_node *new_constant(char *name)
{
	return new_node(PARSE_CONST, name);
}

struct parse_node *new_list(struct parse_node *node)
{
	struct parse_node *list;

	list = new_node(PARSE_LIST, strdup("LIST"));
	add_child(list, node);

	return list;
}

struct parse_node *new_function(char *name, struct parse_node *args)
{
	struct parse_node *node;

	node = new_node(PARSE_FUNCTION, name);
	add_child(node, args);

	return node;
}

/* Specific types/relations etc. */
struct parse_node *new_implication(struct parse_node *conc,
	struct parse_node *premises)
{
	struct parse_node *node;

	node = new_node(PARSE_IMPL, strdup("IMPL"));
	add_child(node, conc);
	add_child(node, premises);

	return node;
}

struct parse_node *new_role(struct parse_node *role)
{
	struct parse_node *node;

	node = new_node(PARSE_ROLE, strdup("ROLE"));
	add_child(node, role);

	return node;
}

struct parse_node *new_role_var(struct parse_node *role)
{
	struct parse_node *node;

	node = new_node(PARSE_ROLE, strdup("ROLE"));
	add_child(node, role);

	return node;
}

struct parse_node *new_init(struct parse_node *init)
{
	struct parse_node *node;

	node = new_node(PARSE_INIT, strdup("INIT"));
	add_child(node, init);

	return node;
}

struct parse_node *new_true(struct parse_node *child)
{
	struct parse_node *node;

	/* (true) is a unary relation. The argument is <expr>. */
	node = new_node(PARSE_TRUE, strdup("TRUE"));
	add_child(node, child);

	return node;
}

struct parse_node *new_next(struct parse_node *child)
{
	struct parse_node *node;

	/* (next) is a unary relation. The argument is <expr>. */
	node = new_node(PARSE_NEXT, strdup("NEXT"));
	add_child(node, child);

	return node;
}

struct parse_node *new_not(struct parse_node *child)
{
	struct parse_node *node;

	/* (not) is a unary relation. The argument is <expr>. */
	node = new_node(PARSE_NOT, strdup("NOT"));
	add_child(node, child);

	return node;
}

struct parse_node *new_or(struct parse_node *children)
{
	struct parse_node *node;

	/* (or) is an n-ary relation. The argument is a list of <expr>s. */
	node = new_node(PARSE_OR, strdup("OR"));
	add_child(node, children);

	return node;
}

struct parse_node *new_distinct(struct parse_node *child_1,
	struct parse_node *child_2)
{
	struct parse_node *node;

	/* (distinct) is a binary relation. The arguments are <expr> <expr>. */
	node = new_node(PARSE_DISTINCT, strdup("DISTINCT"));
	add_child(node, child_1);
	add_child(node, child_2);

	return node;
}

struct parse_node *new_does(struct parse_node *role, struct parse_node *move)
{
	struct parse_node *node;

	/* (does) is a binary relation. The arguments are <role> <move>. */
	node = new_node(PARSE_DOES, strdup("DOES"));
	add_child(node, role);
	add_child(node, move);

	return node;
}

struct parse_node *new_legal(struct parse_node *role, struct parse_node *move)
{
	struct parse_node *node;

	/* (legal) is a binary relation. The arguments are <role> <move>. */
	node = new_node(PARSE_LEGAL, strdup("LEGAL"));
	add_child(node, role);
	add_child(node, move);

	return node;
}

struct parse_node *new_terminal(void)
{
	return new_node(PARSE_TERMINAL, strdup("TERMINAL"));
}

struct parse_node *new_goal(char *role, int goal_value)
{
	struct parse_node *node;
	char *goal_str;

	asprintf(&goal_str, "%i", goal_value);
	node = new_node(PARSE_GOAL, strdup("GOAL"));
	add_child(node, new_node(PARSE_CONST, role));
	add_child(node, new_node(PARSE_CONST, goal_str));

	return node;
}

#ifdef COND
struct parse_node *add_conditions(struct parse_node *node,
	struct parse_node *conditions)
{

}
#endif

/*
 * Utility functions--these are used for general maintenance shit.
 */
/* Is this function needed? */
struct parse_node *new_node(enum parse_type type, char *name)
{
	struct parse_node *node;

//	printf("new node (%s)\n",name);
	node = alloc_node(name);
	node->type = type;

	return node;
}

struct parse_node *alloc_node(char *name)
{
	struct parse_node *node;

	/* We alloc the node on the heap. This is only done in the parser, so I
		think the overhead involved is overpowered by the simplicity gained
		by not creating an ad hoc heap. If the entire code generation process
		takes longer than a few msec, then I might reconsider this... */
	node = (struct parse_node *)malloc(sizeof(struct parse_node));
	if (node == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	node->type = PARSE_UNKNOWN;
	node->name = name;
	node->parent = NULL;
	node->children = NULL;
	node->child_count = 0;
#ifdef COND
	node->conditions = NULL;
	node->condition_count = 0;
#endif
	node_count++;

	return node;
}

/* Add a parse node (i.e. an argument) to the child list of a parse node. */
void add_child(struct parse_node *node, struct parse_node *child)
{
//	printf("adding child to '%s'\n",node->name);
	/* no children yet: malloc a new list */
	if (node->child_count == 0) {
		node->child_count = 1;
		node->children = (struct parse_node **)malloc(
				sizeof(struct parse_node *));
//		printf("creating children to %i, %p\n",node->child_count, node->children);
	}
	/* Existing list, just extend it with realloc */
	else {
		node->child_count++;
		node->children = (struct parse_node **)realloc(node->children,
				sizeof(struct parse_node *) * node->child_count);
//		printf("extending children to %i, %p\n",node->child_count, node->children);
	}

	/* Set the child. */
	node->children[node->child_count - 1] = child;
}

#ifdef COND
/* Add a parse node (i.e. an condition) to the condition list of a parse
	node. This is done when we back up the parser to an implication. The
	conclusion is the parse node, and each premise is passed here as a child
	node. Or we are passed a list of conditions. Who knows.   */
void add_condition(struct parse_node *node, struct parse_node *condition)
{
	/* no conditionren yet: malloc a new list */
	if (node->condition_count == 0) {
		node->condition_count = 1;
		node->conditions = (struct parse_node **)malloc(
				sizeof(struct parse_node *));
	}
	/* Existing list, just extend it with realloc */
	else {
		node->condition_count++;
		node->conditions = (struct parse_node **)realloc(node->conditions,
				sizeof(struct parse_node *) * node->condition_count);
	}

	/* Set the condition. */
	node->conditions[node->condition_count - 1] = condition;
}
#endif

/* Free the memory taken up by a node. I'm not sure this is really needed,
	since presumably the parser is run as a process, it creates a player,
	then it exits. So maybe it can all be handled a bit later by the OS when
	this process exits. That's microoptimization for later. */
void free_node(struct parse_node *node)
{
	int c;

	/* Recursively delete children. */
	if (node->children != NULL) {
		for (c = 0; c < node->child_count; c++)
			free_node(node->children[c]);
		/* Free the actual list. */
		free(node->children);
	}

#ifdef COND
	/* Recursively delete conditions. */
	if (node->conditions != NULL) {
		for (c = 0; c < node->condition_count; c++)
			free_node(node->conditions[c]);
		/* Free the actual list. */
		free(node->conditions);
	}
#endif

	/* Free the name. Assume this string was allocated at some point by
		the parser... */
	if (node->name != NULL)
		free(node->name);

	node_count--;

	free(node);
}
