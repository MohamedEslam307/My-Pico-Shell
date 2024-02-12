
#include "linkedlist.h"


Node *addNode(linkedlist * list, char **element, char *arguments_size,
	      char redirections_num)
{
    Node *AddedNode = (Node *) malloc(sizeof(Node));
    if (NULL != AddedNode) {
	AddedNode->next = NULL;
	AddedNode->Data = element;
	AddedNode->num_of_arguments = *arguments_size;
	AddedNode->num_of_redirections = redirections_num;
	Node *node_ptr = list->head;
	if (list->listSize == 0) {
	    list->head = AddedNode;
	} else {
	    while (node_ptr->next != NULL) {
		node_ptr = node_ptr->next;
	    }
	    node_ptr->next = AddedNode;
	}
	list->listSize++;
    }
    return AddedNode;
}

int size(linkedlist * list)
{
    return list->listSize;
}

void Print(linkedlist * list)
{
    int counter = 1;
    char arguments_counter = 0;
    Node *node_ptr = list->head;
    //printf("head address = %x\n",list->head);
    //printf("%d. %s\n",counter, node_ptr->Data);
    while (counter <= (list->listSize)) {
	arguments_counter = 0;
	printf("%d. ", counter);
	while (arguments_counter < (node_ptr->num_of_arguments)) {
	    printf("%s ", node_ptr->Data[arguments_counter]);
	    arguments_counter++;
	}
	printf("\n");
	node_ptr = node_ptr->next;
	counter++;
    }
}
