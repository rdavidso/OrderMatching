#include "order.hpp"

#include <string.h>
#include <sstream>
#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl;
using std::stringstream;
using boost::algorithm::trim;

Order::Order(string line) {
    string parsedLine[3];
    int inc = 0;
    char cstr[line.length()+1];

    strcpy(cstr, line.c_str());
    auto pch = strtok(cstr, ",");

    while (pch != NULL && inc < 3) {
        parsedLine[inc++] = string(pch);
        pch = strtok(NULL, ",");
    }

    init(parsedLine[0], parsedLine[1], parsedLine[2]);
}

const string
Order::to_string() const {
    stringstream buf;
    buf <<  (_buy ? "B" : "S") << "," << _symbol << "," << _price;
    return buf.str();
}

ostream&
operator << (ostream& os, const Order& obj) {
    return os << obj.to_string();
}

void
Order::parseBuy(string buySell) {
    if(buySell == "B") {
        _buy = true;
    } else if(buySell == "S") {
        _buy = false;
    } else {
        throw "Invalid Buy/Sell marker for ";
    }
}

void
Order::parseSymbol(string symbol) {
    _symbol = string(symbol);
    trim(_symbol);
    if(_symbol.length() == 0) {
        throw "Invalid symbol for ";
    }
}

void
Order::parsePrice(string price) {
    _price = strtod(price.c_str(), NULL);
    if(_price <= 0) {
        throw "Invalid price for ";
    }
}

void
Order::init(string buySell, string symbol, string price) {
    try {
        parseBuy(buySell);
        parseSymbol(symbol);
        parsePrice(price);
    } catch(const char* err) {
        throw err + buySell + "," + symbol + "," + price;
    }

    cout << "Accepted order " << *this << endl;
}
