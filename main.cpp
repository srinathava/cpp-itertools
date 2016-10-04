#include <vector>
#include <tuple>

#include "itertools.hpp"

#include "Node.hpp"

#include "NodeIterator.hpp"

int main()
{
    std::vector<int> range2;

    Node* head = nullptr;

    // Basic usage with a Node*
    for (Node* v: elements_of(head)) {
    
    }

    // Basic usage of zip(...)
    for (auto tuple: zip(elements_of(head), range2)) {
        Node* v = boost::get<0>(tuple);

        int idx = boost::get<1>(tuple);
    }

    // Same thing with const Node*
    const Node* const_head = nullptr;

    for (const Node* v: elements_of(const_head)) {
    
    }

    for (auto tuple: zip(elements_of(const_head), range2)) {
        const Node* v = boost::get<0>(tuple);

        int idx = boost::get<1>(tuple);
    }

    // Basic usage of enumerate(...)
    for (auto pair: enumerate(elements_of(head))) {
        Node* v;
        size_t counter;

        std::tie(v, counter) = pair;
    }

    return 0;
}
