/*
* HuffmanEncoding.cpp
* -----------------
*
* Chapter 18 Question 1
*/

#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::function;
using std::make_unique;
using std::priority_queue;
using std::unique_ptr;
using std::random_device;
using std::shared_ptr;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

const double kEnglishFreq[] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749,  7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360,  0.150, 1.974, 0.074};


struct Symbol {
  char c;
  double prob;
  string code;
};

struct BinaryTreeNode {
  double prob;
  Symbol* s;
  shared_ptr<BinaryTreeNode> left, right;
};


struct Compare{
  bool operator()(const shared_ptr<BinaryTreeNode>& rhs,
                const shared_ptr<BinaryTreeNode>& lhs) {
    return lhs->prob > rhs->prob;
  }
};

void AssignHuffmanCode(const shared_ptr<BinaryTreeNode>& node, const string& s, 
                        unordered_map<char, string>* encoding) {
  if (node) {
    //if node is leaf (contains symbol)
    if (node->s) {
      node->s->code = s;
      (*encoding)[node->s->c] = s;
    } else {
      cout << (node->right != nullptr) << endl;
      //AssignHuffmanCode(node->left, s + "0", encoding);
      AssignHuffmanCode(node->right, s + "1", encoding);
    }
  }
}

unordered_map<char, string> HuffmanEncoding(vector<Symbol> symbols) {
  priority_queue<shared_ptr<BinaryTreeNode>, vector<shared_ptr<BinaryTreeNode> >, Compare> min_heap;

  for (auto& s : symbols) {
    shared_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(BinaryTreeNode({s.prob, &s, nullptr, nullptr}));
    min_heap.push(node);
  }

  while (min_heap.size() > 1) {
    shared_ptr<BinaryTreeNode> l = min_heap.top();
    min_heap.pop();
    shared_ptr<BinaryTreeNode> r = min_heap.top();
    min_heap.pop();
    min_heap.push(make_unique<BinaryTreeNode>(BinaryTreeNode({l->prob + r->prob, nullptr, l, r})));
  }

  unordered_map<char, string> huffman_encoding;

  AssignHuffmanCode(min_heap.top(), string(), &huffman_encoding);

  return huffman_encoding;
}

int main(int argc, char** argv) {   
  
  vector<Symbol> symbols;
  double prob_sum = 0;
  for (int i = 0; i < sizeof(kEnglishFreq)/sizeof(kEnglishFreq[0])  ; i++) {    
    Symbol test = {(char) ('a' + i), kEnglishFreq[i]};
    symbols.push_back(test);
  }

  auto encoding = HuffmanEncoding(symbols);

  for (auto& it : encoding) {
    cout << it.first << " " << it.second << endl;
  } 

  return 0;
}


