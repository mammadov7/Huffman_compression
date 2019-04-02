#include <string.h>
#include <math.h>
#include "LL.h"
#include "HT.h"
#include"readOf.h"
#include"toBits.h"

char *readFile();
unsigned maxChar(LLNode *pList);
unsigned nbrChar(LLNode *pList);
double entropy(LLNode *pList);

int main(){
    LLNode *pList=NULL;
    int n;
    char cAction, l;
    char *tc=readFile();

    int i=0;
    do { 
        if(!LL_Search_L(pList, tc[i]))
            LL_add(&pList, tc[i], 1);
        i++;
    } while(tc[i]!='\n'); //'\0' for multi lines
    LL_Print(pList);
    LLNode *psList = NULL;
    while(pList) {
        LLNode *temp=pList->pNext;
        LL_sorted_add(&psList, pList->ch, pList->nVal);
        free(pList);
        pList=temp;
    }
    LL_Print(psList);
    printf("The entropy value of the file is: %lf \n",entropy(psList));
    HLNode *hlist=readList(psList);
    HuffNode *huffmanTree=buildTree(hlist);
    printHTree(huffmanTree);

    int sizeOfDict=nbrChar(psList);//number of char in the List is size of the dictionary
    Huffchar *dict=(Huffchar*)calloc(sizeOfDict,sizeof(Huffchar));//allocatation of table with size of dictionary
    char *str = (char*) calloc(10, sizeof(char));
    int tmp = 0;
    dictionary(huffmanTree,str,0,dict,&tmp); //creation of the dictionary

    FILE *wr = fopen("test_bin.txt", "wb");
    i = 0;  
    do { //printf("%c",tc[i]); 
        int size = 0;
        str = (char*) calloc(10, sizeof(char));
        findLetter(huffmanTree, str, tc[i], 0, &size);
        for (int i = 0; i < size; i++) {
            fprintf(wr, "%c", str[i]);
        }
        i++;
    } while(tc[i]!='\n');
    fclose(wr);

    //creating Binary file
    FILE *testBinary;
    testBinary = fopen("test.bin","w+b");
    if(testBinary==NULL){printf("Could not open file\n");return 0;}
    writeBinaryFile(testBinary,sizeOfDict,dict); // it writes the dictionary in the file
    int size = numbofChar("test_bin.txt"); //it returns number of the charcters in the file
    char *bits=(char *)malloc(size*sizeof(char)); // for allocating the array
    bits=getArr("test_bin.txt",size); // it stores from file to the array

    BIT_BUFFER buff;
    bb_init(&buff,testBinary);
    bb_fill(&buff,size,bits);
    fclose(testBinary);
  
    return 0;
}


char *readFile() {
    FILE *file = fopen("test.txt", "r");
    char *code;
    size_t n = 0;
    int c;
    if (file == NULL) return NULL;  //could not open
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);
    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    return code;
}

unsigned maxChar(LLNode *pList){
    unsigned nbChar = 0;
    while (pList) {
        nbChar += pList->nVal;
        pList = pList->pNext;
    }
    return nbChar;
}

unsigned nbrChar(LLNode *pList){
    unsigned nbChar = 0;
    while (pList) {
        nbChar++;
        pList = pList->pNext;
    }
    return nbChar;
}

double entropy(LLNode *pList){
    unsigned nbChars = maxChar(pList);
    double entrop = 0, prob, f;
    while (pList) {
        prob = pList->nVal / (float) nbChars;
        f = prob * log2(1 / prob);
        entrop += f;
        pList = pList->pNext;
    }
    return entrop;
}
