/*
* LRUCache.cpp
* -----------------
*
* Chapter 13 Question 4
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::list;
using std::random_device;
using std::pair;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

template <size_t capacity>
class LRUCache {
  public:
    bool Lookup(int isbn, int* price) {
      auto it = isbn_price_table_.find(isbn);
      if (it == isbn_price_table_.end()) {
        return false;
      }
      
      *price = it->second.second;
      MoveToFront(isbn, it); //since isbn is the most recently used 
      
      return true;
    }

    void Insert(int isbn, int price) {
      auto it = isbn_price_table_.find(isbn);

      if (it != isbn_price_table_.end()) {
        MoveToFront(isbn, it);
      } else {
        if (isbn_price_table_.size() == capacity) {
          //removes the least recently used ISBN to get space
          isbn_price_table_.erase(lru_queue_.back());
          lru_queue_.pop_back();
        }

        //adds new entry to the front
        lru_queue_.push_front(isbn);
        isbn_price_table_[isbn] = { lru_queue_.begin(), price };
      }
    }

    bool Erase(int isbn) {
      auto it = isbn_price_table_.find(isbn);
      if (it == isbn_price_table_.end()) {
        return false;
      }

      lru_queue_.erase(it->second.first);
      isbn_price_table_.erase(isbn);
      return true;
    }

  private:
    typedef unordered_map <int, pair<list<int>::iterator, int> > Table;

    void MoveToFront(int isbn, const Table::iterator& it) {
      lru_queue_.erase(it->second.first);
      lru_queue_.push_front(isbn);
      it->second.first = lru_queue_.begin();
    }

    Table isbn_price_table_;
    list<int> lru_queue_;
};

int main(int argc, char** argv) {  
  const int kCapacity = 2;

  LRUCache<kCapacity> c;
  cout << "c.Insert(1, 1)" << endl;
  c.Insert(1, 1);
  cout << "c.Insert(1, 10)" << endl;
  c.Insert(1, 10);
  int val;
  cout << "c.Lookup(2, val)" << endl;
  assert(!c.Lookup(2, &val));
  cout << "c.Lookup(1, val)" << endl;
  assert(c.Lookup(1, &val));
  assert(val == 1);
  c.Erase(1);

  // test capacity constraints honored, also FIFO ordering
  {
    LRUCache<kCapacity> c;
    c.Insert(1, 1);
    c.Insert(2, 1);
    c.Insert(3, 1);
    c.Insert(4, 2);
    int val;
    assert(!c.Lookup(1, &val));
    assert(!c.Lookup(2, &val));
    assert(c.Lookup(3, &val));
    assert(val == 1);
    assert(c.Lookup(4, &val));
    assert(val == 2);
  }

  // test retrieval moves to front
  {
    LRUCache<kCapacity> c;
    c.Insert(1, 1);
    c.Insert(2, 1);
    c.Insert(3, 1);
    int val;
    c.Lookup(2, &val);
    c.Insert(4, 1);
    assert(!c.Lookup(1, &val));
    assert(c.Lookup(2, &val));
    assert(val == 1);
    assert(!c.Lookup(3, &val));
    assert(c.Lookup(4, &val));
    assert(val == 1);
  }

  // test update moves to front
  {
    LRUCache<kCapacity> c;
    c.Insert(1, 1);
    c.Insert(2, 1);
    c.Insert(3, 1);
    c.Insert(2, 2);
    c.Insert(4, 1);
    int val;
    assert(!c.Lookup(1, &val));
    assert(c.Lookup(2, &val));
    assert(val == 1);
    assert(!c.Lookup(3, &val));
    assert(c.Lookup(4, &val));
    assert(val == 1);
  }

  // test remove
  {
    LRUCache<kCapacity> c;
    c.Insert(1, 1);
    c.Insert(2, 1);
    c.Erase(2);
    c.Insert(3, 3);
    int val;
    assert(c.Lookup(1, &val));
    assert(val == 1);
    assert(!c.Lookup(2, &val));
    assert(c.Lookup(3, &val));
    assert(val == 3);
  }


  assert(!c.Lookup(1, &val));
  return 0;
}
