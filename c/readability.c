#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string t);
int count_words(string t);
int count_sentences(string t);

int main(void)
{
    string text = get_string("Text: ");

    float L = (count_letters(text) / (float) count_words(text)) * 100.0;
    float S = (count_sentences(text) / (float) count_words(text)) * 100.0;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string t)
{
    int letters = 0;
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (isalpha(t[i]))
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string t)
{
    int words = 1;
    for (int j = 0, n = strlen(t); j < n; j++)
    {
        if (isblank(t[j]))
        {
            words++;
        }
    }

    return words;
}

int count_sentences(string t)
{
    int sentences = 0;
    for (int v = 0, n = strlen(t); v < n; v++)
    {
        if (t[v] == '.' || t[v] == '!' || t[v] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}
