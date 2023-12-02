#include "../../Libraries/STD_TYPES.h"

#include "../Card/card.h"
#include "terminal.h"

#include <string.h>
#include <stdio.h>
#include <time.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    /*Define terminal error state*/
    EN_terminalError_t _terminalError = TERMINAL_OK;

    /*Get the time and date of the transaction*/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    /*Construct the date format we depends on*/
    /*Construct the day*/
    if(tm.tm_mday < 10)
    {
        termData -> transactionDate[0] = '0';
        termData -> transactionDate[1] = tm.tm_mday + '0';
    }
    else 
    {
        termData -> transactionDate[0] = tm.tm_mday / 10 + '0';
        termData -> transactionDate[1] = tm.tm_mday % 10 + '0';
    }
    termData -> transactionDate[2] = '/';

    /*Construct the month*/
    tm.tm_mon = tm.tm_mon + 1;
    if(tm.tm_mon < 10)
    {
        termData -> transactionDate[3] = '0';
        termData -> transactionDate[4] = tm.tm_mon + '0';
    }
    else 
    {
        termData -> transactionDate[3] = tm.tm_mon / 10 + '0';
        termData -> transactionDate[4] = tm.tm_mon % 10 + '0';
    }
    termData -> transactionDate[5] = '/';
    
    /*Construct the year*/
    tm.tm_year = tm.tm_year + 1900;
    termData -> transactionDate[9] = tm.tm_year % 10 + '0';
    tm.tm_year = tm.tm_year / 10;
    termData -> transactionDate[8] = tm.tm_year % 10 + '0';
    tm.tm_year = tm.tm_year / 10;
    termData -> transactionDate[7] = tm.tm_year % 10 + '0';
    tm.tm_year = tm.tm_year / 10;
    termData -> transactionDate[6] = tm.tm_year % 10 + '0';
    termData -> transactionDate[10] = '\0';

    /*Return error state*/
    return _terminalError;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t* termData)
{
    /*Define terminal error state*/
    EN_terminalError_t _terminalError = TERMINAL_OK;
    /*Define temporary variable for expiry month*/
    uint8_t _expiryDateMonth;
    /*Define temporary variable for current month*/
    uint8_t _currentMonth;
    /*Define temporary variable for expiry year*/
    uint8_t _expiryDateYear;
    /*Define temporary variable for current year*/
    uint8_t _currentYear;
    
    /*Construct months and years needed*/
    _expiryDateMonth = (cardData -> cardExpirationDate[0] - '0') * 10 + (cardData -> cardExpirationDate[1] - '0');
    _currentMonth = (termData -> transactionDate[3] - '0') * 10 + (termData -> transactionDate[4] - '0');
    _expiryDateYear = (cardData -> cardExpirationDate[3] - '0') * 10 + (cardData -> cardExpirationDate[4] - '0');
    _currentYear = (termData -> transactionDate[8] - '0') * 10 + (termData -> transactionDate[9] - '0');

    /*Ensure that the card is not expired*/
    if(_expiryDateYear > _currentYear)
    {
        _terminalError = TERMINAL_OK;
    }
    else if(_expiryDateYear == _currentYear)
    {
        if(_expiryDateMonth < _currentMonth)
        {
            _terminalError = EXPIRED_CARD;
        }
        else
        {
            _terminalError = TERMINAL_OK;
        }
    }
    else 
    {
        _terminalError = EXPIRED_CARD;
    }

    /*Return error state*/
    return _terminalError;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    /*Define terminal error state*/
    EN_terminalError_t _terminalError = TERMINAL_OK;
    
    /*Ask for the transaction amount*/
    printf("Enter the transaction amount, please: ");
    
    /*Store the transaction amount into the terminal data*/
    scanf("%f", &termData -> transAmount);

    /*Validate the transaction amount*/
    if(termData -> transAmount <= 0)
    {
        _terminalError = INVALID_AMOUNT;
    }

    /*Return error state*/
    return _terminalError;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    /*Define terminal error state*/
    EN_terminalError_t _terminalError = TERMINAL_OK;
    
    /*Ensure that the transaction amount is below the maximum amount*/
    if(termData -> transAmount > termData -> maxTransAmount)
    {
        _terminalError = EXCEED_MAX_AMOUNT;
    }

    /*Return error state*/
    return _terminalError;    
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    /*Define terminal error state*/
    EN_terminalError_t _terminalError = TERMINAL_OK;
    
    /*Validate the max allowed amount*/
    if(maxAmount > 0)  
    {
        termData -> maxTransAmount = maxAmount;
    }
    else
    {
        _terminalError = INVALID_MAX_AMOUNT;
    }

    /*Return error state*/
    return _terminalError;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    /*Define terminal error state*/
    EN_terminalError_t _terminalError = TERMINAL_OK;
    /*Define a loop counter*/
    sint8_t _counter;
    /*Define an indicator*/
    uint8_t _indicator = 0;
    /*Define a sum*/
    uint8_t _sum = 0;
    /*Define a temporary number*/
    uint8_t _tempNum;
    /*Define a control checksum number*/
    uint8_t _actualControl;
    /*Define an inputed control number*/
    uint8_t _inputedControl = cardData -> primaryAccountNumber[strlen(cardData -> primaryAccountNumber) - 1] - '0';

    /*Ensure that the PAN is Luhn number*/
    for(_counter = strlen(cardData -> primaryAccountNumber) - 2; _counter >= 0; _counter--)
    {
        /*Put the number into temporary variable*/
        _tempNum = cardData -> primaryAccountNumber[_counter] - '0';

        /*Multiply numbers with even rank*/
        _indicator++;
        if(_indicator % 2)
        {
            _tempNum = _tempNum * 2;

            if(_tempNum >= 10)
            {
                _tempNum = _tempNum / 10 + _tempNum % 10;
            }
        }

        /*Update the summation*/
        _sum = _sum + _tempNum;
    }

    /*Calculate the control number*/
    _actualControl = (10 - (_sum % 10)) % 10;

    /*Validate the control number*/
    if(_actualControl != _inputedControl)
    {
        _terminalError = INVALID_CARD;
    }

    /*Return error state*/
    return _terminalError;
}
