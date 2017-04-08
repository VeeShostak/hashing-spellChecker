/*
    Title: DoubleProbing.h
    Author: Vlad Shostak
    Created on: April 2, 2017
    Description: This is the specification(interface) together with the
        implementation (can seperate) for double hashing
    Modifications:
    Notes:
*/

#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>


// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();  
  
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  void resetCollisions() {
    num_collisions_ = 0;
  }

  int getNumCollisions() {
    return num_collisions_;
  }
  int getNumElements() {
    return current_size_;
  }
  int getSize() {
    return array_.size();
  }
// ================================================================
// private
// ================================================================

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    
  // VARIABLES
  std::vector<HashEntry> array_;
  size_t current_size_;

  mutable size_t num_collisions_;


  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  /* 
  FindPos(const HashedObj & x) const
  */
  size_t FindPos(const HashedObj & x) const {
    //size_t offset = 1;

    size_t offset = InternalHashSecond(x);
    size_t current_pos = InternalHash(x);
    
    

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {

      num_collisions_++;

      current_pos += offset;

      if (current_pos >= array_.size())
	       current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();

  }
  size_t InternalHashSecond(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return (191 - ( hf(x) )  % 191) % array_.size();
  }

};

#endif  // DOUBLE_PROBING_H
