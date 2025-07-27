#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Key Not entered\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Invalid key entered, it must be 26 characters long!");
        return 1;
    }

    char *key = argv[1];
    for (int j = 0; j < 26; j++)
    {
        if (!isalpha(key[j]))
        {
            printf("Invalid key entered, all the letter must be characters");
            return 1;
        }
        char letter = key[j];
        for (int k = 0; k < 25; k++)
        {
            if (k == j)
            {
                continue; // to skip that index
            }

            if (key[k] == toupper(letter) || key[k] == tolower(letter))
            {
                printf("All keys must be unique\n");
                return 1;
            }
        }
    }

    int index;
    char *cipher_text;
    char *plain_text = get_string("Plain Text: ");
    int len = strlen(plain_text);
    cipher_text = malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if (isupper(plain_text[i]))
        {
            index = plain_text[i] - 'A';
            cipher_text[i] = toupper(key[index]);
        }
        else if (islower(plain_text[i]))
        {
            index = plain_text[i] - 'a';
            cipher_text[i] = tolower(key[index]);
        }

        else
        {
            cipher_text[i] = plain_text[i];
        }
    }
    printf("ciphertext: %s\n", cipher_text);

    free(cipher_text);
    return 0;
}
