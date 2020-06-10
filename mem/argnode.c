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
		fprintf(stderr, "[-]ArgNode: Error in allocating memory!\n");
		_exit(-1);
	}

	anode->req=req;
	anode->type=type;

	return anode;
}

ArgNode *argnode_find(ArgNode *start, char *name)
{
	ArgNode *curr=start, *ret=NULL;
	while(curr!=NULL) {
		if(!strcmp(curr->name, name)) {
			ret=curr;
			break;
		}
		curr=curr->nxt;
	}

	return ret;
}

void argnode_add_val(ArgNode *start, char *name, void *val)
{
	ArgNode *anode=argnode_find(start, name);
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
			fprintf(stderr, "[-]ArgNode: SVAL: Error in allocating memory!\n");
			_exit(-1);
		}
		break;
	case NoneType:
		break;
	default:
		fprintf(stderr, "[-]ArgNode: Unknown type: %d!\n", anode->type);
		_exit(-1);
	}
}

void argnode_add_node(ArgNode *start, ArgNode *node)
{
	ArgNode *curr=start;
	while(curr->nxt!=NULL)
		curr=curr->nxt;
	curr->nxt=node;
}

void argnode_del_list(ArgNode *start)
{
	ArgNode *curr=start->nxt;
	while(start->nxt!=NULL) {
		start->nxt=curr->nxt;
		argnode_deinit(curr);
		curr=start->nxt;
	}
	argnode_deinit(start);
}

void argnode_deinit(ArgNode *anode)
{
	free(anode->sname);
	free(anode->lname);
	free(anode->help);
	free(anode->name);
	if(anode->type==StrType)
		free(anode->sval);
	free(anode);
}
