/************************************************************************

������

FUNCTIONS :
ListCreate   - ����һ���µ�������
ListInsertAt  - ����ڵ㵽������
ListPushFront  - ������ͷ������ڵ㡣
ListPushBack  - ������β������ڵ㡣
ListPopFront  - ɾ������ͷ���ڵ㡣
ListPopBack   - ɾ������β���ڵ㡣
ListGetFront  - ��õ�һ���ڵ�
ListGetBack   - ������һ���ڵ㡣
ListGetNodeAt  - ������Ż�ýڵ㡣
ListDeleteNodeAt - �������ɾ���ڵ㡣
ListDestroy   - ɾ���������������ͷ��ڴ档
ListCleaer   - ��������е����нڵ�����ݡ�
ListGetError  - ��ô�����
ListGetSize   - ��õ�ǰ������С���ڵ���������


************************************************************************/
#include <stdlib.h> // ʹ�õ���malloc(), free()�Ⱥ�����
#include "LinkList.h"

//-- ���ָ���Ƿ�Ϊ0
#define CHECK_POINTER( ppNode ) \
  if( ppNode == 0L ) {  \
  return( pList->ListError = LIST_ERROR_DEREFERENCE_NULL ); \
        }

PNODE NodeCreate(void* data)
{
	PNODE pnode = (PNODE) malloc(sizeof(NODE));
	pnode->data = data; 
	pnode->next = 0;
	return pnode;
}

void NodeDestory(PNODE node)
{
	free(node->data);
	free(node);
}

int ListSize(PLIST list)
{
	int  cnt;
	PNODE node = list->first;

	cnt = 0;
	while (node)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}


void* ListDeleteAt(PLIST list, int n)
{
	int  i;
	PNODE tmp;
	PNODE prev;

	tmp = list->first;
	if (n < 1)
		return (NULL);
	if (n == 0)
	{
		return ListPopFront(list);
	}
	i = 1;
	while (i < n)
	{
		prev = tmp;
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
		++i;
	}
	prev->next = tmp->next;
	return (tmp->data);
}


void* ListGetAt(PLIST list, unsigned int n)
{
	unsigned int   i;
	PNODE node = list->first;

	if (!node)
		return (NULL);
	
	for (i = 1; i <= n; i++)
	{
		node = node->next;
		if (!node)
			return (NULL);
	}
	return (node->data);
}

PLIST ListCreate(void* list_data)
{
	PLIST new_list;

	new_list = NULL;
	new_list = (PLIST)malloc(sizeof(LIST));
	if (new_list != NULL)
	{
		new_list->list_data = list_data;
		new_list->first = NULL;
	}
	return (new_list);
}

void ListDestory(PLIST list)
{
	if (list != NULL)
	{
		ListClear(list);
		free(list);
	}
}

void* ListPopFront(PLIST list)
{
	PNODE tmp;
	void*  data = NULL;
	if (list != NULL)
	{
		if (list->first != NULL)
		{
			tmp = list->first;
			data = tmp->data;
			list->first = tmp->next;
			free(tmp);
		}
	}
	return (data);
}


void* ListPopBack(PLIST list)
{
	PNODE previous;
	PNODE current;
	PNODE node = list->first;
	void* data;

	if (!node)
		return (NULL);
	if (!(node)->next)
	{
		data = (node)->data;
		free(node);
		node = NULL;
		return (data);
	}
	previous = node;
	current = (node)->next;
	while (current->next)
	{
		previous = current;
		current = current->next;
	}
	data = current->data;
	free(current);
	previous->next = NULL;
	return (data);
}


void ListPushBack(PLIST list, void* data)
{
	PNODE tmp;
	PNODE new_node = NodeCreate(data);

	if (new_node)
	{
		if (list)
		{
			if (list->first)
			{
				tmp = list->first;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_node;
			}
			else
				list->first = new_node;
		}
	}
}


void ListPushFront(PLIST list, void* data)
{
	PNODE new_node;

	if (list != NULL)
	{
		new_node = NodeCreate(data);
		if (new_node != NULL)
		{
			new_node->next = list->first;
			list->first = new_node;
		}
	}
}



void ListClear(PLIST list)
{
	PNODE tmp;
	PNODE node;

	if (list != NULL)
	{
		node = list->first;
		while (node)
		{
			tmp = node->next;
			NodeDestory(node);
			node = tmp;
		}
		list->first = 0;
	}
}

