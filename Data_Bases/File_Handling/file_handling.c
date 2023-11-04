#include "../../Libraries/STD_TYPES.h"
#include "../../Payment_System/Card/card.h"
#include "../../Payment_System/Terminal/terminal.h"
#include "../../Data_Structures/List/list.h"
#include "../../Payment_System/Server/server.h"

#include "file_handling.h"

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

EN_fileError_t loadAccountsData(ST_node_t **accountsListPtrPtr)
{
	/*Define file error state*/
	EN_fileError_t _fileError = FILE_OK;
	/*Define an indicator*/
	uint8_t _indicator = 0;
	/*Define a flag*/
	uint8_t _scanningFlag;
	/*Define a temporary pointer to an account struct*/
	ST_accountsDB_t *_tempAccountPtr = NULL;
	/*Define a node for the starting point of the linked list*/
	ST_node_t *_accountsListPtr = NULL;

	/*Open accounts file*/
	FILE *_filePtr = NULL;
	_filePtr = fopen("D:/BReakinPoint LVL1/PaymentApplication/System/Data_Bases/Data/accounts_DB.csv", "r");
	
	/*Validate the file pointer*/
	if(_filePtr != NULL)
	{	
		/*Create a new linked list for accounts*/
		_accountsListPtr = createLinkedList(0);
		
		/*Create nodes for the accounts exist in the accounts file*/
		do
		{
			/*Create new account variable*/
			_tempAccountPtr = (ST_accountsDB_t *) malloc(sizeof(ST_accountsDB_t));

			/*Scan the account details into the account variable*/
			_scanningFlag = fscanf(_filePtr,
									"%f,%d,%19[^\n]s",
									&(_tempAccountPtr -> balance),
									&(_tempAccountPtr -> state),
									(_tempAccountPtr -> primaryAccountNumber));

			/*Insert the new account member into the accounts list*/
			_accountsListPtr = insertAtEnd(_accountsListPtr, (ST_accountsDB_t *) _tempAccountPtr);

			/*Ensure that the process has done successfully*/
			if(_scanningFlag == 3)
			{
				_indicator++;
			}
			
			/*Ensure that the file format is correct*/
			if((_scanningFlag != 3) && (!feof(_filePtr)))
			{
				_fileError = FILE_FORMAT_INCORRECT;
			}

			/*Ensure that there are no errors*/
			if(ferror(_filePtr))
			{
				_fileError = ERROR_READING_FILE;
			}
		}
		/*Loop till the end of the file*/
		while((!feof(_filePtr)) && (_fileError == FILE_OK));

		/*Close the file*/
		fclose(_filePtr);
		
		/*Return the list handler to the user*/
		*accountsListPtrPtr = _accountsListPtr;
	}
	else
	{
		_fileError = ERROR_OPENNING_FILE;
	}

	/*Return error state*/
	return _fileError;
}

void viewAccountsData(ST_node_t *accountsListPtr)
{
	while(accountsListPtr != NULL)
	{
		printf("%.2f\t", (*((ST_accountsDB_t *)((*accountsListPtr).infoPtr))).balance);
		printf("%d\t", (*((ST_accountsDB_t *)((*accountsListPtr).infoPtr))).state);
		printf("%s\n", (*((ST_accountsDB_t *)((*accountsListPtr).infoPtr))).primaryAccountNumber);
		accountsListPtr = accountsListPtr -> linkPtr;
	}
}

