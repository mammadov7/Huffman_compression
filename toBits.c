#include"toBits.h"

void bb_init(BIT_BUFFER *buff, FILE *fp){
    buff->f=fp;
    buff->pos=0;
    buff->bits=0;
}
//-----------------------------------------------
void bb_print(BIT_BUFFER *buff){
    if(buff->pos==0)return;
//IF WE HAVE number of bits<8
    while(buff->pos<8){
        buff->bits &= ~(1<< 8-buff->pos-1);
        buff->pos++; 
    }
//WHEN ALL BITS are filled with 8 bits
        fwrite(&(buff->bits),sizeof(char),1,buff->f);
        buff->pos=0;
        buff->bits=0;
}
//----------------------------------------------------------------
void bb_fill(BIT_BUFFER *buff, int s,char *bitsTab){
    int i,shift_pos;
    for(i=0;i<s;i++){
        if(buff->pos==8) bb_print(buff);
        shift_pos= 8-buff->pos-1;
       // printf("%c\n",bitsTab[i]);
        if(bitsTab[i]=='1') buff->bits |= (1 << shift_pos);
        else buff->bits &= ~(1 << shift_pos);
        (buff->pos)++;
    }
    bb_print(buff);
}
//--------------------------------------------------------------------
int numbofChar(char *FILE_NAME){ //it returns number of the caracters in file
    int count = 0;  /* number of characters seen */
    FILE *in_file;    /* input file */
    int ch;
    in_file = fopen(FILE_NAME, "r");
    if (in_file == NULL) {
        printf("Cannot open %s\n", FILE_NAME);
        return 0;
    } 
    while (1){
        ch = fgetc(in_file);
        if (ch == EOF)
            break;
        ++count;
    }
    fclose(in_file);
    return count;
}//--------------------------------------------------------------------
char *getArr(char *FILE_NAME,int size){
    int i=0;
    FILE *in_file;
    in_file = fopen(FILE_NAME, "r");   
    char *arr=(char*)malloc(sizeof(char)*size);    
    while((fscanf(in_file,"%c",&arr[i]))!=EOF)//scanf and check EOF
    i++;
    fclose(in_file);
    return arr;
}