#include<stdio.h>
#include<string.h>

int CompareFunction(char str1[], char str2[])
{
     int value;
     value = strcmp(str1, str2);
     if(value == 0)
     {
        printf("0");
     }
     else
     {
        printf("-1");
     }

     return 0;
}   