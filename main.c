#include <stdio.h>
#include <stdlib.h>
#include "hw1.h"

int main (void){
int number,c;
int8_t return_code;
char *str;
str = (char *)malloc(50);

printf("Enter the number of charecters: ");
scanf("%d",&number);
while ((c = getchar()) !=EOF && c != '\n');
printf("Enter the string:");
fgets(str,number+1,stdin);

return_code=(int8_t)reverse(str,number);

switch(return_code){
case -1:
printf("error:you passed a null pointer\n");
break;
case -2:
printf("error: length should be a positive number\n");
break;
case -3:
printf("error: entered length and length of string doesn't match\n");
break;
case -4:
printf("error: you passed a NULL charecter\n");
break;
case 0:
printf("\nReversed string:\n");
printf("%s\n",str);
break;
}
return 0;
}

