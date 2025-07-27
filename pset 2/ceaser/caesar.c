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
    int len_1 = strlen(argv[1]);

    int key = atoi(argv[1]);
    for (int j = 0; j < len_1; j++)
    {
        if (!isdigit(argv[1][j]))
        {
            printf("Invalid key entered \n");
            return 1;
        }
    }
    if (key < 0)
    {
        printf("Invalid key entered \n");
        return 1;
    }

    int index;

    char *cipher_text;
    char *plain_text = get_string("Plain Text: ");
    int len = strlen(plain_text);
    cipher_text = malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        char cipher = plain_text[i];
        if (key > 26)
        {
            key = key % 26;
        }
        if (isalpha(cipher))
        {
            if (islower(cipher))
            {
                cipher_text[i] = (((cipher - 'a') + key) % 26) + 'a';
            }
            else if (isupper(cipher))
            {
                cipher_text[i] = (((cipher - 'A') + key) % 26) + 'A';
            }
        }
        else
        {
            cipher_text[i] = cipher;
        }
    }

    cipher_text[len] = '\0';
    printf("ciphertext: %s\n", cipher_text);

    free(cipher_text);
    return 0;
}
