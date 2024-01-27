#pragma once
#include<string>
#include<fstream>

#define BOUND 10000
class Parser;
class Reader {
public:
    Reader(std::ifstream& inputfile) : inputfileRef(inputfile) {
        std::cout << "inside Reader::Reader(ifstream&)\n";
        for (int i = 0; inputfile.good() && i < BOUND; i++) {
            buffer[i] = inputfile.get();
            length++;
        }
    }
    int printBuffer() {
        for (int i = 0; i < length; i++) { std::cout << buffer[i]; }
        return length;
    }
    ~Reader() {
        std::cout << "inside Reader::~Reader()\n";
        inputfileRef.close();
    }
private:
    friend class Parser;
    int length = 0;
    char buffer[BOUND];
    std::ifstream& inputfileRef;
};
