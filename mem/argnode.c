#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"argnode.h"

ArgNode *argnode_init(char *sname, char *lname, char *help, char *name,
			ArgType type, int req)
{
	ArgNode *anode=calloc(1, sizeof(ArgNode));
	if(anode==NULL) {
		fprintf(stderr, "[-]ArgNode: Error in allocating memory!\n");
		_exit(-1);
	}

	anode->sname=strdup(sname);
	anode->lname=strdup(lname);
	anode->help=strdup(help);
	anode->name=strdup(name);
	if(anode->sname==NULL || anode->lname==NULL || anode->help==NULL ||
		anode->name==NULL) {
		fprintf(stderr, "[-]Argnode: Error in allocating memory!\n");
		_exit(-1);
	}

	anode->type=IntType;

	return anode;
}

void argnode_add_val(Argnode *anode, void *val)
{
	switch(anode->type) {
	case IntType:
		anode->ival=*(int *)val;
		break;
	case FloatType:
		anode->fval=*(float *)val;
		break;
	case StrType:
		anode->sval=strdup((char *)val);
		if(anode->sval==NULL) {
			fprintf(stderr, "[-]Argnode: SVAL: Error in allocating memory!\n");
			_exit(-1);
		}
		break;
	default:
		fprintf(stderr, "[-]Argnode: Unknown type: %d!\n", anode->type);
		_exit(-1);
	}
}

void argnode_add_node(Argnode *start, Argnode *node)
{
	Argnode *curr=start;
	while(curr->nxt!=NULL)
		curr=curr->nxt;
	curr->nxt=node;
}

void argnode_del_list(Argnode *start)
{
	Argnode *curr=start->nxt;
	while(start->nxt!=NULL) {
		start->nxt=curr->nxt;
		argnode_deinit(curr);
		curr=start->nxt;
	}
	argnode_deinit(start);
}

void argnode_deinit(Argnode *anode)
{
	free(anode->sname);
	free(anode->lname);
	free(anode->help);
	free(anode->name);
	if(anode->type==StrType)
		free(anode->sval);
	free(anode);
}
