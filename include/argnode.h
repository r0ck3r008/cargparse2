#ifndef ARGNODE_H
#define ARGNODE_H

typedef enum
{
	IntType,
	FloatType,
	StrType
} ArgType;

typedef struct Argnode
{
	char *sname, *lname, *help, *name;
	ArgType type;
	int on, req, def;
	union
	{
		int ival;
		float fval;
		char *sval;
	};
	struct Argnode *nxt;
} Argnode;

void argnode_add_val(Argnode *, void *);
void argnode_add_node(Argnode *, Argnode *);
void argnode_del_list(Argnode *);
void argnode_deinit(Argnode *);
ArgNode *argnode_init(char *, char *, char *, char *,
			ArgType, int);
ArgNode *argnode_find(ArgNode *, char *);
void argnode_add_val(ArgNode *, char *, void *);
void argnode_add_node(ArgNode *, ArgNode *);
void argnode_del_list(ArgNode *);
void argnode_deinit(ArgNode *);

#endif
