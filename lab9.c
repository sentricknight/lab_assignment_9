#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order;
    struct RecordType* pNext;   // pointer to next record in the same index
};

// Fill out this structure
struct HashType
{
    struct RecordType* pRecord;
};

// Compute the hash function
int hash(int x)
{
    return x % 100;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);

        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i, j;

    for (i=0; i < hashSz; ++i)
    {
        if (pHashArray[i].pRecord != NULL)
        {
            printf("Index %d -> ", i);

            struct RecordType* pCur = pHashArray[i].pRecord;
            while (pCur != NULL)
            {
                printf("%d %c %d -> ", pCur->id, pCur->name, pCur->order);
                pCur = pCur->pNext;
            }

            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    struct HashType *pHashTable;
    int recordSz = 0, hashSz = 100, i, j;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    pHashTable = (struct HashType*) malloc(sizeof(struct HashType) * hashSz);

    if (pHashTable == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(-1);
    }

    for (i=0; i < hashSz; ++i)
    {
        pHashTable[i].pRecord = NULL;
    }

    // insert records into the hash table
    for (i = 0; i < recordSz; ++i)
{
int idx = hash(pRecords[i].id);
struct RecordType* pNewRecord = (struct RecordType*) malloc(sizeof(struct RecordType));
if (pNewRecord == NULL)
{
printf("Cannot allocate memory\n");
exit(-1);
}
pNewRecord->id = pRecords[i].id;
pNewRecord->name = pRecords[i].name;
pNewRecord->order = pRecords[i].order;
pNewRecord->pNext = NULL;

    if (pHashTable[idx].pRecord == NULL)
    {
        pHashTable[idx].pRecord = pNewRecord;
    }
    else
    {
        struct RecordType* pCur = pHashTable[idx].pRecord;
        struct RecordType* pPrev = NULL;
        while (pCur != NULL && pCur->id < pNewRecord->id)
        {
            pPrev = pCur;
            pCur = pCur->pNext;
        }

        if (pPrev == NULL)
        {
            pNewRecord->pNext = pCur;
            pHashTable[idx].pRecord = pNewRecord;
        }
        else
        {
            pPrev->pNext = pNewRecord;
            pNewRecord->pNext = pCur;
        }
    }
}

displayRecordsInHash(pHashTable, hashSz);

// Free memory
for (i=0; i < hashSz; ++i)
{
    struct RecordType *pCur = pHashTable[i].pRecord;
    while (pCur != NULL)
    {
        struct RecordType *pNext = pCur->pNext;
        free(pCur);
        pCur = pNext;
    }
}
free(pHashTable);
free(pRecords);

return 0;
}
