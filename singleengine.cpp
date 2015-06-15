#include "singleengine.hpp"

#include <sstream>

using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;

SingleEngine::SingleEngine() {
    _high = false;
}

SingleEngine::SingleEngine(bool high) {
    _high = high;
}

void
SingleEngine::add(Order order) {
    auto stored_val = _orders[order.symbol()];
    stored_val.push_back(order);
    _orders[order.symbol()] = stored_val;
}

bool
SingleEngine::match(Order order) {
    auto lst = _orders[order.symbol()];
    auto match = lst.end();

    for(auto it = lst.begin(); it != lst.end(); ++it) {
        if(_high) {
            if(order.price() >= it->price()) {
                match = match == lst.end() ? it : match->price() < it->price() ? match : it;
            }
        } else {
            if(order.price() <= it->price()) {
                match = match == lst.end() ? it : match->price() > it->price() ? match : it;
            }
        }
    }

    if(match != lst.end()) {
        cout << "Found match for " << order << " in " << *match << endl;
        lst.erase(match);
        _orders[order.symbol()] = lst;
        return true;
    }

    return false;
}

ostream&
operator << (ostream& os, const SingleEngine& obj) {
    return os << obj.to_string();
}

const string
SingleEngine::to_string() const {
    stringstream buf;
    for(auto kv : _orders) {
        for(auto order : kv.second) {
            buf << order << endl;
        }
    }
    return buf.str();
}
