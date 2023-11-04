#include "../../Libraries/STD_TYPES.h"

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

/*Functions' Implementation*/
ST_node_t *createLinkedList(uint32_t size)
{
	/*Defining variables*/
	uint32_t _counter;
	ST_node_t *_startAddress = NULL, *_tempPtr = NULL, *_NewElement = NULL;
	
	/*Validating the size*/
	if(size < 1)
	{
		/*Don't complete the function*/
		return _startAddress;
	}
	
	/*Reserving the first node in the linked list, then assigning its link to NULL*/
	_startAddress = (ST_node_t *) malloc(sizeof(ST_node_t));
	_startAddress -> linkPtr = NULL;
	
	/*Assigning TempPtr to the StartAddress, then working with TempPtr so we don't miss the StartAddress*/
	_tempPtr = _startAddress;
	
	for(_counter = 1; _counter < size; _counter++)
	{
		/*Reserving a new node element, then assigning its link to NULL*/
		_NewElement = (ST_node_t *) malloc(sizeof(ST_node_t));
		_NewElement -> linkPtr = NULL;
		
		/*Making the previous element point to the new element*/
		_tempPtr -> linkPtr = _NewElement;
		
		/*Moving the TempPtr to the last element on the linked list*/
		_tempPtr = _NewElement;
	}
	
	return _startAddress;
}

ST_node_t *insertAtEnd(ST_node_t *startAddress, void *insertionMember)
{
	/*Defining Variables*/
	ST_node_t *_tempPtr = startAddress;
	
	/*Reserving a new node*/
	ST_node_t *_newElement = malloc(sizeof(ST_node_t));
	
	/*Intializing its Info value to the InsertionNumber, and its Link to NULL*/
	_newElement -> infoPtr = insertionMember;
	_newElement -> linkPtr = NULL; 
	
	/*Looping over the linked list elements to reach the last element*/
	if(startAddress == NULL)
	{
		return _newElement;
	}
	else
	{
		while(_tempPtr -> linkPtr != NULL)
		{
			/*Moving the TempPtr to the next element of the linked list*/
			_tempPtr = _tempPtr -> linkPtr;
		}
		/*Expanding the linked list by changing the Link of the last element to the new element*/
		_tempPtr -> linkPtr = _newElement;		
	}
	
	/*Return start address*/
	return startAddress;
}

void displayLinkedList(ST_node_t *startAddress)
{
	/*Defining variables*/
	ST_node_t *_tempPtr = startAddress;
	
	/*Validating the linked list start adress*/
	if(startAddress == NULL)
	{
		printf("The linked list is empty!\n");
	}
	else
	{
		/*Printing a message to the user*/
		printf("The linked list members are: ");
		
		/*Looping over the linked list elements*/
		while(_tempPtr != NULL)
		{
			/*Printing the info of the element*/
			printf("%p\t", _tempPtr -> infoPtr);
		
			/*Moving the TempPtr to the next element of the linked list*/
			_tempPtr = _tempPtr -> linkPtr;
		}
		
		/*Printing a new line*/
		printf("\n");
	}
}

// void scanLinkedList(Node_t *StartAddress)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAddress;
// 	int i = 1;
	
// 	/*Validating the linked list start adress*/
// 	if(StartAddress == NULL)
// 	{
// 		return;
// 	}

// 	/*Looping over the linked list elements*/
// 	while(TempPtr != NULL)
// 	{
// 		/*Scanning the elment value from the user*/
// 		printf("Please enter element %d of the linked list: ", i);
// 		scanf("%d", &TempPtr->infoPtr);
		
// 		/*Moving the TempPtr to the next element of the linked list*/
// 		TempPtr = TempPtr -> linkPtr;
		
// 		/*Incrementing the iterator*/
// 		i++;
// 	}

// }

// Node_t *insertBeforeNode(Node_t *StartAddress, int NodeValue, int InsertionNumber)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAddress, *NewElement = NULL;
// 	int IfFirst;

// 	/*Validating the linked list adress*/
// 	if(StartAddress == NULL)
// 	{
// 		return StartAddress;
// 	}
	
// 	/*Searching for the node through the linked list, and discovering if the node is the first element or not*/
// 	while(TempPtr != NULL)
// 	{
// 		if(TempPtr -> infoPtr == NodeValue)
// 		{
// 			IfFirst = 1;
// 			break;
// 		}
// 		else if((TempPtr -> linkPtr != NULL) && (TempPtr -> linkPtr -> infoPtr == NodeValue))
// 		{
// 			IfFirst = 0;
// 			break;
// 		}
// 		else
// 		{
// 			TempPtr = TempPtr -> linkPtr;
// 		}
// 	}
	
