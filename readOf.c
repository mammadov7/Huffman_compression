#include"readOf.h"

void writeBinaryFile(FILE *filename, int sizeofDict, Huffchar tab[]){
    //firstly save the file size 
    putw(sizeofDict,filename);
    //save the table of structures
    for(int i=0;i<sizeofDict; i++) fwrite(&tab[i],sizeof(Huffchar),1,filename);
}

char *readBinaryFile(FILE *filename){
    int num=getw(filename);
    printf("the number of character is %d",num);//this line is just for test
    Huffchar newch={0,""};
    while(!feof(filename)){
        fread(&newch,sizeof(Huffchar),1,filename);
        printf("character %c : %s",newch.letter,newch.bitstap); 
    }
    //read the compresses text and translate
}
//this function creates dictionary from the HUFFMAN tree
void dictionary(HuffNode *hTree, char *str, int count,Huffchar *tab,int *huffcount) {
    if (hTree->left == NULL && hTree->right == NULL) {
        tab[*huffcount].letter=hTree->ch;
        for (int i = 0; i < count; i++) {
             tab[*huffcount].bitstap[i]=str[i];
        }
        (*huffcount)++;
    } else {
        if (hTree->left) {
            str[count] = '0';
            dictionary(hTree->left, str, count + 1,tab,huffcount);
        }
        if (hTree->right) {
            str[count] = '1';
            dictionary(hTree->right, str, count + 1,tab,huffcount);
        }
    }
}