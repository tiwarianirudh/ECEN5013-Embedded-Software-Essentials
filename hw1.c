#include <stdio.h>
#include <stdlib.h>
#include "hw1.h"

char reverse (char * str, int length){
char temp;
int i,len_of_string;

if(str == NULL){
return -1;
}

if(length <= 0){
return -2;
}

len_of_string = measure_len(str);
if(len_of_string != length){	
return -3;
}

if(*str == '\0'){
return -4;
}

for(i=0;i<(length/2);i++){
temp = *(str+i);
*(str+i)=*(str+length-(i+1));
*(str+length-(i+1))=temp;
}
return 0;
}

int measure_len(char * str){	
int length=0;

while(*str++ != '\0'){
length++;
}

return length;
}
