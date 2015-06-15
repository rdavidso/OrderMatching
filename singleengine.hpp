#pragma once

#include <list>
#include <unordered_map>

#include "order.hpp"

using std::string;
using std::ostream;
using std::list;
using std::unordered_map;

class SingleEngine {
    unordered_map<string, list<Order>> _orders;
    bool _high;
public:
    SingleEngine();
    SingleEngine(bool high);
    void add(Order order);
    bool match(Order order);
    
    const string to_string() const;

    friend ostream& operator << (ostream& os, const SingleEngine& obj);
};
