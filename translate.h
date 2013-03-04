/*
 * translate.h
 *
 * Structures for translating our syntax into a player.
 *
 * Contains all the data for the translation process. Not much is used now.
 *
 * Created 2009/06/12
 */

#ifndef _TRANSLATE_H_

#define _TRANSLATE_H_

#include "main.h"
#include "parse.h"

/* The prefix for the symbols that we generate (really just a big enum). */
#define SYM_PREFIX "sym_"

/* Translation data */
extern int enum_counter;

/*
 * Prototypes
 */

void translate(void);
void translate_init_files(void);
void translate_finish_files(void);
void translate_roles(void);
void translate_symbols(void);
void translate_defs(void);
void translate_init(void);
void translate_init_elem(struct parse_node *node);
void emit_enum(FILE *ofile, char *prefix, char *name);

#endif /* _TRANSLATE_H_ */
