#include<stdio.h>
int linearSearch(int arr[], int size, int element)
{
    for(int i = 0; i<size; i++)
    {
        if(arr[i] == element)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    int arr[5];
    int element;

    printf("Enter the Elements of the array : ");
    for(int i = 0 ; i<5 ; ++i)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter the element : ");
    scanf("%d", &element);
    int size = sizeof(arr) / sizeof(int);
    int SearchIndex = linearSearch(arr, size, element);
    printf("The Element %d was found at index %d\n", element, SearchIndex);
    return 0;
}