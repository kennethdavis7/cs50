#include <cs50.h>
#include <math.h>
#include <stdio.h>

int len(long n);
int check_visa(int digits, long credit, int l);
int check_ae(int digits, long credit, int l);
int check_mc(int digits, long credit, int l);
int check_sum(long credit, int l);

int main(void)
{
    long credit_number = get_long("Number: ");
    int length = len(credit_number);
    int start_digits = credit_number / (long) pow(10, length - 2);

    if (check_visa(start_digits, credit_number, length))
    {
        printf("VISA\n");
    }
    else if (check_ae(start_digits, credit_number, length))
    {
        printf("AMEX\n");
    }
    else if (check_mc(start_digits, credit_number, length))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int check_visa(int digits, long credit, int l)
{
    if (digits / 10 == 4 && check_sum(credit, l) && (l == 13 || l == 16))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_ae(int digits, long credit, int l)
{
    if ((digits == 34 || digits == 37) && check_sum(credit, l) && l == 15)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_mc(int digits, long credit, int l)
{
    if (check_sum(credit, l) && l == 16)
    {
        for (int v = 51; v <= 55; v++)
        {
            if (digits == v)
            {
                return 1;
            }
        }
    }

    return 0;
}

int check_sum(long credit, int l)
{
    int sum = 0;
    for (int i = 2; i <= l; i += 2)
    {
        int number = (credit % (long) pow(10, i)) / (long) pow(10, i - 1) * 2;
        int number_length = len(number);
        if (number_length == 2)
        {
            sum += (number % 10) + (number / 10);
        }
        else
        {
            sum += number;
        }
    }

    for (int j = 1; j <= l; j += 2)
    {
        int number = (credit % (long) pow(10, j)) / (long) pow(10, j - 1);
        sum += number;
    }

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int len(long n)
{
    return log10(n) + 1;
}
