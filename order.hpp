#pragma once

#include <string>
#include <iostream>

using std::ostream;
using std::string;

class Order {
    string _symbol;
    double _price;
    bool _buy;

    void init(string buySell, string symbol, string price);
    void parseBuy(string buySell);
    void parseSymbol(string symbol);
    void parsePrice(string price);
public:
    Order(string line);

    const string to_string() const;

    const string symbol() const { return _symbol; };
    const bool buy() const { return _buy; };
    const double price() const { return _price; };

    friend ostream& operator << (ostream& os, const Order& obj);
};
