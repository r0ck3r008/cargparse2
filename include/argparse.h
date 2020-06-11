#ifndef ARGPARSE_H
#define ARGPARSE_H

#include"argtype.h"
#include"argnode.h"

typedef struct
{
	ArgNode *args;
	int min_argc;
} ArgParse;

ArgParse *argparse_init();
void add_argument(ArgParse *, char *, char *, char *,
			char *, ArgType, int, void *);
void parse_args(ArgParse *, int, char **);
int argparse_get_int(ArgParse *, char *);
float argparse_get_float(ArgParse *, char *);
char *argparse_get_char(ArgParse *, char *);
void show_help(ArgParse *);
void clean(ArgParse *);

#endif
