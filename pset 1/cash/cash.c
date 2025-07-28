#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change = get_int("how much change is remaining? ");
    while (change < 0)
    {
        printf("incorrect change enetered ");
        change = get_int("how much change is remaining? ");
    }

    int quarter = 0;
    int dime = 0;
    int nickel = 0;
    int pennies = 0;

    while (change >= 25)
    {
        change = change - 25;
        quarter += 1;
    }

    while (change >= 10)
    {
        change = change - 10;
        dime += 1;
    }
    while (change >= 5)
    {
        change = change - 5;
        nickel += 1;
    }
    pennies = change;

    printf("%i\n", quarter + dime + nickel + pennies);
}
