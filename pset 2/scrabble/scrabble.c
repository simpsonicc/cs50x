#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SCORES[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3,10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int index_1;
int index_2;
char *upper_1;
char *upper_2;
int sum_1 = 0;
int sum_2 = 0;

int main(void)
{
    char *word_1 = get_string("Player 1: ");
    char *word_2 = get_string("Player 2: ");

    int len_1 = strlen(word_1);
    int len_2 = strlen(word_2);

    upper_1 = malloc(len_1 * sizeof(char));
    upper_2 = malloc(len_2 * sizeof(char));

    for (int a = 0; a < len_1; a++)
    {
        upper_1[a] = toupper(word_1[a]);
    }
    for (int b = 0; b < len_2; b++)
    {
        upper_2[b] = toupper(word_2[b]);
    }

    for (int i = 0; i < len_1; i++)
    {
        if (upper_1[i] >= 'A' && upper_1[i] <= 'Z')
        {
            index_1 = upper_1[i] - 'A';
            sum_1 += SCORES[index_1];
        }
    }
    for (int j = 0; j < len_2; j++)
    {
        if (upper_2[j] >= 'A' && upper_2[j] <= 'Z')
        {
            index_2 = upper_2[j] - 'A';
            sum_2 += SCORES[index_2];
        }
    }

    if (sum_2 > sum_1)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else if (sum_2 < sum_1)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    printf("Tie\n");

    free(upper_1);
    free(upper_2);
}
