#include "matchengine.hpp"

#include <list>
#include <unordered_map>
#include <fstream>
#include <sstream>

using std::stringstream;
using std::ofstream;
using std::cout;
using std::endl;

MatchEngine::MatchEngine() {
    _sellEngine = SingleEngine(true);
}

void
MatchEngine::add(Order order) {
    SingleEngine* actionEngine = order.buy() ? &_buyEngine : &_sellEngine;
    SingleEngine* searchEngine = order.buy() ? &_sellEngine : &_buyEngine;
    auto match = searchEngine->match(order);
    if(!match) {
        actionEngine->add(order);
    }
}

void
MatchEngine::exportToFile(string filename) {
    ofstream file;
    file.open(filename);
    if(file.is_open()) {
        file << _buyEngine << _sellEngine;
    } else {
        cout << "Problem writing to file " << filename << endl;
    }
    file.close();
}

ostream&
operator << (ostream& os, const MatchEngine& obj) {
    return os << obj.to_string();
}

const string
MatchEngine::to_string() const {
    stringstream buf;
    buf << "Buy Orders: " << endl << _buyEngine << endl << "Sell Orders:" << endl << _sellEngine;
    return buf.str();
}
