/*
 * print.h
 *
 * Information for printing out the parse information.
 *
 * Print.c contains the functions for printing a parse tree. That's about it,
 * it's pretty small.
 *
 * Created 2009/06/12
 */

#include "main.h"
#include "parse.h"

/*
 * Prototypes
 */

void print_node(struct parse_node *node, int depth, int cmask);
