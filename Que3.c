
#include<stdio.h>
int main()
{
    int num, reverse = 0, rem;
    printf("Enter the number : ");
    scanf("%d", &num);
    while(num)
    {
        rem = num % 10;
        reverse = reverse * 10 + rem;
        num = num / 10;

    }
    printf("Reverse Number is %d\n", reverse);
} 
