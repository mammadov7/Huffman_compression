#include<stdio.h>
#include<stdlib.h>
typedef struct BIT_BUFFER{
    FILE *f;
    int pos;
    char bits;
}   BIT_BUFFER;

void bb_init(BIT_BUFFER *buff, FILE *fp);
void bb_print(BIT_BUFFER *buff);
void bb_fill(BIT_BUFFER *buff, int s,char *bitsTab);
int numbofChar(char *FILE_NAME);
char *getArr(char *FILE_NAME,int size);