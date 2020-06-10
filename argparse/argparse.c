#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"argparse.h"

ArgParse *argparse_init()
{
	ArgParse *args=calloc(1, sizeof(ArgParse));
	if(args==NULL) {
		fprintf(stderr, "[-]ArgParse: Error in allocating memory!\n");
		_exit(-1);
	}

	args->args=argnode_init("-h", "--help", "Show help", "help",
				NoneType, 0);
	args->min_argc++;
	return args;
}

void add_argument(ArgParse *args, char *sname, char *lname, char *help,
			char *name, ArgType type, int req, void *def)
{
	ArgNode *node=argnode_init(sname, lname, help, name, type, req);
	argnode_add_node(args->args, node);
	if(type!=NoneType && def!=NULL) {
		argnode_add_val(args->args, name, def);
		node->def=1;
	}
	if(req)
		args->min_argc+=(type==NoneType) ? (1) : (2);
}

void show_help(ArgParse *args)
{
	ArgNode *curr=args->args;
	fprintf(stdout, "Flag, Name\tHelp\tRequired\tDefault\n");
	while(curr!=NULL) {
		fprintf(stdout, "%s ,%s\t%s\t", curr->sname, curr->lname,
			curr->help);
		if(curr->req)
			fprintf(stdout, "Required\t");
		else
			fprintf(stdout, "Optional\t");
		if(curr->type!=NoneType && curr->def) {
			switch(curr->type) {
			case IntType:
				fprintf(stdout, "%d\n", curr->ival);
				break;
			case FloatType:
				fprintf(stdout, "%f\n", curr->fval);
				break;
			case StrType:
				fprintf(stdout, "%s\n", curr->sval);
				break;
			}
		} else {
			fprintf(stdout, "NULL\n");
		}
	}

	clean(args);
}

void clean(ArgParse *args)
{
	argnode_del_list(args->args);
	free(args);
}
