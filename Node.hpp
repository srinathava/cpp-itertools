#pragma once

/// INPUT: An example class outside our control which does not offer any of
/// the niceties of C++11 like an internal iterator etc to make iterating
/// over it easy.
struct Node
{
    Node* next;
};
