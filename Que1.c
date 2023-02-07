
/*
#include<stdio.h>
#include<string.h>
int forThreeDigit(char *a){
    char singleDigit[10][9] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *twoDigit[] = {"", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tensDigit[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char *tens_power[] = {"hundred", "thousand"};
    int num;  
    num = a[0] - 48;
        printf("%s %s ", singleDigit[num], tens_power[0]);
        //  for second digit
        if (a[1] == 49)
        {
            num = (a[1] - 48) + (a[2] - 48);
            printf("%s ", twoDigit[num]);
        }
        else if (a[1] == 48)
        {
            num = a[2] - 48;
            printf("%s ", singleDigit[num]);
        }
        else
        {
            num = a[1] - 48;
            printf("%s ", tensDigit[num]);
            num = a[2] - 48;
            printf("%s ", singleDigit[num]);
        }
}

void numberToWord()
{
    // char a[5] ="0123";
    // int x = a[3]-48;
    // printf("%d",x); //print 48 as ascii value of 0 is 48:; so, we minus the 48 from that value to get required value

    char a[20];
    char *singleDigit[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *twoDigit[] = {"", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tensDigit[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char *tens_power[] = {"hundred", "thousand"};

    printf("Enter a number : ");
    scanf("%s", a);

    int len = strlen(a);
    int num;
    //  for 1-9 digit
    if (len == 1)
    {
        num = a[0] - 48; //  a[0]== *a == *(a+0)  these all are same thing we get first value of a
        printf("digit is %s = %s", a, singleDigit[num]);
    }
    // for 10-19
    if (len == 2 && a[0] == 49)
    {
        num = (a[0] - 48) + (a[1] - 48);
        printf("digit is %s = %s", a, twoDigit[num]);
    }
    else if (len == 2 && a[1] == 48)
    {
        num = (a[0] - 48) + (a[1] - 48);
        printf("digit is %s = %s", a, tensDigit[num]);
    }
    else if (len == 2)
    {
        num = a[0] - 48;
        printf("%s ", tensDigit[num]);
        num = a[1] - 48;
        printf("%s", singleDigit[num]);
    }
    // for 100 - 999
    else if (len == 3)
    {

        // forThreeDigit(a);
        num = a[0] - 48;
        printf("%s %s ", singleDigit[num], tens_power[0]);
        //  for second digit
        if (a[1] == 49)
        {
            num = (a[1] - 48) + (a[2] - 48);
            printf("%s ", twoDigit[num]);
        }
        else if (a[1] == 48)
        {
            num = a[2] - 48;
            printf("%s ", singleDigit[num]);
        }
        else
        {
            num = a[1] - 48;
            printf("%s ", tensDigit[num]);
            num = a[2] - 48;
            printf("%s ", singleDigit[num]);
        }
    }
   else if(len==4){
         num = a[0] - 48;
        printf("%s %s ", singleDigit[num], tens_power[1]);
        forThreeDigit(a+1);
    }

}

int main(){
    numberToWord();
    return 0;
}


/// hiii
// bss karo abb

*/

#include<stdio.h>

void convert_number_to_words(int num) {
    if (num <= 0) {
        printf("Invalid number\n");
        return;
    }

    char *ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *thousands[] = {"", "thousand", "million", "billion", "trillion"};

    if (num < 10)
        printf("%s\n", ones[num]);
    else if (num < 20)
        printf("%s\n", teens[num - 10]);
    else if (num < 100) {
        printf("%s ", tens[num / 10]);
        if (num % 10 != 0)
            printf("%s\n", ones[num % 10]);
    } else if (num < 1000) {
        printf("%s hundred ", ones[num / 100]);
        if (num % 100 != 0)
            convert_number_to_words(num % 100);
    } else {
        convert_number_to_words(num / 1000);
        printf("%s ", thousands[(num / 1000) - 1]);
        if (num % 1000 != 0)
            convert_number_to_words(num % 1000);
    }
}

int main() {
    int num = 021;
    printf("%d in words: ", num);
    convert_number_to_words(num);
    return 0;
}

