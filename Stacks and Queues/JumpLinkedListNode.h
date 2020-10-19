#ifndef JUMP_LINKED_LIST_PROTOTYPE_H_
#define JUMP_LINKED_LIST_PROTOTYPE_H_

#include <memory>
#include <iostream> 

using namespace std;

using std::shared_ptr;

struct PostingListNode {
  int order;
  shared_ptr<PostingListNode> next, jump;
};
// @exclude

#endif
