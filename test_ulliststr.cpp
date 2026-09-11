#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "ulliststr.h"

// Compare the whole list with the expected strings.
void check(const ULListStr& list,
           const std::vector<std::string>& expected)
{
    assert(list.size() == expected.size());
    assert(list.empty() == expected.empty());

    for (size_t i = 0; i < expected.size(); i++) {
        assert(list.get(i) == expected[i]);
    }

    if (!expected.empty()) {
        assert(list.front() == expected.front());
        assert(list.back() == expected.back());
    }
}

int main()
{
    ULListStr list;
    std::vector<std::string> expected;

    // Empty-list removals should do nothing.
    list.pop_front();
    list.pop_back();
    check(list, expected);

    // Fill multiple nodes from the back.
    for (int i = 0; i < 25; i++) {
        std::string value = std::to_string(i);
        list.push_back(value);
        expected.push_back(value);
        check(list, expected);
    }

    // Add enough at the front to create multiple new nodes.
    for (int i = 1; i <= 15; i++) {
        std::string value = std::to_string(-i);
        list.push_front(value);
        expected.insert(expected.begin(), value);
        check(list, expected);
    }

    // Test set() and the non-const get().
    list.set(12, "changed");
    expected[12] = "changed";
    list.get(13) = "edited";
    expected[13] = "edited";
    check(list, expected);

    // Invalid positions should throw.
    bool caught = false;
    try {
        list.get(list.size());
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);

    // Alternate removals until all nodes are deleted.
    while (!expected.empty()) {
        list.pop_front();
        expected.erase(expected.begin());
        check(list, expected);

        if (!expected.empty()) {
            list.pop_back();
            expected.pop_back();
            check(list, expected);
        }
    }

    // Push to the front of an empty list, then remove from back.
    list.push_front("single");
    expected.push_back("single");
    check(list, expected);

    list.pop_back();
    expected.clear();
    check(list, expected);

    // Push to the back of an empty list, then remove from front.
    list.push_back("single");
    expected.push_back("single");
    check(list, expected);

    list.pop_front();
    expected.clear();
    check(list, expected);

    // Reuse space after removing from either end.
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    list.pop_front();
    list.push_front("new a");
    list.pop_back();
    list.push_back("new c");
    expected = {"new a", "b", "new c"};
    check(list, expected);

    // Clear multiple nodes and reuse the list.
    for (int i = 0; i < 25; i++) {
        list.push_back("extra");
    }
    list.clear();
    expected.clear();
    check(list, expected);

    list.push_back("reused");
    expected.push_back("reused");
    check(list, expected);

    // Leave multiple nodes for the destructor to clean up.
    for (int i = 0; i < 25; i++) {
        list.push_back("cleanup");
        expected.push_back("cleanup");
    }
    check(list, expected);

    std::cout << "All custom tests passed!\n";
    return 0;
}
