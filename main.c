#include <stdio.h>

#include "parse.h"

int main(void)
{
	while(1)
	{
	int c = 0;
		while (c<100000)
		{
			gdl_read("rules/buttons.el");

			//printf("node count = %i!\n",node_count);
			free_node(root_node);
			//		if(node_count!=0){
			//printf("node count = %i!\n",node_count);
			//			exit(0);
			//		}
			c++;
		}
		getchar();
	}

//	printf("done parsing.\n\n\n");

//	print_node(root_node, 0, 0);

	return 0;
}
