
#include "linkedlist.h"


void addNode(linkedlist *list,char** element,char *arguments_size,char redirections_num) {
    Node* AddedNode = (Node*) malloc (sizeof(Node));
    AddedNode->next = NULL;
    AddedNode->Data = element;
    AddedNode->num_of_arguments=*arguments_size;
    AddedNode->num_of_redirections=redirections_num;
    //strcpy(AddedNode->Data,element);
    Node* node_ptr = list->head;
	//printf("%s\n",AddedNode->Data);
    if (list->listSize == 0) {
        list->head = AddedNode;
        //printf("head node\n");
    } else {
        while (node_ptr->next != NULL) {
            //printf("node data = %s\n",node_ptr->Data);
            node_ptr = node_ptr->next;
        }
        node_ptr->next = AddedNode;
        /*printf("size = %d , added node address = 0x%x, data = %s , head = %s\n",list->listSize,AddedNode,AddedNode->Data,list->head->Data);
    	printf("node pointer address = %x node pointer data = %s\n",node_ptr,node_ptr->Data);*/
    }
    list->listSize++;
}
int size(linkedlist *list) { 
        return list->listSize;
}
void Print(linkedlist *list) {
	int counter =1;
	char arguments_counter=0;
	Node* node_ptr = list->head;
	//printf("head address = %x\n",list->head);
	//printf("%d. %s\n",counter, node_ptr->Data);
        while (counter<=(list->listSize)) {
                arguments_counter=0;
        	printf("%d. ",counter);
        	while (arguments_counter<(node_ptr->num_of_arguments)){
        		printf("%s ", node_ptr->Data[arguments_counter]);
        		arguments_counter++;
        	}
            	printf("\n");
            node_ptr = node_ptr->next;
            counter++;
        }
}

