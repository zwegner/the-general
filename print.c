/*
 * print.c
 *
 * Functions for printing out the parse tree.
 *
 * Just contains one function now, and that's probably all it will need for
 * a while. Just recursively prints out the type, name, etc. for parse nodes.
 *
 * Created 2009/06/12
 */

#include <stdio.h>

#include "main.h"
#include "print.h"
#include "parse.h"

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
		mask = (c < node->child_count - 1) << (depth + 1);
		print_node(node->children[c], depth + 1, cmask | mask);
	}
}
