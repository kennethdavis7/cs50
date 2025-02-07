from cs50 import get_string
from math import floor

def check_sum(number):
    sum = 0
    for i in range(len(number) - 2, -1, -2):
        doubled = int(number[i]) * 2
        sum += floor(doubled / 10) + (doubled % 10)

    for j in range(len(number) - 1, -1, -2):
        sum += int(number[j])

    if(sum % 10 == 0):
        return True
    else:
        return False

number = get_string("Number: ")

if check_sum(number):
    first_two_digits = int(number[:2])  # Get the first two digits
    first_digit = int(number[0])  # Get the first digit

    if len(number) == 15 and (first_two_digits == 34 or first_two_digits == 37):
        print("AMEX")
    elif len(number) == 16 and 51 <= first_two_digits <= 55:
        print("MASTERCARD")
    elif (len(number) == 13 or len(number) == 16) and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")





