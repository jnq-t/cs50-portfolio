#variables
string = input("Text: ")
words_raw=1
sentence_raw=0
letters_raw=len(string)

#gathering raw counts
for i in range(len(string)):
    if string[i]== " ":
        words_raw+=1
        letters_raw-=1
    if string[i]== "." or string[i] == "!" or string[i] == "?" :
        sentence_raw+=1
        letters_raw-=1
    elif string[i].isalpha() != True and string[i] != " " :
        letters_raw -=1
        
        
#computing index from raw counts
l= (letters_raw/words_raw)*100
s= (sentence_raw/words_raw)*100
index= round(0.0588 * l - 0.296 * s - 15.8)

#debugging print statement
#print(f"there are {words_raw} words and {sentence_raw} sentences and {letters_raw} letters")

#possible outcomes
if index > 16 :
    print("Grade 16+")
    quit()
if index < 1 :
    print("Before Grade 1")
    quit()
print(f"Grade {index}")