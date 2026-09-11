/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"

#include "split.h"
#include <cassert>
#include <iostream>

int main()
{
    Node* in = nullptr;
    Node* odds = nullptr;
    Node* evens = nullptr;

    // Test 1: Empty input should leave all three lists empty.
    split(in, odds, evens);

    assert(in == nullptr);
    assert(odds == nullptr);
    assert(evens == nullptr);

    // Test 2: Sorted input with negatives, zero, and duplicates.
    // Input: -3 -> -2 -> 0 -> 1 -> 1 -> 4
    Node* n6 = new Node(4, nullptr);
    Node* n5 = new Node(1, n6);
    Node* n4 = new Node(1, n5);
    Node* n3 = new Node(0, n4);
    Node* n2 = new Node(-2, n3);
    Node* n1 = new Node(-3, n2);
    in = n1;

    split(in, odds, evens);

    assert(in == nullptr);

    // Expected odds: -3 -> 1 -> 1
    assert(odds == n1);
    assert(n1->next == n4);
    assert(n4->next == n5);
    assert(n5->next == nullptr);

    // Expected evens: -2 -> 0 -> 4
    assert(evens == n2);
    assert(n2->next == n3);
    assert(n3->next == n6);
    assert(n6->next == nullptr);

    // Check that node values were preserved.
    assert(n1->value == -3 && n2->value == -2);
    assert(n3->value == 0 && n4->value == 1);
    assert(n5->value == 1 && n6->value == 4);

    // Free each allocated node exactly once after testing.
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    std::cout << "All custom tests passed!\n";
    return 0;
}
