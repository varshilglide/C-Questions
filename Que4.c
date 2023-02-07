#include<stdio.h>
#include<stdlib.h>
 
int invert(const int, int, int);

int main(int argc, char **argv)
{

    int i;
    int position;
    int count;

    scanf("%d", &i);
    scanf("%d", &position);
    scanf("%d", &count);
    
    printf("The inverted integer is : \t%d\n", invert(i, position, count));
    return 0;

}
int invert(const int i, int position, int count)
{
    int mask = ~(~0 << count) << position;
    return i ^ mask;    
}



