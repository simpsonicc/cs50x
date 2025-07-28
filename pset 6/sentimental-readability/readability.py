from cs50 import get_string

text_input = get_string("Text: ")

# used to convert input into  a list, split oop returs list
text = text_input.split()
letter_count = 0
sentence_count = 0

# len on list counts no of elements in it
word_count = len(text)

for letters in text_input:
    # checks if it is alphabet, could b capital or small
    if (letters.isalpha() == True):
        letter_count += 1
    if (letters == "." or letters == "?" or letters == "!"):
        sentence_count += 1


L = letter_count / word_count * 100
S = sentence_count / word_count * 100

grade = 0.0588 * L - 0.296 * S - 15.8
grade = round(grade)

if (grade < 1):
    print("Before Grade 1")

elif (grade >= 16):
    print("Grade 16+")

else:
    print(f"Grade {grade}")