EN_fileError_t loadTransactionsData(ST_node_t **transactionsListPtrPtr)
{
	/*Define file error state*/
	EN_fileError_t _fileError = FILE_OK;
	/*Define an indicator*/
	uint8_t _indicator = 0;
	/*Define a flag*/
	uint8_t _scanningFlag;
	/*Define a temporary pointer to an account struct*/
	ST_transaction_t *_tempTransactionPtr = NULL;
	/*Define a node for the starting point of the linked list*/
	ST_node_t *_transactionsListPtr = NULL;

	/*Open transactions file*/
	FILE *_filePtr = NULL;
	_filePtr = fopen("D:/BReakinPoint LVL1/PaymentApplication/System/Data_Bases/Data/transactions_DB.csv", "r");
	
	/*Validate the file pointer*/
	if(_filePtr != NULL)
	{	
		/*Create a new linked list for accounts*/
		_transactionsListPtr = createLinkedList(0);
		
		/*Create nodes for the accounts exist in the accounts file*/
		do
		{
			/*Create new transaction variable*/
			_tempTransactionPtr = (ST_transaction_t *) malloc(sizeof(ST_transaction_t));

			/*Scan the account details into the account variable*/
			_scanningFlag = fscanf(_filePtr,
									"%24[^,],%19[^,],%5[^,],%f,%f,%10[^,],%d,%d\n",
									(_tempTransactionPtr -> cardHolderData.cardHolderName),
									(_tempTransactionPtr -> cardHolderData.primaryAccountNumber),
									(_tempTransactionPtr -> cardHolderData.cardExpirationDate),
									&(_tempTransactionPtr -> terminalData.transAmount),
									&(_tempTransactionPtr -> terminalData.maxTransAmount),
									(_tempTransactionPtr -> terminalData.transactionDate),
									&(_tempTransactionPtr -> transState),
									&(_tempTransactionPtr -> transactionSequenceNumber));

			/*Insert the new account member into the accounts list*/
			_transactionsListPtr = insertAtEnd(_transactionsListPtr, (ST_transaction_t *) _tempTransactionPtr);

			/*Ensure that the process has done successfully*/
			if(_scanningFlag == 8)
			{
				_indicator++;
			}

			/*Ensure that the file format is correct*/
			if((_scanningFlag != 8) && (!feof(_filePtr)))
			{
				_fileError = FILE_FORMAT_INCORRECT;
			}

			/*Ensure that there are no errors*/
			if(ferror(_filePtr))
			{
				_fileError = ERROR_READING_FILE;
			}
		}
		/*Loop till the end of the file*/
		while((!feof(_filePtr)));
		
		/*Send the last transcation sequence number to the server file to continue on it*/
		setTransactionsSequenceNumber(_tempTransactionPtr -> transactionSequenceNumber);
		
		/*Close the file*/
		fclose(_filePtr);
		
		/*Return the list handler to the user*/
		*transactionsListPtrPtr = _transactionsListPtr;
	}
	else
	{
		_fileError = ERROR_OPENNING_FILE;
	}

	/*Return error state*/
	return _fileError;
}

