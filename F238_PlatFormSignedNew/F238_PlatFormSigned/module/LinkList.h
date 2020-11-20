#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ListNode
{
	void *data;
	struct ListNode *pNext;
}LISTNODE,*PLISTNODE;

typedef struct HeadListNode
{
	struct ListNode  Node;
	int              count;
}HEAD_LISTNODE,*PHEAD_LISTNODE;


int list_insert(PHEAD_LISTNODE list_head, void* data_node);
void* list_delete(PHEAD_LISTNODE list_head, int (*cmp_func)(void *, void *), void *cmp_data);
int list_clear(PHEAD_LISTNODE list_head, int (*del_data)(void *));
void* list_find(PHEAD_LISTNODE list_head, int (*cmp_func)(void *, void *), void *cmp_data);
int list_num(PHEAD_LISTNODE list_head);
int list_print(PHEAD_LISTNODE list_head, int (*print_func)(void *));

#ifdef __cplusplus
}   
#endif

#endif  /* ndef __LINK_LIST_H__ */
