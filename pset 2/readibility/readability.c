#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letters = 0;
int words = 0;
int sentences = 0;
float L = 0;
float S = 0;
float index;
int rounded;

int main(void)
{
    char *text = get_string("Text: ");
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        if (isspace(text[i]))
        {
            words += 1;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
                sentences += 1;
        }
    }
    words += 1;
    L = ((float) letters / ((float) words)) * 100;
    S = ((float) sentences / ((float) words)) * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;
    rounded = round(index);

    if (rounded < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (rounded >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", rounded);
}
