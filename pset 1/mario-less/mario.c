#include <cs50.h>
#include <stdio.h>

void print_spaces (int a);
void print_row(int j);
int main(void)
{
    int num = get_int("enter height: ");
    while ( num <= 0)
    {
         printf("Enter Valid height");
         printf("\n");
         num = get_int("enter height: ");

    }

    for (int i=1; i<num+1; i++)
    {
        if (num-i >0)
        {
            print_spaces(num-i);
        }

        print_row(i);
    }
}
void print_row(int j)
{
    for (int no=0; no<j; no++)
    {
        printf("#");
    }
    printf("\n");
}

void print_spaces (int a)
{
    for (int b=0; b<a; b++)
    {
        printf(" ");
    }
}

