#pragma once

#include "order.hpp"
#include "singleengine.hpp"

#include <iostream>
#include <string>

using std::string;
using std::ostream;

class MatchEngine {
    SingleEngine _buyEngine;
    SingleEngine _sellEngine;
public:
    MatchEngine();
    void add(Order order);
    void exportToFile(string filename);

    const string to_string() const;

    friend ostream& operator << (ostream& os, const MatchEngine& obj);
};
