import sys
import csv
if len(sys.argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        quit()
def main():
    #opening file and printing for reference and debugging
    with open(sys.argv[2], 'r') as f:
        string = f.read()
    #print (string)
    f = open(sys.argv[1], 'r')
    reader = csv.reader(f)
    
    #make and populate dict with csv 
    people = {}
    for row in reader:
        key = row[0]
        i = 1
        people.setdefault(key, [])
        while i < len(row):
            people[key].append(row[i])
            i += 1
    f .close()
    #extract the subs from the dict
    for key in people:
        if key == "name":
            subs = (people[key])
    
    #create results array and populate it 
    results = []
    for sub in subs:
        temp = longest(string, sub)
        results.append(temp)
    #print(results)
    
    #compare results array to values in dict
    for key in people:
        if people[key] == results:
            print(key)
            return 
    print("No match")
    return
    
#main currently returns the longest instance of whatever is value is given the variable sub in the string referenced by the command line
def longest(string, sub):

    returns = repititions(string, sub, 0)
    longest = returns[0]
    while returns[1] + (returns[0] * len(sub)) < len(string):
        returns = repititions(string, sub, returns[1] + (returns[0]*len(sub)))
        if returns[0] > longest :
            longest = returns[0]
    return str(longest)


# returns a list with first value=found index , second value number of reps at index
# accepts string, substring, and index from which to begin looking
def repititions (string, sub, begin_index):
    index = string.find(sub, begin_index, len(string))
    if index < 0:
        #will terminate while loop on line 12
        return [0, len(string)]
    if index >= 0:
        repititions = recursive_find(string, sub, index+len(sub), index+(2 * len(sub)), 1)
        #print(f"{repititions} found and index {index}")
    return [repititions, index]


def recursive_find(string, sub, x, y, counter):
    true = string.find(sub, x, y)
    if true >= 0:
        counter += recursive_find(string, sub, x+len(sub), y+len(sub), counter)
    return counter

main()