// 	/*Descovering why we breaked the loop and knowing if is the node is the first element or not*/
// 	if(TempPtr == NULL)
// 	{
// 		printf("Does not exist");
// 		return StartAddress;
// 	}
// 	else if(IfFirst == 1)
// 	{
// 		/*Reserving new node and iserting it through the linked list*/
// 		NewElement = (Node_t *) malloc(sizeof(Node_t));
// 		NewElement -> infoPtr = InsertionNumber;
// 		StartAddress = NewElement;
// 		NewElement -> linkPtr = TempPtr;
// 		return StartAddress;
// 	}
// 	else
// 	{
// 		/*Reserving new node and iserting it through the linked list*/
// 		NewElement = (Node_t *) malloc(sizeof(Node_t));
// 		NewElement -> infoPtr = InsertionNumber;
// 		NewElement -> linkPtr = TempPtr -> linkPtr;
// 		TempPtr -> linkPtr = NewElement;
// 	}
	
// 	/*Returning the new start adress*/
// 	return StartAddress;
// }

// void insertAfterNode(Node_t *StartAddress, int NodeValue, int InsertionNumber)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAddress, *NewElement = NULL;

// 	/*Validating the linked list adress*/
// 	if(StartAddress == NULL)
// 	{
// 		return;
// 	}
	
// 	/*Searching for the node through the linked list*/
// 	while(TempPtr != NULL)
// 	{
// 		if(TempPtr -> infoPtr == NodeValue)
// 		{
// 			break;
// 		}
// 		else
// 		{
// 			TempPtr = TempPtr -> linkPtr;
// 		}
// 	}
	
// 	/*Descovering why we breaked the loop*/
// 	if(TempPtr == NULL)
// 	{
// 		/*The linked list is empty*/
// 		return;
// 	}
// 	else 
// 	{
// 		/*Reserving new node and inserting it through the linked list*/
// 		NewElement = (Node_t *) malloc(sizeof(Node_t));
// 		NewElement -> infoPtr = InsertionNumber;
// 		NewElement -> linkPtr = TempPtr -> linkPtr;
// 		TempPtr -> linkPtr = NewElement;
// 	}
// }

// Node_t *insertAtPosition(Node_t *StartAddress, int NodeIndex, int InsertionNumber)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAddress, *NewElement = NULL;
// 	int i, IfFirst;

// 	/*Validating the linked list adress*/
// 	if(StartAddress == NULL)
// 	{
// 		return StartAddress;
// 	}
	
// 	/*Validating the node index*/
// 	if(NodeIndex < 1)
// 	{
// 		return StartAddress;
// 	}
// 	/*Descovering if it is the first node or not*/
// 	else if(NodeIndex == 1)
// 	{
// 		IfFirst = 1;
// 	}
// 	else 
// 	{
// 		IfFirst = 0;
// 	}
	
// 	/*Moving to the previous node to the node on the linked list*/
// 	for(i = 1; i < (NodeIndex - 1); i++)
// 	{
// 		if(TempPtr == NULL)
// 		{
// 			/*The node does not exist*/
// 			return StartAddress;
// 		}
		
// 		/*Moving the pointer to the next element*/
// 		TempPtr = TempPtr -> linkPtr;
// 	}
	
// 	/*Reserving new node and inserting it through the linked list*/
// 	NewElement = (Node_t *) malloc(sizeof(Node_t));
// 	NewElement -> infoPtr = InsertionNumber;
	
// 	if(IfFirst == 1)
// 	{
// 		NewElement -> linkPtr = TempPtr;
// 		StartAddress = NewElement;
// 	}
// 	else
// 	{
// 		NewElement -> linkPtr = TempPtr -> linkPtr;
// 		TempPtr -> linkPtr = NewElement;		
// 	}
	
// 	/*Returning the Start Adress*/
// 	return StartAddress;
// }

// Node_t *deleteFromLinkedList(Node_t *StartAddress, int DeletedElement)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAddress, *DeletedNode = NULL;
	
// 	/*Validating StartAddress*/
// 	if(TempPtr == NULL)
// 	{
// 		/*The linked list is empty*/
// 	}
	
// 	/*If the node is the first element or the linked list has one element*/
// 	else if(TempPtr -> infoPtr == DeletedElement)
// 	{
// 		StartAddress = TempPtr -> linkPtr;
// 		free(TempPtr);
// 	}
	
// 	else
// 	{
// 		/*Moving the pointer to the previous element to the element we want to delete*/
// 		while(TempPtr -> linkPtr != NULL)
// 		{
// 			if(TempPtr -> linkPtr -> infoPtr == DeletedElement)
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				TempPtr = TempPtr -> linkPtr;
// 			}
// 		}
		
// 		/*Discovering why the loop breaked*/
// 		if(TempPtr -> linkPtr == NULL)
// 		{
// 			/*Element Not found*/
// 		}
// 		else 
// 		{
// 			/*Moving the pointer from the previous element to the next element, then delete the element itself*/
// 			DeletedNode = TempPtr -> linkPtr;
// 			TempPtr -> linkPtr = DeletedNode -> linkPtr;
// 			free(DeletedNode);	
// 		}
// 	}
		
// 	return StartAddress;
// }


