#include <iostream>
#include <fstream>
#include <string.h>
#include <list>

#include "order.hpp"
#include "matchengine.hpp"

using std::ifstream;
using std::string;
using std::cout;
using std::endl;

void
processOrderFile(char* filename, MatchEngine& engine) {
    string line;
    ifstream file(filename);
    if(file.is_open()) {
        while(getline(file, line)) {
            try {
                Order order(line);
                engine.add(order);
            } catch(string err) {
                cout << err << endl;
            }
        }
        file.close();
    } else {
        cout << "Unable to open file " << filename << endl;
    }
}

int
main (int argc, char** argv) {
    if(argc < 2) {
        cout << "Please provide an input filename or an output filename and at least one valid input filename." << endl;
        return 1;
    }

    MatchEngine engine;
    string outputFileName = "export.txt";

    if(argc == 2) {
        processOrderFile(argv[1], engine);
    } else {
        outputFileName = argv[1];
        for(int i = 2; i < argc; i++) {
            processOrderFile(argv[i], engine);
        }
    }
    engine.exportToFile(outputFileName);
    
    cout << engine << endl;

    return 0;
}
