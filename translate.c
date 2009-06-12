#include "parse.h"

int token = 0;

/* Prototypes for this file. */
void translate_roles(void);

/* Translate a full parse tree into code. Sounds easy, huh? */
void translate(void)
{
	ASSERT(root_node->type == PARSE_LIST);

	/* Roles go first! Their tokens get the first enums for indexing. */
	translate_roles();
}

void translate_roles(void)
{
	struct parse_node *node;
	int c;

	/* The valid roles are only at the root of the parse tree. So, assuming
		that the root node is a LIST, loop through its children and find ones
		that are of type ROLE. */
	printf("roles:");
	for (c = 0; c < root_node->child_count; c++) {
		node = root_node->children[c];
		if (node->type == PARSE_ROLE)
			printf(" %s", node->name);
	}
	printf("\n");
}
