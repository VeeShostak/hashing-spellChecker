# Hashing-SpellChecker

NOTE: for the double hashing implementation, R = 191

### Compilation

You can compile everything by typing 

`make all`

You delete all .o files and executables by typing 

`make clean`

After compilation you can run each program from the terminal as follows:
```
CreateAndTestHash <words file name> <query words file name> <flag>
SpellCheck <document file> <dictionary file> <flag>
```


## Project Description

The goal of this assignment is to test three hashing implementations. You will also use your best hashing implementation for a simple spell-checker.
Test each hashing implementation as follows:

* A) Read all words from a given text file words.txt and insert them into a hash table. After the table is created print out the total number of elements in the table (N), the size of table (T), the load factor (N/T), the total number of collisions (C), and the average number of collisions (C/N).

* B) Check whether each word in another given file query_words.txt is in the hash table or not. For each word that is found print the word, the string “Found” and the number of probes used. For each word not found, print the word, the string “Not Found” and the number of probes used.

To implement the above, write a test program named CreateAndTestHash .
Your programs should run from the terminal as follows:

```CreateAndTestHash <words file name> <query words file name> <flag>```

<flag> should be “quadratic” for quadratic probing, “linear” for linear probing, and “double” for double hashing.

For example you can write on the terminal:
```CreateAndTestHash words.txt query_words.txt quadratic```

**Part 1**

Write code to implement quadratic and linear probing and test using CreateAndTestHash.

**Part 2**

Write code to implement double hashing and test using CreateAndTestHash. As the second hash function you can try the one described in the book: ```R – (x mod R)```where R is a prime smaller than table size. Try various values for R and keep the one that provides the best performance (i.e. smaller number of collisions).

**Part 3**

Now you are ready to implement a spell checker by using your favorite hash table. 

Given a document your program should output all of the misspelled words. For each misspelled word you should also provide a list of candidate corrections from the dictionary that can be formed by applying one of the following rules to the misspelled word:

* a) Adding one character in each possible position
* b) Removing one character from the word
* c) Swapping adjacent characters in the word

Your program should run as follows:
```SpellCheck <document file> <dictionary file>```
You will be provided with a small document named document1_short.txt (and document1.txt) and a dictionary file with approximately 100k words named wordsEn.txt.

As an example, the following mistakes should be corrected by your spell checker: 

```
comlete -> complete (case a)
deciasion -> decision (case b)
lwa -> law (case c)
```
Note that there may be other words in the document that are not in the dictionary due to the limited size and scope of the dictionary. You do not have to correct those misspellings.
