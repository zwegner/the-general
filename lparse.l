%{
#include <stdio.h>
#include <string.h>
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
terminal	return TERMINAL;
goal		return GOAL;
<=			return RULE;

[a-zA-Z0-9_-]* {
				yylval.u_string = strdup(yytext);
				return ITEM_T;
			}

[ \t\n]+	; /* whitespace */
;[^\n]*		; /* comments */

.			return (int)yytext[0]; /* literals */

%%
