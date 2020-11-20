#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include "LinkList.h"

int list_insert(PHEAD_LISTNODE list_head, void* data_node)
{
	PLISTNODE temp;
	temp = &list_head->Node;

	while(temp->pNext != NULL) {
		temp = temp->pNext;
	}
	temp->pNext = (PLISTNODE)malloc(sizeof(struct ListNode));
	if(!(temp->pNext)) {
		printf("malloc err!\n");
		return -1;
	}
	temp->pNext->data = data_node;
	temp->pNext->pNext = NULL;
	list_head->count++;
	return 0;
}

void* list_delete(PHEAD_LISTNODE list_head, int (*cmp_func)(void *, void *), void *cmp_data)
{
	PLISTNODE temp;
	PLISTNODE t = NULL;
	void *data = NULL;
	temp = &list_head->Node;

	while(temp->pNext != NULL) {
		if(!cmp_func(temp->pNext->data, cmp_data)) {
			t = temp->pNext;
			temp->pNext = t->pNext;
			break;
		}
		temp = temp->pNext;
	}
	
	if (t != NULL){
		data = t->data; 
		free(t);
	}
	else {
		printf("no data to delete\n");
		return NULL;
	}
	list_head->count--;
	return data;
}

int list_clear(PHEAD_LISTNODE list_head, int (*del_data)(void *))
{
	PLISTNODE temp;
	PLISTNODE t = NULL;
    //void *data = NULL;
	temp = &list_head->Node;

	while(temp->pNext != NULL) {
		t = temp->pNext;
		temp->pNext = t->pNext;
		
		if (del_data != NULL) {
			del_data(t->data);
		}
		free(t);
	}
	list_head->count = 0;
	
	return 0;
}

void* list_find(PHEAD_LISTNODE list_head, int (*cmp_func)(void *, void *), void *cmp_data)
{
	PLISTNODE temp;
	temp = &list_head->Node;
	
	while(temp->pNext != NULL) {
		if(!cmp_func(temp->pNext->data, cmp_data)) {
			return temp->pNext->data;
		}
		temp = temp->pNext;
	}

	printf("find no data\n");
	return NULL;
}

int list_num(PHEAD_LISTNODE list_head)
{
	return list_head->count;
}

int list_print(PHEAD_LISTNODE list_head, int (*print_func)(void *))
{
	PLISTNODE temp;
	temp = &list_head->Node;

	while(temp->pNext != NULL) {
		print_func(temp->pNext->data);
		temp = temp->pNext;
	}

	return 0;
}
