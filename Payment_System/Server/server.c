#include "../../Libraries/STD_TYPES.h"

#include "../../Data_Structures/List/list.h"

#include "../../Data_Bases/File_Handling/file_handling.h"

#include "../Card/card.h"
#include "../Terminal/terminal.h"

#include "server.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Define a global variable to access the accounts list*/
ST_node_t *__accountsListPtr = NULL;
/*Define a global variable to access the transactions list*/
ST_node_t *__transactionsListPtr = NULL;
/*Defina a global variable to carry the last transaction list number*/
uint32_t __lastTransactionsSequenceNumber;

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    /*Define a transaction error state*/
    EN_transState_t _transError;
    ST_accountsDB_t *_tempAccountPtr;
    EN_serverError_t _transServerError;
    EN_serverError_t _saveServerError;

    /*Search for the account into the database*/
    _transServerError = isValidAccount(&transData -> cardHolderData, &_tempAccountPtr);

    /*Check if the account is found or not*/
    if(_transServerError == SERVER_OK)
    {
        /*Check if the transaction amount is available or not*/
        _transServerError = isAmountAvailable(&transData -> terminalData, _tempAccountPtr);

        if(_transServerError == SERVER_OK)
        {
            /*Check if the account is blocked or not*/
            _transServerError = isBlockedAccount(_tempAccountPtr);

            if(_transServerError == SERVER_OK)
            {
                /*Here, transaction is going well*/
                _transError = APPROVED;
                transData -> transState = APPROVED;
            }   
            else
            {
                _transError = DECLINED_STOLEN_CARD;
                transData -> transState = DECLINED_STOLEN_CARD;
            }
        }
        else
        {
            _transError = DECLINED_INSUFFECIENT_FUND;
            transData -> transState = DECLINED_INSUFFECIENT_FUND;
        }
    }
    else
    {
        _transError = FRAUD_CARD;
        transData -> transState = FRAUD_CARD;
    }

    /*Save the transaction to the transactions list*/
    _saveServerError = saveTransaction(transData);

    /*If the transaction is approved, and saved successfully into the data base, then deduct the transaction amount from the balance*/
    if((_saveServerError == SERVER_OK) && (_transServerError == SERVER_OK))
    {
        _tempAccountPtr -> balance -= transData -> terminalData.transAmount;
    }
    else
    {
        _transError = INTERNAL_SERVER_ERROR;
    }

    /*Return error state*/
    return _transError;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountReference)
{
    /*Define server error state*/
    EN_serverError_t _serverError = SERVER_OK;
    /*Define file error state*/
    EN_fileError_t _fileError;
    /*Defina a pointer to the account reference*/
    void *_accountReference;
    
    /*Search for the PAN inside the accounts linked list*/
    _fileError = searchForAccount(__accountsListPtr, cardData -> primaryAccountNumber, &_accountReference);

    /*Check for the file error*/
    if(_fileError != FILE_OK)
    {
        /*Account hasn't been found*/
        *accountReference = NULL;
        _serverError = ACCOUNT_NOT_FOUND;
    }
    else
    {
        /*Account has been found*/    
        *accountReference = _accountReference;
    }

    /*Return server error*/
    return _serverError;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
    /*Define server error state*/
    EN_serverError_t _serverError;

    /*Check if the account is blocked or running*/
    if(accountReference -> state == RUNNING)
    {
        _serverError = SERVER_OK;
    }
    else
    {
        _serverError = BLOCKED_ACCOUNT;
    }

    /*Return server error*/
    return _serverError;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t* accountReference)
{
    /*Define server error state*/
    EN_serverError_t _serverError;
    
    /*Check if the transaction amount is available or not*/
    if(termData -> transAmount <= accountReference -> balance)
    {
        _serverError = SERVER_OK;
    }
    else
    {
        _serverError = LOW_BALANCE;
    }

    /*Return server error*/
    return _serverError;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    /*Define server error state*/
    EN_serverError_t _serverError = SERVER_OK;
    /*Define a temporary transaction pointer*/
    ST_transaction_t *_tempTransactionPtr = NULL;

    /*Create new transaction variable*/
	_tempTransactionPtr = (ST_transaction_t *) malloc(sizeof(ST_transaction_t));

    /*Copy the data into the new transaction node info*/
    *_tempTransactionPtr = *transData;

    /*Give the new node the sequence number*/
    _tempTransactionPtr -> transactionSequenceNumber = ++__lastTransactionsSequenceNumber;

    /*Insert the new node into the transactions list*/
    __transactionsListPtr = createNewListNode(__transactionsListPtr, _tempTransactionPtr);

    /*Return server error*/
    return _serverError;
}

void listSavedTransactions(void)
{
    viewTransactionsData(__transactionsListPtr);
}

void setAccountsListPtr(ST_node_t *accountsListPtr)
{
    /*Make the accounts list pointer a global variable to the server file*/
    __accountsListPtr = accountsListPtr;
}

void setTransactionsListPtr(ST_node_t *transactionsListPtr)
{
    /*Make the transactions list pointer a global variable to the server file*/
    __transactionsListPtr = transactionsListPtr;
}

void setTransactionsSequenceNumber(uint32_t lastTransactionSequenceNumber)
{
    /*Make the last transaction sequence number a global variable to the sever file*/
    __lastTransactionsSequenceNumber = lastTransactionSequenceNumber;
}