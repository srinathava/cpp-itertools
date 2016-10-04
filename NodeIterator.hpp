#pragma once

#include "Node.hpp"

// An adapter range class which can be instantiated with a Node pointer and
// allows us to iterate over all elements of that Node in a nice C++11
// range-based for loop style.
//
// This class is templatized to allow iteration over both a "Node*" and a
// "const Node*". 
//
// With a Node*, we get an iterator which gives us back Node* pointers
// which we can modify.
//
// With a "const Node*", we get back "const Node*" objects during the
// iteration which we cannot modify.
//
// This entire class is templatized by Node purely to account for the
// "Node*" vs "const Node*" constructor. It would be nice to not have to
// templatize it (so as to hide the details of the iteration algorithm).
template <typename Node>
struct ElementsOfRange
{
    ElementsOfRange(Node* n)
        : m_node(n)
    {}

    // It is important to define all 4 template parameters for
    // std::iterator here. The default value for the last one causes a very
    // strange compiler error.
    struct iterator: public std::iterator<std::forward_iterator_tag, Node*, ptrdiff_t, Node**, Node*>
    {
        iterator(Node* n)
            : m_node(n)
        { }

        bool operator!=(const iterator& other) const
        {
            return m_node != other.m_node;
        }

        bool operator==(const iterator& other) const
        {
            return m_node == other.m_node;
        }

        iterator& operator++()
        {
            m_node = m_node->next;
            return *this;
        }

        Node* operator*() const
        {
            return m_node;
        }

        Node* m_node;
    };

    iterator begin() const { return iterator(m_node); }

    iterator end() const { return iterator(nullptr); }

    Node* m_node;
};

// Free functions which make it a bit nicer to use the ElementsOfRange
// without having to specify template arguments.
ElementsOfRange<Node> elements_of(Node* n)
{
    return ElementsOfRange<Node>(n);
}

ElementsOfRange<const Node> elements_of(const Node* n)
{
    return ElementsOfRange<const Node>(n);
}


