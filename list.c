/**************/
/*   list.c   */
/**************/


#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST* pList)
{
	if (pList == NULL)
		return False;	// no list to initialize

	pList->head.next = NULL;
	return True;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value)
{
	if (!pNode)
		return NULL;

	NODE* tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode, void(*freeKey)(void*))
{
	NODE* tmp;
	if (!pNode || !(tmp = pNode->next))
		return False;

	pNode->next = tmp->next;
	if (freeKey != NULL)
		freeKey(tmp->key);

	free(tmp);
	return True;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
NODE* L_find(NODE* pNode, DATA Value, int(*compare)(const void*, const void*))
{
	NODE* tmp = NULL;

	while (pNode != NULL)
	{
		if (compare(pNode->key, Value) == 0)
		{
			tmp = pNode;
			break;
		}
		pNode = pNode->next;
	}

	return tmp;
}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
BOOL L_free(LIST* pList, void(*freeKey)(void*))
{
	NODE *tmp;
	BOOL cont = True;
	if (!pList)
		return False;

	tmp = &(pList->head);
	while (cont)
		cont = L_delete(tmp, freeKey);

	return True;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(const LIST* pList, void(*print)(const void*))
{
	NODE	*tmp;
	int		c = 0;

	if (!pList)
		return False;

	printf("\n");
	tmp = pList->head.next;
	while (tmp != NULL)
	{
		print(tmp->key);
		c++;
		tmp = tmp->next;
	}
	printf("\n");
	return c;
}
