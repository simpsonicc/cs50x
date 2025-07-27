from cs50 import get_int

height = get_int("height: ")

while (height <= 0 or height > 8):
    height = get_int("height: ")

spaces = height - 1
# range fuction like this checks, the second argument is not included, evenrything < second argument is.
for i in range(1, height + 1):
    # end="" prevents the print statent from going to the new line cos in pythin everytime u can print it adds a new line
    print(" " * spaces, end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
    spaces -= 1