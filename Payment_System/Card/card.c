#include "../../Libraries/STD_TYPES.h"

#include "card.h"

#include <string.h>
#include <stdio.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    /*Define card error state*/
    EN_cardError_t _cardError = CARD_OK;
    
    /*Ask for the card holder's name*/
    printf("Enter your name, please: ");

    /*Store the card holder's name into the card data*/
    scanf("%24[^\n]s", cardData -> cardHolderName);

    /*Flush the stdin buffer*/
    while ((getchar()) != '\n');

    /*Validate the inputed holder's name*/
    if((cardData -> cardHolderName == NULL) || (strlen(cardData -> cardHolderName) < 20))
    {
        _cardError = WRONG_NAME;
    }

    /*Return the error state*/
    return _cardError;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    /*Define card error state*/
    EN_cardError_t _cardError = CARD_OK;
    
    /*Define loop counter*/
    uint8_t _counter;

    /*Define variable to carry the expiry date month*/
    uint8_t _expiryDateMonth;

    /*Ask for the expiry date*/
    printf("Enter the card expiry date, please: ");
    
    /*Store the card expiry date into the card data*/
    scanf("%5[^\n]s", cardData -> cardExpirationDate);
    
    /*Flush the stdin buffer*/
    while ((getchar()) != '\n');
    
    /*Validate the inputed expiry date*/
    if((cardData -> cardExpirationDate == NULL) || (strlen(cardData -> cardExpirationDate) < 5))
    {
        _cardError = WRONG_EXP_DATE;
    }
    else
    {
        /*Validate the expiry date format*/
        for(_counter = 0; _counter < 5; _counter++)
        {
            if(_counter == 2)
            {
                if(cardData -> cardExpirationDate[_counter] != '/')
                {
                    _cardError = WRONG_EXP_DATE;
                    break;
                }
            }
            else 
            {
                if(!(cardData -> cardExpirationDate[_counter] <= '9') && (cardData -> cardExpirationDate[_counter] >= '0'))
                {
                    _cardError = WRONG_EXP_DATE;
                    break;
                }
            }
        }

        /*Validate the expiry date month*/
        if(_cardError != WRONG_EXP_DATE)
        {
            _expiryDateMonth = (cardData -> cardExpirationDate[0] - '0') * 10 + (cardData -> cardExpirationDate[1] - '0');
            if(!(_expiryDateMonth <= 12))
            {
                _cardError = WRONG_EXP_DATE;
            }
        }
    }

    /*Return the error state*/
    return _cardError;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    /*Define card error state*/
    EN_cardError_t _cardError = CARD_OK;
    
    /*Define loop counter*/
    uint8_t _counter;

    /*Ask for the PAN*/
    printf("Enter the PAN, please: ");
    
    /*Store the PAN into the card data*/
    scanf("%19[^\n]s", cardData -> primaryAccountNumber);
    
    /*Flush the stdin buffer*/
    while ((getchar()) != '\n');
    
    /*Validate the inputed PAN*/
    if((cardData -> primaryAccountNumber == NULL) || (strlen(cardData -> primaryAccountNumber) < 16))
    {
        _cardError = WRONG_PAN;
    }
    else
    {
        /*Ensure that PAN has only numbers*/
        for(_counter = 0; _counter < strlen(cardData -> primaryAccountNumber); _counter++)
        {
            if(!((cardData -> primaryAccountNumber[_counter] <= '9') && (cardData -> primaryAccountNumber[_counter] >= '0')))
            {
                printf("h%dhh", _counter);
                _cardError = WRONG_PAN;
                break;
            }
        }
    }

    /*Return the error state*/
    return _cardError;
}