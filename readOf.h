#include<stdio.h>
#include"HT.h"
typedef struct Huffchar{
    char letter;
    char bitstap[8];
} Huffchar;


void writeBinaryFile(FILE *filename, int sizeofDict, Huffchar tab[]);
char *readBinaryFile(FILE *filename);       
void dictionary(HuffNode *hTree, char *str, int count,Huffchar *tab,int *huffcount);
