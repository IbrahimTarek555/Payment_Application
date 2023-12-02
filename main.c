#include "Libraries/STD_TYPES.h"

#include "Data_Structures/List/list.h"

#include "Data_Bases/File_Handling/file_handling.h"

#include "Payment_System/Card/card.h"
#include "Payment_System/Terminal/terminal.h"
#include "Payment_System/Server/server.h"

#include "Application/application.h"

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    system("cls");
    /*Define a choice variable*/
    uint32_t _userChoice;

    /*Define error state for the accounts list*/
    EN_fileError_t _accountsFileErrorState;
    /*Define error state for the transactions list*/
    EN_fileError_t _transactionsFileErrorState;
    
    /*Fill two lists with all the data inside databases*/
    ST_node_t *_accountsListPtr = NULL;
    ST_node_t *_transactionsListPtr = NULL;
    
    _accountsFileErrorState = loadAccountsData(&_accountsListPtr);
    _transactionsFileErrorState = loadTransactionsData(&_transactionsListPtr);

    /*Ensure that the system has been initialized correctly*/
    if((_accountsFileErrorState == FILE_OK) && (_transactionsFileErrorState == FILE_OK))
    {
        /*Send the accounts list ptr to the server layer*/
        setAccountsListPtr(_accountsListPtr);
        /*Send the transactions list ptr to the server layer*/
        setTransactionsListPtr(_transactionsListPtr);

        /*Print system choices*/
        while(1)
        {
            system("cls");

            printf("#############################################\n");
            
            printf("Choices:\n");
            
            printf("Press 1 for: New Transaction.\n");
            printf("Press 2 for: List saved transactions.\n");
            printf("Press 0 for: Exit\n");
            printf("#############################################\n");

            printf("\nYour Choice: ");
            scanf("%d", &_userChoice);
            fflush(stdin);

            if(_userChoice == 1)
            {
                appStart();
            }
            else if(_userChoice == 2)
            {
                listSavedTransactions();
            }
            else if(_userChoice == 0)
            {
                break;
            }
            else
            {
                system("cls");
                printf("#############################################\n");
                printf("Wrong Input.\n");
                printf("#############################################\n");
                sleep(1);
            }
        }

        /*Close the system, retriving all the databases*/
        _accountsFileErrorState = retrieveAccountsData(_accountsListPtr);
        _transactionsFileErrorState = retrieveTransactionsData(_transactionsListPtr);
        
        /*Ensure that the system has been finished correctly*/
        if(!((_accountsFileErrorState == FILE_OK) && (_transactionsFileErrorState == FILE_OK)))
        {
            printf("Error finishing the system, call service.");
        }
    }
    else
    {
        printf("Error initializing the system, try again leter.");
    }
}