// Node_t *reverseLinkedList1(Node_t *StartAddress)
// {
// 	Node_t *TempPtr = StartAddress, *Ptr = StartAddress, *StartTemp = StartAddress;
	
// 	/*Validating the start address*/
// 	if(StartAddress == NULL)
// 	{
// 		/*Don't do any thing*/
// 	}
	
// 	else
// 	{
// 		while(TempPtr -> linkPtr != NULL)
// 		{
// 			TempPtr = TempPtr -> linkPtr;
// 		}
	
// 		StartAddress = TempPtr;
	
// 		while(TempPtr != StartTemp)
// 		{
// 			while(Ptr -> linkPtr != TempPtr)
// 			{
// 				Ptr = Ptr -> linkPtr;
// 			}
		
// 			TempPtr -> linkPtr = Ptr;
// 			TempPtr = TempPtr -> linkPtr;
// 			Ptr = StartTemp;
// 		}
	
// 		TempPtr -> linkPtr = NULL;
// 	}
	
// 	return StartAddress;
// }

// Node_t *reverseLinkedList(Node_t *StartAddress)
// {
// 	Node_t *Previous = NULL, *Actuall = StartAddress, *Next = StartAddress;
	
// 	/*Validating the start address*/
// 	if(StartAddress == NULL)
// 	{
// 		/*Don't do any thing*/
// 	}
	
// 	else
// 	{
// 		while(Next != NULL)
// 		{
// 			/*Moving Next to the next element*/
// 			Next = Next -> linkPtr;

// 			/*Making Actuall Point to the previous*/
// 			Actuall -> linkPtr = Previous;
			
// 			/*Moving Actuall and Previous to the next element*/
// 			Previous = Actuall;
// 			Actuall = Next;
// 		}
		
// 		/*Moving StartAddress to the last element of the linked list*/
// 		StartAddress = Previous;
// 	}
	
// 	return StartAddress;
// }

// int countLinkedListNodes(Node_t *StartAdress)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAdress; 
// 	int LinkedListSize = 0;
	
// 	/*Looping over the linked list elements*/
// 	while(TempPtr != NULL)
// 	{
// 		/*Incrementing the iterator*/
// 		LinkedListSize++; 
		
// 		/*Moving the TempPtr to the next element of the linked list*/
// 		TempPtr = TempPtr -> linkPtr;
// 	}
	
// 	/*Returning the length of the linked list*/
// 	return LinkedListSize;
// }

// int searchLinkedList(Node_t *StartAdress, int SearchNumber)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAdress; 
// 	int Position = 1;
	
// 	/*Validating the linked list start adress*/
// 	if(StartAdress == NULL)
// 	{
// 		/*If the linked list is empty return -2 to the user as a flag*/
// 		Position = -2;
// 	}
// 	else
// 	{
// 		/*Looping over the linked list elements*/
// 		while(TempPtr != NULL)
// 		{
// 			/*If the the first element contain the search number break*/
// 			if(TempPtr -> infoPtr == SearchNumber)
// 			{	
// 				break;
// 			}
// 			/*Else increment the iterator and move TempPtr to the next element*/
// 			else
// 			{
// 				Position++;
// 				TempPtr = TempPtr -> linkPtr;
// 			}
// 		}
	
// 		/*discovering why we break the loop*/
// 		if(TempPtr == NULL)
// 		{
// 			/*If the Number does not exist return -1 to the user as a flag*/
// 			Position = -1;
// 		}
// 	}
	
// 	/*Returning the SearchNumber index*/
// 	return Position;
// }

// Node_t *insertAtBeginning(Node_t *StartAdress, int InsertionNumber)
// {
// 	/*Reserving a new node*/
// 	Node_t *NewElement = malloc(sizeof(Node_t));
	
// 	/*Intializing its Info value to the InsertionNumber*/
// 	NewElement -> infoPtr = InsertionNumber;
	
// 	/*Changing the StartAdress to make the new element the beginning of the linked list*/
// 	NewElement -> linkPtr = StartAdress;
// 	StartAdress = NewElement;
	
// 	/*Returning the new adress of the linked list*/
// 	return StartAdress;
// }

// void insertAtEnd(Node_t *StartAdress, int InsertionNumber)
// {
// 	/*Defining Variables*/
// 	Node_t *TempPtr = StartAdress;
	
// 	/*Reserving a new node*/
// 	Node_t *NewElement = malloc(sizeof(Node_t));
	
// 	/*Intializing its Info value to the InsertionNumber, and its Link to NULL*/
// 	NewElement -> infoPtr = InsertionNumber;
// 	NewElement -> linkPtr = NULL; 
	
// 	/*Looping over the linked list elements to reach the last element*/
// 	while(TempPtr -> linkPtr != NULL)
// 	{
// 		/*Moving the TempPtr to the next element of the linked list*/
// 		TempPtr = TempPtr -> linkPtr;
// 	}
	
// 	/*Expanding the linked list by changing the Link of the last element to the new element*/
// 	TempPtr -> linkPtr = NewElement;
// }