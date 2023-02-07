#include<stdio.h>
// #include "CompareFunction.c"

int CompareFunction(char[],char[]);
int main()
{
       char str1[10];
       char str2[10];
       printf("Enter First String : " );
       scanf("%s", &str1);
       printf("Enter second String : ");
       scanf("%s", &str2);

       int ans;
       ans = CompareFunction(str1, str2);
       
       return 0;
}