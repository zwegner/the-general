%start toplevel

%%

toplevel
	: toplevel_rule
	| toplevel toplevel_rule
	;

toplevel_rule
	: datalog_rule
	| rule
	;

pre_token
	: ROLE
	| INIT
	| TRUE
	| NOT
	| DISTINCT
	| OR
	| LEGAL
	| DOES
	| TERMINAL
	| GOAL
	| RULE
	;

token
	: pre_token
	| TOKEN_T
	;

variable
	: '?' TOKEN_T
	;

constant
	: token
	;

relation
	: '(' token ')'
	| token
	;

term
	: variable
	| constant
	| function
	;

vocab
	: term
	| relation
	;

atomic
	: '(' term rel_args ')'
	;

rel_args
	: term
	| rel_args term
	;

literal
	: atomic
	| not atomic
	;

datalog_rule
	: '(' RULE atomic datalog_args ')'
	;

datalog_args
	: literal
	| datalog_args literal
	;
