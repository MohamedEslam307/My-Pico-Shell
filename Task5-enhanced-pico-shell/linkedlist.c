
#include "linkedlist.h"

void destroyList(linkedlist * list)
{
    Node *current = list->head;
    while (current->next != NULL) {
	Node *next = current->next;
	free(current);
	current = next;
    }
    free(current);
    current = NULL;
    //list->head->num_of_arguments = 0;
    //list->head->num_of_redirections = 0;
}

Node *addNode(linkedlist * list, char **element, char arguments_size)
{
    Node *AddedNode = (Node *) malloc(sizeof(Node));
    if (NULL != AddedNode) {
	AddedNode->next = NULL;
	AddedNode->Data = element;
	AddedNode->num_of_arguments = arguments_size;
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
	while (arguments_counter < (node_ptr->num_of_arguments)+(node_ptr->num_of_redirections)*2) {
	    printf("%s ", node_ptr->Data[arguments_counter]);
	    arguments_counter++;
	}
	printf("\n");
	node_ptr = node_ptr->next;
	counter++;
    }
}
