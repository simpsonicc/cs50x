#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string number = get_string("Enter your credit card number: ");
    int len = strlen(number);

    int firsttwo;
    int first;
    int second;
    int sum = 0;
    int multipliedsum = 0;

     for (int i = len - 1, alt = 0; i >= 0; i--, alt++)
    {
        int digit = number[i] - '0';

        if ((alt % 2) == 1)
        {
            multipliedsum = digit * 2;
            sum += (multipliedsum / 10) + (multipliedsum % 10);
        }
        else
        {
            sum += digit;
        }
    }
    first = (number[0] - '0');
    second = (number[1] - '0');
    firsttwo = first * 10 + second;
    if (sum % 10 == 0)
    {
        if ((firsttwo == 34 || firsttwo == 37) && (len == 15))
        {
            printf("AMEX\n");
            return 0;
        }
        else if ((firsttwo >= 51 && firsttwo <= 55) && (len == 16))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if ((first == 4) && (len == 13 || len == 16))
        {
            printf("VISA\n");
            return 0;
        }
    }
    printf("INVALID\n");
}
