#ifndef FILE_HANDLING_H_
#define FILE_HANDLING_H_

typedef enum EN_fileError_t
{
    FILE_OK, ERROR_OPENNING_FILE, FILE_FORMAT_INCORRECT, ERROR_READING_FILE, ERROR_WRITING_FILE, PAN_NOT_FOUND, EMPTY_ACCOUNTS_LIST
}EN_fileError_t;

EN_fileError_t loadAccountsData(ST_node_t **accountPtr);
void viewAccountsData(ST_node_t *accountsListPtr);
EN_fileError_t loadTransactionsData(ST_node_t **transactionsListPtrPtr);
void viewTransactionsData(ST_node_t *transactionsListPtr);
EN_fileError_t searchForAccount(ST_node_t *accountsListPtr, char *primaryAccountNumber, void **accountReference);
ST_node_t *createNewListNode(ST_node_t *listPtr, void *nodeInfoPtr);
EN_fileError_t retrieveAccountsData(ST_node_t *accountsListPtr);
EN_fileError_t retrieveTransactionsData(ST_node_t *transactionsListPtr);

#endif