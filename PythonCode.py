from operator import delitem
import re
import string
import csv

# Reads Grocery.txt and creates frequency.dat with purchase frequences
# Intention is to call it only once at beginning of program
def cacheItems():
    # Open read and write files
    with open('CS210_PROJECT_THREE_INPUT_FILE.txt', 'r') as glist, open('frequency.dat', 'w', newline = '') as results:
        fieldnames = ['Item', 'Quantity']
        rdr = csv.reader(glist)
        wrt = csv.DictWriter(results, fieldnames = fieldnames, delimiter=" ")

        tabulator = []
        masterList = {}

        # Read rows and add them to a list of items
        for row in rdr:
            tabulator += row

        # Read list and add items to dict. If item already exists, increment total
        for x in tabulator:
            if x in masterList:
                masterList[x] += 1
            else:
                masterList[x] = 1

        # Write all items and quantities to frequency.dat, delimeted by space
        for x in masterList:
            wrt.writerow({
                'Item': x,
                'Quantity': masterList[x]
            })
    return 0

# Prints a simple divider
def printBorder():
    print("="*45)

# Reads from frequency.dat, forms dictionary, returns dictionary
# For use by functions only
def pullFrequency():
    masterList = {}

    with open('frequency.dat', 'r') as glist:
        rdr = csv.reader(glist, delimiter=" ")

        for row in rdr:
            masterList[row[0]] = row[1]

    return masterList

# Print purchase totals as a normal list
def printPurchases():
    masterList = pullFrequency()

    printBorder()
    print("           The Corner Grocer")
    print("           Daily Items Sold")
    printBorder()

    for x in masterList:
        print("{: >20} : {: <15}".format(x, masterList[x]))

    printBorder()
    return 0

# Prints purchase amount for user selected item
def itemSearch(choice):
    masterList = pullFrequency()

    printBorder()

    # Colors for error printing
    CRED = '\033[41m'
    CEND = '\033[0m'

    if choice.capitalize() in masterList:
        return int(masterList[choice.capitalize()])
    else:
        print(CRED + 'Sorry, that item cannot be found' + CEND)
        return -1
