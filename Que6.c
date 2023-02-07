#include<stdio.h>
#include<string.h>

int main()
{
    char a[20];
    printf("Enter the Expression : ");
    scanf("%s", &a);
    int start, end;
    int l = strlen(a);
    int i,j;

    if(a[0] != 45)
    {
        for(int i = 0; i<l; i++)
        {
            if(a[i] == 45)
            {
                start = a[i-1];
                end = a[i+1];

                for(j = start; j<=end; j++)
                {
                    printf("%c", j);
                }
            }
        }
    }
    else
    {
        for(int i = 1; i<l; i++)
        {
            if(a[i] == 45)
            {
            start = a[i-1];
            end = a[i+1];


            for(int j = start; j<=end; j++)
            {
                printf("%c", j);
            }
            }
            
        }
    }
    return 0;
}
