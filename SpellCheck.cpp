/*
    Title: DoubleProbing.h
    Author: Vlad Shostak
    Created on: April 2, 2017
    Description: This is the main driver program to test the spell checking portion 
                 of the requirnment in the specification.
    Modifications:
    Notes:
*/
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleProbing.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
using namespace std;

// ./SpellCheck document1_short.txt wordsEn.txt



template <typename HashTableType>
void
printMisspelledWords(HashTableType &hash_table, const string &document_filename, const string &dictionary_filename) {

  cout << "TestFunctionForHashTables..." << endl;
  cout << "Document filename: " << document_filename << endl;
  cout << "Dictionary filename: " << dictionary_filename << endl;
  

  hash_table.MakeEmpty();
  hash_table.resetCollisions();

  ifstream document_file;
  document_file.open(document_filename.c_str());
  if (document_file.fail())
  {
    cerr << "Error opening document file\n";
  }

  ifstream dictionary_file;
  dictionary_file.open(dictionary_filename.c_str());
  if (dictionary_file.fail())
  {
    cerr << "Error opening dictionary file\n";
  }

  // ==================================

  string line;
  // store dictionary
  while(dictionary_file.good()) {
    getline(dictionary_file, line);
    hash_table.Insert(line);
  }

  bool skip = false; // use to skip apostrophised words

  // START check each word in document
  while(document_file >> line) {
    string letter = "";
    string word = "";
    // START get each word
    for (int i = 0; i < line.length(); i++) {

      letter = tolower(line[i]);
      if(letter == "\'") { 
          skip = true; // skip apostrophised words
        }

      if (  (letter >= "a" && letter <= "z" )  ) {
            word += letter;
      }
    }
    // END get each word
  

   // check word, 3 cases
   string newWord = word;
   if ( !skip && !hash_table.Contains(newWord)) {

       // 1) add one char in each possible position
       for(int i = 0; i < word.length() + 1; i++) {

            // insert a - z
            for (char ch = 'a';ch <= 'z'; ch++) {
                newWord.insert(i, 1, ch);
                
                if(hash_table.Contains(newWord)) {
                    cout << word << " -> " << newWord << endl;
                }
                newWord = word; // reset
                
            }
            
       }
       newWord = word;
       // 2) remove one character from the word
       for(int i = 0; i < word.length(); i++) {
            //  begins at the character position pos and spans len characters
            newWord.erase(i,1);
            if(hash_table.Contains(newWord)) {
                    cout << word << " -> " << newWord << endl;
            }
            newWord = word; // reset

       }
       // 3) Swap adjacent characters in the word
       for(int i = 0; i < word.length() - 1; i++) {
            //  begins at the character position pos and spans len characters
            swap(newWord[i], newWord[i+1]);
            if(hash_table.Contains(newWord)) {
                    cout << word << " -> " << newWord << endl;
            }
            newWord = word; // reset

       }
    } // end if
    skip = false;

  } // end while line
  // END check each word in document





document_file.clear();
document_file.close();
dictionary_file.clear();
dictionary_file.close();


}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <documentfilename> <dictionaryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    printMisspelledWords(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    printMisspelledWords(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    printMisspelledWords(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
