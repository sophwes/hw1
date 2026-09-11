#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::push_back(const std::string& val)
{
    if (tail_ == NULL) {
        // Empty list: create its first node.
        Item* node = new Item();
        head_ = node;
        tail_ = node;
    }
    else if (tail_->last == ARRSIZE) {
        // No room after the tail's used values.
        Item* node = new Item();

        node->prev = tail_;
        tail_->next = node;
        tail_ = node;
    }

    // Append to the current tail.
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
}void ULListStr::push_front(const std::string& val)
{
    if (head_ == NULL) {
        // Empty list: create its first node.
        Item* node = new Item();
        node->first = ARRSIZE;
        node->last = ARRSIZE;

        head_ = node;
        tail_ = node;
    }
    else if (head_->first == 0) {
        // No room before the head's first value.
        Item* node = new Item();
        node->first = ARRSIZE;
        node->last = ARRSIZE;

        node->next = head_;
        head_->prev = node;
        head_ = node;
    }

    // Insert immediately before the first used slot.
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
}void ULListStr::pop_back()
{
    if (tail_ == NULL) {
        return;
    }

    tail_->last--;
    size_--;

    if (tail_->first == tail_->last) {
        // The tail node is now empty.
        Item* oldTail = tail_;
        tail_ = oldTail->prev;

        if (tail_ != NULL) {
            tail_->next = NULL;
        } else {
            // We removed the only node.
            head_ = NULL;
        }

        delete oldTail;
    }
}void ULListStr::pop_front()
{
    if (head_ == NULL) {
        return;
    }

    head_->first++;
    size_--;

    if (head_->first == head_->last) {
        // The head node is now empty.
        Item* oldHead = head_;
        head_ = oldHead->next;

        if (head_ != NULL) {
            head_->prev = NULL;
        } else {
            // We removed the only node.
            tail_ = NULL;
        }

        delete oldHead;
    }
}std::string const & ULListStr::front() const
{
    if (head_ == NULL) {
        throw std::out_of_range("List is empty");
    }

    return head_->val[head_->first];
}

std::string const & ULListStr::back() const
{
    if (tail_ == NULL) {
        throw std::out_of_range("List is empty");
    }

    return tail_->val[tail_->last - 1];
}std::string* ULListStr::getValAtLoc(size_t loc) const
{
    if (loc >= size_) {
        return NULL;
    }

    Item* current = head_;

    while (current != NULL) {
        size_t count = current->last - current->first;

        if (loc < count) {
            return &current->val[current->first + loc];
        }

        loc -= count;
        current = current->next;
    }

    return NULL;
}
void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
