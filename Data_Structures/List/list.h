#ifndef LIST_H_
#define LIST_H_


/*Single Linked List Node Definition*/
typedef struct Node
{
	void *infoPtr;
	struct Node *linkPtr;
}
ST_node_t;

/*Functions' Prototypes*/
/*A function to reserve a linked list with Size elements and return the first element Adress*/
ST_node_t *createLinkedList(uint32_t size);
// /*A function to display a linked list*/
void displayLinkedList(ST_node_t *startAddress);
// /*A function to scan a linked list*/
// void scanLinkedList(Node_t *StartAddress);
// /*A function to count a linked list elements*/
// int countLinkedListNodes(Node_t *StartAdress);
// /*A function to search a number through a linked list*/
// int searchLinkedList(Node_t *StartAdress, int SearchNumber);
// /*A function to insert an element at the beginning of a linked list and return the linked list adress after isertion*/
// Node_t *insertAtBeginning(Node_t *StartAdress, int InsertionNumber);
/*A function to insert an element at the end of a linked list*/
ST_node_t *insertAtEnd(ST_node_t *startAddress, void *insertionMember);
// /*A function to insert a node after a node*/
// void insertAfterNode(Node_t *StartAddress, int NodeValue, int InsertionNumber);
// /*A function to insert a node before a node*/
// Node_t *insertBeforeNode(Node_t *StartAddress, int NodeValue, int InsertionNumber);
// /*A function to insert a node at a given position*/
// Node_t *insertAtPosition(Node_t *StartAddress, int NodeIndex, int InsertionNumber);
// /*A function to delete an element from a linked list*/
// Node_t *deleteFromLinkedList(Node_t *StartAddress, int DeletedElement);
// /*A function to reverse a linked list*/
// Node_t *reverseLinkedList(Node_t *StartAddress);
// /*A function to reverse a linked list (Bad Implementation)*/
// Node_t *reverseLinkedList1(Node_t *StartAddress);

#endif