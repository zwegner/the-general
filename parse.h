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
	PARSE_INIT, PARSE_TRUE, PARSE_NEXT, PARSE_ROLE, PARSE_GOAL, PARSE_TERMINAL,
	PARSE_IMPL, PARSE_NOT, PARSE_OR, PARSE_DISTINCT, PARSE_DOES, PARSE_LEGAL,
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
	/* Whether this node has been translated already. */
	int used;
};

/* Global error string--so yacc and shit can use it */
extern const char *error_str;

extern struct parse_node *root_node;

/*
 * Prototypes
 */
/* yacc stuff */
int yywrap(void);
void yyerror(const char *);

void translate(void);

void print_node(struct parse_node *node, int depth, int cdepth);
/* parsing */
struct parse_node *new_list(struct parse_node *node);
struct parse_node *new_function(char *name, struct parse_node *args);
struct parse_node *new_legal(struct parse_node *role, struct parse_node *move);
struct parse_node *new_true(struct parse_node *child);
struct parse_node *new_does(struct parse_node *role, struct parse_node *move);
struct parse_node *new_variable(char *name);
struct parse_node *new_role(struct parse_node *role);
struct parse_node *new_role_var(struct parse_node *role);
struct parse_node *new_init(struct parse_node *init);
struct parse_node *new_terminal(void);
struct parse_node *new_goal(char *role, int goal_value);
struct parse_node *new_constant(char *name);
struct parse_node *new_implication(struct parse_node *conc,
	struct parse_node *premises);
struct parse_node *new_next(struct parse_node *child);
struct parse_node *new_not(struct parse_node *child);
struct parse_node *new_or(struct parse_node *children);
struct parse_node *new_distinct(struct parse_node *child_1,
	struct parse_node *child_2);
struct parse_node *add_new_node(enum parse_type type, char *name);
struct parse_node *alloc_node(char *name);
struct parse_node *new_node(enum parse_type type, char *name);
void add_child(struct parse_node *node, struct parse_node *child);
void free_node(struct parse_node *node);
