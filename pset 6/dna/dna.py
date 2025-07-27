import csv
import sys


def main():

    # TODO: Check for command-line usage
    # sys is a list that stores command line sys.argv stores the list of arguments provided, u can apply len function on it to see no of arguments provided
    if (len(sys.argv) != 3):
        print("python dna.py database/filename sequence/filename")
        sys.exit()
    # TODO: Read database file into a variable
    database = []
    filename = sys.argv[1]
    # add with before opening a file cos even if u forget to close it, it will close it for you
    with open(filename, 'r') as file1:
        # The csv.DictReader is used to read CSV files into a dictionary format in rows
        # file1.read reads from the file as a variable
        data = csv.DictReader(file1)
        for i in data:
            # writes everything in the list of database
            database.append(i)

    # TODO: Read DNA sequence file into a variable
    sample = sys.argv[2]
    with open(sample, 'r') as file2:
        sampledata = file2.read()

    # TODO: Find longest match of each STR in DNA sequence

     # [1: ] will return from one and onwards
    subsequence = list(database[0].keys())[1:]

    result = {}
    for j in subsequence:
        # j is the key and the value returned by longest_match will be its value
        result[j] = longest_match(sampledata, j)

    # TODO: Check database for matching profiles
    for person in database:
        match = 0
        for z in subsequence:
            # z is the key 
            if int(person[z]) == result[z]:
                match += 1

        # if every subsequence matches its a pefect match
        if match == len(subsequence):
            print(person['name'])
            return

    print("No Match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
