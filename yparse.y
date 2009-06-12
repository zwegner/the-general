%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

#define YYDEBUG 1

extern FILE *yyin;
extern void yyerror(const char *str);
extern int yywrap(void);
extern int yylex(void);
extern int yyparse(void);

%}

%union
{
	char *u_string;
	long u_long;
	struct parse_node *u_node;
}

%token ROLE;
%token INIT;
%token TRUE;
%token NOT;
%token DISTINCT;
%token OR;
%token LEGAL;
%token DOES;
%token NEXT;
%token TERMINAL;
%token GOAL;
%token IMPL;

%token <u_string>TOKEN_T;

%type <u_node> toplevel_list;
%type <u_node> toplevel_rule;
%type <u_node> toplevel_rel;

%type <u_node> rel_legal;
%type <u_node> rel_role;
%type <u_node> rel_init;
%type <u_node> rel_true;
%type <u_node> rel_does;
%type <u_node> rel_next;
%type <u_node> rel_not;
%type <u_node> rel_or;
%type <u_node> rel_distinct;
%type <u_node> rel_role_var;
%type <u_node> rel_terminal;
%type <u_node> rel_goal;
%type <u_node> rel_other;

%type <u_node> term;
%type <u_node> term_list;
%type <u_node> atom;
%type <u_node> constant;
%type <u_node> variable;
%type <u_node> function;
%type <u_node> function_args;

%type <u_node> implication;
%type <u_node> impl_conc;
%type <u_node> impl_premise;
%type <u_node> impl_prem_list;

%start toplevel;

%%

toplevel
	: toplevel_list {
		root_node = $1;
	}
	;
/* Top level: our GDL file just consists of a bunch of rules. */
toplevel_list
	: toplevel_rule {
		//printf("toplevel rule, new list\n");
		$$ = new_list($1);
	}
	| toplevel_list toplevel_rule {
		add_child($1, $2);
		$$ = $1;
	}
	;

toplevel_rule
	: toplevel_rel
	| implication
	;

/* RELATIONS: These are constant relations at the top level of the parse tree.*/
toplevel_rel
	: rel_role
	| rel_init
	| rel_legal
	| rel_other
	;

/* Role relation: top level, only one argument, generic token */
rel_role
	: '(' ROLE constant ')' {
		$$ = new_role($3);
	}
	;

/* Init relation: top level, one term argument */
rel_init
	: '(' INIT term ')' {
		$$ = new_init($3);
	}
	;

/* Other relation: This is game-specific, it is defined in the GDL file.
	An example would be (successor 1 2) */
rel_other
	: TOKEN_T {
		$$ = new_constant($1);
	}
	| '(' TOKEN_T term_list ')' {
		$$ = new_function($2, $3);
	}
	;

/*
 * IMPLICATIONS: these are conditional relations, only top level.
 */
implication
	: '(' IMPL impl_conc impl_prem_list ')' {
		$$ = new_implication($3, $4);
	}
	;

/* Implication conclusion (head) */
impl_conc
	: rel_next
	| rel_legal
	| rel_terminal
	| rel_goal
	| rel_other
	;

/* Implication premises (body) */
impl_prem_list
	: impl_premise {
		$$ = new_list($1);
	}
	| impl_prem_list impl_premise {
		add_child($1, $2);
		$$ = $1;
	}
	;

impl_premise
	: rel_true
	| rel_not
	| rel_distinct
	| rel_or
	| rel_does
	| rel_role_var
	| rel_legal
	| rel_other
	;

/*
 * Implication Conclusions
 */

/* Next: a relation is true in the next game state. */
rel_next
	: '(' NEXT rel_other ')' {
		$$ = new_next($3);
	}
	;

/* Legal: a certain move is legal of the given player to make. */
rel_legal
	: '(' LEGAL atom rel_other ')' {
		$$ = new_legal($3, $4);
	}
	;

/* Terminal: the game state has no successors; the game is over. */
rel_terminal
	: TERMINAL {
		$$ = new_terminal();
	}
	;

/* Goal: The given player gets the given number of points for the game. Only
	in terminal positions. */
rel_goal
	: '(' GOAL TOKEN_T TOKEN_T ')' {
		$$ = new_goal($3, atoi($4));
	}
	;

/*
 * Implication Premises
 */

rel_true
	: '(' TRUE term ')' {
		$$ = new_true($3);
	}
	;

rel_not
	: '(' NOT term ')' {
		$$ = new_not($3);
	}
	;

rel_or
	: '(' OR term_list ')' {
		$$ = new_or($3);
	}
	;

rel_distinct
	: '(' DISTINCT term term ')' {
		$$ = new_distinct($3, $4);
	}
	;

rel_does
	: '(' DOES atom term ')' {
		$$ = new_does($3, $4);
	}
	;

/* Separate relation for roles. This isn't a toplevel rule, but rather a
	premise. Thus, it must have a variable. */
rel_role_var
	: '(' ROLE variable ')' {
		$$ = new_role_var($3);
	}
	;

/*
 * Misc. syntax stuff
 */

/* Variable: this can appear only in implications. */
variable
	: '?' TOKEN_T {
		$$ = new_variable($2);
	}
	;

constant
	: TOKEN_T {
		$$ = new_constant($1);
	}
	;

function
	: '(' TOKEN_T function_args ')' {
		$$ = new_function($2, $3);
	}
	| rel_distinct
	| rel_true
	| rel_role_var
	| rel_legal
	;

function_args
	: term
	| function_args term
	;

atom
	: variable
	| constant
	;

term
	: atom
	| function
	;

term_list
	: term {
		$$ = new_list($1);
	}
	| term_list term {
		add_child($1, $2);
		$$ = $1;
	}
	;
