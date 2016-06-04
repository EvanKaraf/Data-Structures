#include <stdio.h>
#include <string.h>
#include <time.h>
#include "HashTableInterface.h"
#define READ_FROM_FILE 1
#define READ_SINGLE 2
#define PRINT_HASH 3
#define SEARCH_HASH 4
#define QUIT 5
#define CLEAN_SCRN 6

#define HASH 1
#define REHASH -1
#define EmptyKey "0"

/*Prints menu options.*/
void options() {
    printf("~~~~~~~~Linear Hashing Menu~~~~~~~~\n");
    printf("1. Insert elements from file.\n");
    printf("2. Insert a single element.\n");
    printf("3. Print hash table.\n");
    printf("4. Search a key in the hash table.\n");
    printf("\n\n5. Quit.\n");
    printf("6. Clear screen.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
/*Read key(s) and insert it/them in the given hash table.*/
int readFromFile(Table *T) {
    char data[20];
    char key[100];
    char user_filename[150];
    int pos;
    int count = 0;
    float t=0,t1;
    int flag = 0;
    printf("Enter filename to read from:\n");
    scanf("%s", user_filename);
    FILE *file=fopen(user_filename, "r");
    if (!file) {
        printf("Error opening file..\n");
        return -1;
    }
    while (fscanf(file, "%s", key) == 1) {
        count++;
        strcpy(data,"placeholder");
        t1 = clock();
        pos = HashInsert(T,key,data,HASH);
        t += (clock()-t1)/CLOCKS_PER_SEC;
        //if (pos != -1) printf("Key %s inserted in position %d\n",key,pos);
        //else printf("Had to rehash.Please search if you want to find position.\n");
    }
    system("clear");
    options();
    printf("Read %d keys which took %f second(s).\n",count,t);
    return 0;
}

/*Read a single key and insert it in the given hash table.*/
void readHashEntry(Table *T) {
    char key[100];
    char data[20];
    int pos;
    printf("Enter key:\n");
    scanf("%s",key);
    printf("Enter data:\n");
    scanf("%s",data);
    pos = HashInsert(T,key,data,HASH);
    system("clear");
    options();
    if (pos != -1) printf("Key %s inserted in position %d\n",key,pos);
    else printf("Had to rehash.Please search if you want to find position.\n");
}

/*Prints given hash table including all keys.*/
void printHashTable(Table T){
    int count = 0;
    int i;
    ListNode* temp;
    system("clear");
    options();
    for (i=0; i<T.buckets; i++) {
        if (strcmp(T.TableArray[i].key,EmptyKey)) {
<<<<<<< HEAD
            if (T.TableArray[i].L == NULL)
                printf("In pos %d is key %s\n",i,T.TableArray[i].key);
            temp = T.TableArray[i].L;
            if (temp)
                printf("In position %d key(s): %s->",i,T.TableArray[i].key);
=======
        	if (T.TableArray[i].L == NULL)
            	printf("In pos %d is key %s\n",i,T.TableArray[i].key);
            temp = T.TableArray[i].L;
            if (temp)
            	printf("In position %d key(s): %s->",i,T.TableArray[i].key);
>>>>>>> origin/master
            while (temp) {
                printf("%s->",temp->Entry.key);
                temp = temp->next;
            }
            printf("\b\b  \n");
        } else if (!strcmp(T.TableArray[i].key,EmptyKey)) {
            count++;
        }
    }
    printf("Empty buckets are %d \n",count);
    printf("-----------------------------------------------\n");
}
/*Read user's input and act accordingly.*/
void menu(Table T) {
    int choice;
    char key[100];
    int pos;
    system("clear");
    options();
    while(1) {
        printf("Enter input:");
        scanf("%d",&choice);
        switch (choice) {
        case READ_FROM_FILE:
            system("clear");
            options();
            readFromFile(&T);
            break;
        case READ_SINGLE:
            system("clear");
            options();
            readHashEntry(&T);
            break;
        case PRINT_HASH:
            printHashTable(T);
            options();
            break;
        case SEARCH_HASH:
            printf("Enter key to search!:\n");
            scanf("%s",key);
            pos = SearchHash(T,key);
            system("clear");
            options();
            if (pos == -1) printf("FAILURE\nKey %s isn't in the hash table.\n",key);
            else printf("SUCCESS\nKey %s is in position %d\n",key,pos);
            break;
        case CLEAN_SCRN:
            system("clear");
            options();
            break;
        case QUIT:
	    printf("Exiting...\n");
            return;
            break;
        default:
            printf("Wrong input!\n");
            break;

        }
    }
}
