from cs50 import get_string


def main():
    number = get_string("Enter your credit card number: ")
    length = len(number)

    firsttwo = 0
    first = 0
    second = 0
    sum = 0
    multipliedsum = 0
    # range (start, stop, step)
    for i in range(length - 1, -1, -1):
        alt = length - 1 - i
        # converts char into int
        digit = int(number[i])

        if ((alt % 2) == 1):

            multipliedsum = digit * 2
            # // used for integer divsion
            sum += (multipliedsum // 10) + (multipliedsum % 10)

        else:
            sum += digit
    first = int((number[0]))
    second = int((number[1]))
    firsttwo = first * 10 + second
    if (sum % 10 == 0):
        if ((firsttwo == 34 or firsttwo == 37) and (length == 15)):
            print("AMEX")
            return

        elif ((firsttwo >= 51 and firsttwo <= 55) and (length == 16)):
            print("MASTERCARD")
            return

        elif ((first == 4) and (length == 13 or length == 16)):
            print("VISA")
            return

    print("INVALID")


main()