void viewTransactionsData(ST_node_t *transactionsListPtr)
{
	/*Defina a variable to help in printing*/
	char _temp;

	/*Loop over all the list elements and print them in a specific stamp*/
	while(transactionsListPtr != NULL)
	{
		system("cls");
		printf("Saved Transactions:\n");
		printf("#############################################\n");
		printf("Transaction Sequence Number: %d\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).transactionSequenceNumber);
		printf("Transaction Date: %s\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).terminalData.transAmount);
		printf("Transaction State: %d\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).transState);
		printf("Terminal Max Account: %.2f\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).terminalData.maxTransAmount);
		printf("Card Holder Name: %s\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).cardHolderData.cardHolderName);
		printf("PAN: %s\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", (*((ST_transaction_t *)((*transactionsListPtr).infoPtr))).cardHolderData.cardExpirationDate);
		printf("#############################################\n");
		
		/*Don't traverse until the user press character 'n'*/
		printf("\nEnter n to continue: ");
		scanf("%c", &_temp);
		fflush(stdin);

		if(_temp == 'n')
		{
			transactionsListPtr = transactionsListPtr -> linkPtr;
		}
		else
		{
			system("cls");
			printf("#############################################\n");
			printf("Wrong Input!\n");
			printf("#############################################\n");
			sleep(1);
			break;
		}
	}

	if(_temp == 'n')
	{
		system("cls");
		printf("#############################################\n");
		printf("List has finished.\n");
		printf("#############################################\n");
		sleep(1);
	}
}

EN_fileError_t searchForAccount(ST_node_t *accountsListPtr, char *primaryAccountNumber, void **accountReference)
{
	/*Define file error*/
	EN_fileError_t _fileError = FILE_OK;

	/*Check if the list is empty or not*/
	if(accountsListPtr != NULL)
	{
		/*Search for the PAN into the linked list*/
		while(accountsListPtr != NULL)
		{
			/*If the PAN exists, return it to the user*/
			if(!(strcmp(((*((ST_accountsDB_t *)(accountsListPtr -> infoPtr))).primaryAccountNumber), primaryAccountNumber)))
			{
				*accountReference = accountsListPtr -> infoPtr;
				break;
			}
			/*Else, traverse to the next node*/
			else
			{
				accountsListPtr = accountsListPtr -> linkPtr;
			}
		}

		/*If the list has ended without founding the PAN, tell the user*/
		if(accountsListPtr == NULL)
		{
			_fileError = PAN_NOT_FOUND;
		}
	}
	else
	{
		_fileError = EMPTY_ACCOUNTS_LIST;
	}

	/*Return error stata*/
	return _fileError;
}

ST_node_t *createNewListNode(ST_node_t *listPtr, void *nodeInfoPtr)
{
	/*Insert the new member into the list*/
	return insertAtEnd(listPtr, nodeInfoPtr);
}

EN_fileError_t retrieveAccountsData(ST_node_t *accountsListPtr)
{
	/*Define file error state*/
	EN_fileError_t _fileError = FILE_OK;
	/*Defina a temporary node pointer to free nodes*/
	ST_node_t *_tempNode;

	/*Open accounts file*/
	FILE *_filePtr = NULL;
	_filePtr = fopen("D:/BReakinPoint LVL1/PaymentApplication/System/Data_Bases/Data/accounts_DB.csv", "w");
	
	/*Validate the file pointer*/
	if(_filePtr != NULL)
	{	
		/*Print all the list members into the accounts file*/
		while(accountsListPtr != NULL)
		{
			/*Print each account details into the database file*/
			fprintf(_filePtr,
					"%.2f,%d,%s",
					((*((ST_accountsDB_t *)(accountsListPtr -> infoPtr))).balance),
					((*((ST_accountsDB_t *)(accountsListPtr -> infoPtr))).state),
					((*((ST_accountsDB_t *)(accountsListPtr -> infoPtr))).primaryAccountNumber));
			
			/*Keep the address of the previous node*/
			_tempNode = accountsListPtr;
			
			/*Traverse to the next node*/
			accountsListPtr = accountsListPtr -> linkPtr;
			
			/*Free the previous node*/
			free(_tempNode);

			if(accountsListPtr != NULL)
			{
				fprintf(_filePtr, "\n");
			}
		}

		/*Ensure that there are no errors*/
		if(ferror(_filePtr))
		{
			_fileError = ERROR_WRITING_FILE;
		}
		
		/*Close the file*/
		fclose(_filePtr);
	}
	else
	{
		_fileError = ERROR_OPENNING_FILE;
	}

	/*Return error state*/
	return _fileError;
}

EN_fileError_t retrieveTransactionsData(ST_node_t *transactionsListPtr)
{
	/*Define file error state*/
	EN_fileError_t _fileError = FILE_OK;
	/*Defina a temporary node pointer to free nodes*/
	ST_node_t *_tempNode;

	/*Open accounts file*/
	FILE *_filePtr = NULL;
	_filePtr = fopen("D:/BReakinPoint LVL1/PaymentApplication/System/Data_Bases/Data/transactions_DB.csv", "w");
	
	/*Validate the file pointer*/
	if(_filePtr != NULL)
	{	
		/*Print all the list members into the accounts file*/
		while(transactionsListPtr != NULL)
		{
			/*Print each account details into the database file*/
			fprintf(_filePtr,
					"%s,%s,%s,%.2f,%.2f,%s,%d,%d",
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).cardHolderData.cardHolderName),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).cardHolderData.primaryAccountNumber),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).cardHolderData.cardExpirationDate),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).terminalData.transAmount),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).terminalData.maxTransAmount),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).terminalData.transactionDate),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).transState),
					((*((ST_transaction_t *)(transactionsListPtr -> infoPtr))).transactionSequenceNumber));

			/*Keep the address of the previous node*/
			_tempNode = transactionsListPtr;
			
			/*Traverse to the next node*/
			transactionsListPtr = transactionsListPtr -> linkPtr;
			
			/*Free the previous node*/
			free(_tempNode);

			if(transactionsListPtr != NULL)
			{
				fprintf(_filePtr, "\n");
			}
		}

		/*Ensure that there are no errors*/
		if(ferror(_filePtr))
		{
			_fileError = ERROR_WRITING_FILE;
		}
		
		/*Close the file*/
		fclose(_filePtr);
	}
	else
	{
		_fileError = ERROR_OPENNING_FILE;
	}

	/*Return error state*/
	return _fileError;
}
