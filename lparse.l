%{

#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "Y.tab.h"

extern int yylex(void);

%}

%%

role		return ROLE;
init		return INIT;
true		return TRUE;
not			return NOT;
distinct	return DISTINCT;
or			return OR;
legal		return LEGAL;
does		return DOES;
next		return NEXT;
terminal	return TERMINAL;
goal		return GOAL;
\<=			return IMPL;

[a-zA-Z0-9_-]+ {
				yylval.u_string = strdup(yytext);
				return TOKEN_T;
			}

[ \t\n]+	; /* whitespace */
;[^\n]*		; /* comments */

.			return (int)yytext[0]; /* literals */

%%
