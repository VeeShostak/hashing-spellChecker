/*
    Title: DoubleProbing.h
    Author: Vlad Shostak
    Created on: April 2, 2017
    Description: This is the main driver program to test performance of the different hash functions
                outlined in the spicifcation.
    Modifications:
    Notes:
*/
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleProbing.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// test commands
// ./SpellCheck document1_short.txt wordsEn.txt quadratic
// ./CreateAndTestHash words.txt query_words.txt quadratic


template <typename HashTableType>
void
TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  

  hash_table.MakeEmpty();
  hash_table.resetCollisions();

  ifstream all_words_file;
  all_words_file.open(words_filename.c_str());
  if (all_words_file.fail())
  {
    cerr << "Error opening words file\n";
  }

    
    string line;
    while(all_words_file.good()) {
      getline(all_words_file, line);
      hash_table.Insert(line);

    }



  //hash_table.MakeEmpty();  
  //..Insert your own code

  cout << "Number of elements: " << hash_table.getNumElements() << endl;
  cout << "Size of hash table: " << hash_table.getSize() << endl;
  cout << "Load factor: " << (hash_table.getNumElements() / (double)hash_table.getSize()) << endl;

  cout << "Total collisions: " << hash_table.getNumCollisions() << endl;
  cout << "Avg. number of collisions: " << (hash_table.getNumCollisions()/(double)hash_table.getNumElements()) << endl;

  ifstream query_file;
  query_file.open(query_filename.c_str());
  if (query_file.fail())
  {
    cerr << "Error opening query file\n";
  }

  // =========================
  // part 2

  hash_table.resetCollisions();

  while(query_file.good()) {
      getline(query_file, line);
      if(hash_table.Contains(line)) {
        cout << line << " Found " << hash_table.getNumCollisions() + 1 << endl;
        hash_table.resetCollisions();
      } else {
        cout << line << " Not Found " << hash_table.getNumCollisions() + 1 << endl;
        hash_table.resetCollisions();
      }
  }


all_words_file.clear();
all_words_file.close();
query_file.clear();
query_file.close();



}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
