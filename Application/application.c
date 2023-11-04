#include "../Libraries/STD_TYPES.h"

#include "../Data_Structures/List/list.h"

#include "../Payment_System/Card/card.h"
#include "../Payment_System/Terminal/terminal.h"
#include "../Payment_System/Server/server.h"

#include "application.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void appStart(void)
{
    EN_cardError_t _cardError;
    EN_terminalError_t _terminalError;
    EN_transState_t _transError = INTERNAL_SERVER_ERROR;

    ST_transaction_t _currentTransactionData;

    /*Print the stamp*/
    system("cls");
    printf("New Transaction:\n");
    printf("#############################################\n\n");
    _cardError = getCardHolderName(&_currentTransactionData.cardHolderData);

    if(_cardError == WRONG_NAME)
    {
        system("cls");
        printf("#############################################\n");
        printf("Invalid Name.\n");
        printf("#############################################\n");
        sleep(1);
    }
    
    if(_cardError == CARD_OK)
    {
        system("cls");
        printf("New Transaction:\n");
        printf("#############################################\n\n");
        _cardError = getCardExpiryDate(&_currentTransactionData.cardHolderData);
    }

    if(_cardError == WRONG_EXP_DATE)
    {
        system("cls");
        printf("#############################################\n");
        printf("Wrong Expiry Date Format!\n");
        printf("#############################################\n");
        sleep(1);
    }

    if(_cardError == CARD_OK)
    {
        system("cls");
        printf("New Transaction:\n");
        printf("#############################################\n\n");
        _cardError = getCardPAN(&_currentTransactionData.cardHolderData);
        _terminalError = isValidCardPAN(&_currentTransactionData.cardHolderData);
    }
    
    if((_terminalError == INVALID_CARD) || (_cardError == WRONG_PAN))
    {        
        system("cls");
        printf("#############################################\n");
        printf("Invalid PAN Number.\n");
        printf("#############################################\n");
        sleep(1);
    }

    if((_terminalError == TERMINAL_OK) && (_cardError == CARD_OK))
    {
        _terminalError = getTransactionDate(&_currentTransactionData.terminalData);
    }

    if(_terminalError == TERMINAL_OK)
    {
        _terminalError = isCardExpired(&_currentTransactionData.cardHolderData, &_currentTransactionData.terminalData);
    }

    if(_terminalError == EXPIRED_CARD)
    {        
        system("cls");
        printf("#############################################\n");
        printf("Expired Card.\n");
        printf("#############################################\n");
        sleep(1);
    }

    if(_terminalError == TERMINAL_OK)
    {
        _terminalError = setMaxAmount(&_currentTransactionData.terminalData, MAX_TRANSACTION_AMOUNT);
    }
    
    if(_terminalError == INVALID_MAX_AMOUNT)
    {
        system("cls");
        printf("#############################################\n");
        printf("Internal Error.\n");
        printf("#############################################\n");
        sleep(1);
    }

    if(_terminalError == TERMINAL_OK)
    {
        system("cls");
        printf("New Transaction:\n");
        printf("#############################################\n\n");
        _terminalError = getTransactionAmount(&_currentTransactionData.terminalData);
    }

    if(_terminalError == INVALID_AMOUNT)
    {
        system("cls");
        printf("#############################################\n");
        printf("Invalid Amount.\n");
        printf("#############################################\n");
        sleep(1);
    }

    if(_terminalError == TERMINAL_OK)
    {
        _terminalError = isBelowMaxAmount(&_currentTransactionData.terminalData);
    }

    if(_terminalError == EXCEED_MAX_AMOUNT)
    {
        system("cls");
        printf("#############################################\n");
        printf("Amount exceed limit.\n");
        printf("#############################################\n");
        sleep(1);
    }

    if(_terminalError == TERMINAL_OK)
    {
        _transError = recieveTransactionData(&_currentTransactionData);
    }

    if(_transError == APPROVED)
    {
        system("cls");
        printf("#############################################\n");
        printf("Successful Transaction.\n");
        printf("#############################################\n");
        sleep(1);
    }
    else
    {
        system("cls");
        printf("#############################################\n");
        printf("Unsuccessful Transaction.\n");
        printf("#############################################\n");
        sleep(1);
    }
}