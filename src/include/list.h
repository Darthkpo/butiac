#ifndef _BUTIAC_LIST_H_
#define _BUTIAC_LIST_H_

#include <stdlib.h>

struct node {
	
	void *value;
	struct node *next;
	
} typedef node;

node* nnew(void *val);
void nfree(node *nptr, int freevalue);

struct list {
	
	node *head;
	size_t size;
	
} typedef list;

//List init
list* lnew(void);
//List free, frees all nodes
void lfree(list *list, int freevaluess);
//Add val to end of list
void ladd(list *list, void *val);
//Delete last item
node* ldell(list *list);
//Delete first item
node* ldelf(list *list);
//Check if list has item, return index if it has or -1 if not
ssize_t lhas(list *list, void *val);
//Get item at index
node* lgetat(list *list, size_t index);

#endif
