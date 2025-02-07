#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_character(string k, int l);

int main(int argc, string key[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int length = strlen(key[1]);

    if (length != 26 || check_character(key[1], length))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char plain_c = plaintext[i];
        if (isupper(plain_c))
        {
            printf("%c", toupper(key[1][plain_c - 65]));
        }
        else if (islower(plain_c))
        {
            printf("%c", tolower(key[1][plain_c - 97]));
        }
        else
        {
            printf("%c", plain_c);
        }
    }

    printf("\n");

    return 0;
}

int check_character(string k, int l)
{

    for (int j = 0; j < l; j++)
    {

        char c = tolower(k[j]);

        if (!isalpha(c))
        {
            return 1;
        }

        for (int v = 0; v < l; v++)
        {
            if (c == tolower(k[v]) && j != v)
            {
                return 1;
            }
        }
    }

    return 0;
}
