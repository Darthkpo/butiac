#include "list.h"

node* nnew(void *val) {

	node *node = malloc(sizeof(node));
	node->value = val;
	node->next = NULL;
	return node;

}

void nfree(node *node) {
	
	if(node->value)
		free(node->value);
	if(node)
		free(node); //:D
	
}

list* lnew(void) {
	
	list *list = malloc(sizeof(list));
	list->head = NULL;
	list->size = 0;
	return list;
	
}

void lfree (list *list) {
	
	if(!list)
		return;
	node *iter = list->head;
	while(iter != NULL) {
		list->head = list->head->next;
		nfree(iter);
		iter= list->head;
	}
	free(list);
	
}

void ladd(list *list, void *val) {
	
	node *link = nnew(val);
	if(list->head == NULL) {
		list->head = link;
	} else {
		
		node *iter = list->head;
		while(iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = link;
		
	}
	list->size++;
	
}

node* ldelf(list *list) {
	
	node *tmp = list->head;
	list->head = list->head->next;
	if(tmp != NULL) 
		list->size--;
	return tmp;
	
}

node* ldell(list *list) {

	node *tmp = list->head;
	node *prev_tmp = list->head;
	for (int i = 0; i < list->size - 1; i++) {
		if(i < list->size - 2)
			prev_tmp = prev_tmp->next;
		tmp = tmp->next;
	}
	prev_tmp->next = NULL;
	return tmp;
	
}

ssize_t lhas(list *list, void *val) {
	
	ssize_t result = -1;
	node *iter = list->head;
	for(int i = 0; i < list->size; i++){
		if(iter->value == val) {
			result = i;
			break;
		}
		iter = iter->next;
	}
	return result;
	
}

node* lgetat(list *list, size_t index) {
	
	if(index > list->size - 1)
		return NULL;
	if(index == 0)
		return list->head;
	node *iter = list->head;
	for(int i = 0; i < index; i++){
		iter = iter->next;
	}
	return iter;
	
}
