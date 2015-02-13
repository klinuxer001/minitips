#include "common.h"
#include "slist.h"

int assign_node(slist *node, char *buf, int len)
{
	node->context = (char *)malloc(BUF_LEN);
	assert(node->context != NULL);
	memcpy(node->context, buf, len);
	return SUCCESS;
}

__inline void add_to_list(slist *node, slist *shead)
{
	assert((node!=NULL) && (shead!=NULL));
	shead->next = node;
	node->next = NULL;
	pos = node;
}


__inline void del_from_list(slist *node, slist *shead)
{
	assert((node!=NULL) && (shead!=NULL));
	shead->next = node->next;
	free(node->context);
}

__inline void del_list_head(slist *node)
{
	head = node->next;
	free(node->context);
	free(node);
}

