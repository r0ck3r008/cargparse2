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
	union
	{
		int ival;
		float fval;
		char *sval;
	};
	struct Argnode *nxt;
} Argnode;

Argnode *argnode_init(char *, char *, char *, char *,
			ArgType);
void argnode_add_val(Argnode *, void *);
void argnode_add_node(Argnode *, Argnode *);
void argnode_del_list(Argnode *);
void argnode_deinit(Argnode *);

#endif
