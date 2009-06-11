enum relation_type { relation_true, relation_init, relation_role, relation_does,
  relation_next, relation_legal, relation_goal, relation_terminal,
  relation_distinct, relation_x };

struct relation_t {
  enum relation_type type;

};

enum parse_type {
	PARSE_UNKNOWN,
	/* User Defined stuff */
	PARSE_CONST, PARSE_VAR, PARSE_FUNCTION,
	/* Predefined constants */
	PARSE_INIT, PARSE_TRUE, PARSE_NEXT, PARSE_ROLE, PARSE_GOAL, PARSE_IMPL,
	/* Bookkeeping stuff */
	PARSE_LIST
};

struct parse_node {
	enum parse_type type;
	char *name;
	struct parse_node *parent;
	struct parse_node **children;
	int child_count;
#ifdef COND
	struct parse_node **conditions;
	int condition_count;
#endif
};

/* Global error string--so yacc and shit can use it */
extern const char *error_str;

/*
 * Prototypes
 */
/* yacc stuff */
int yywrap(void);
void yyerror(const char *);

/* parsing */
struct parse_node *new_list(struct parse_node *node);
struct parse_node *new_function(char *name, struct parse_node *args);
struct parse_node *add_legal(char *role, struct parse_node *move);
struct parse_node *new_role(char *role);
struct parse_node *new_init(struct parse_node *init);
struct parse_node *add_goal(char *role, int goal_value);
struct parse_node *add_new_node(enum parse_type type, char *name);
struct parse_node *alloc_node(char *name);
struct parse_node *new_node(enum parse_type type, char *name);
void add_child(struct parse_node *node, struct parse_node *child);
void free_node(struct parse_node *node);
