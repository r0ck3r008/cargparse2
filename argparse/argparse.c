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
		argnode_add_val(args->args, sname, def);
		node->def=1;
	}
	if(req)
		args->min_argc+=(type==NoneType) ? (1) : (2);
}

void parse_args(ArgParse *args, int argc, char **argv)
{
	if(argc-1<args->min_argc) {
		show_help(args);
		return;
	}

	for(int i=1; i<argc; i++) {
		ArgNode *curr=argnode_find(args->args, argv[i]);
		if(curr==NULL) {
			show_help(args);
			break;
		}

		void *val=NULL; float fval; int ival;
		if(curr->type!=NoneType) {
			switch(curr->type) {
			case IntType:
				ival=strtol(argv[++i], NULL, 10);
				val=&ival;
				break;
			case FloatType:
				fval=strtof(argv[++i], NULL);
				val=&fval;
				break;
			case StrType:
				val=argv[++i];
				break;
			default:
				show_help(args);
			}
			argnode_add_val(curr, NULL, val);
		}
		curr->on=1;
	}
}

int argparse_get_int(ArgParse *args, char *name)
{
	ArgNode *curr=argnode_find(args->args, name);
	if(curr==NULL) {
		show_help(args);
		return 0;
	}

	if(curr->type==IntType)
		return curr->ival;
	else if(curr->type==NoneType)
		return ((curr->on) ? (1) : (0));

	return 0;
}

float argparse_get_float(ArgParse *args, char *name)
{
	ArgNode *curr=argnode_find(args->args, name);
	if(curr==NULL) {
		show_help(args);
		return 0;
	}

	if(curr->type==FloatType)
		return curr->fval;

	return 0.0;
}

char *argparse_get_char(ArgParse *args, char *name)
{
	ArgNode *curr=argnode_find(args->args, name);
	if(curr==NULL) {
		show_help(args);
		return 0;
	}

	if(curr->type==StrType)
		return curr->sval;

	return NULL;
}

void show_help(ArgParse *args)
{
	ArgNode *curr=args->args;
	fprintf(stdout, "Flag, Name\t\tHelp\t\tRequired\t\tDefault\n");
	while(curr!=NULL) {
		fprintf(stdout, "%s ,%s\t\t%s\t\t", curr->sname, curr->lname,
			curr->help);
		if(curr->req)
			fprintf(stdout, "Required\t\t");
		else
			fprintf(stdout, "Optional\t\t");
		if(curr->def) {
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
			case NoneType:
				fprintf(stdout, "NULL\n");
			}
		} else {
			fprintf(stdout, "NULL\n");
		}
		curr=curr->nxt;
	}

	clean(args);
	_exit(-1);
}

void clean(ArgParse *args)
{
	argnode_del_list(args->args);
	free(args);
}
