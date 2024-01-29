// exceptions_try_except_Statement.cpp
// Example of try-except and try-finally statements
#include <stdio.h>
#include <windows.h> // for EXCEPTION_ACCESS_VIOLATION
#include <excpt.h>

int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
    puts("in filter.");
    if (code == EXCEPTION_ACCESS_VIOLATION)
    {
        puts("caught AV as expected.");
        return EXCEPTION_EXECUTE_HANDLER;
    }
    else
    {
        puts("didn't catch AV, unexpected.");
        return EXCEPTION_CONTINUE_SEARCH;
    };
}
#include <iostream>
#include <fstream>
#include "parser.h"
#include <ctime>
#include <chrono>

using namespace std;

int main()
{
    long double start = time(nullptr);

    unsigned long cstart =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::microseconds(1);

    auto ret = [&]() {

        ifstream inputfile("temp.txt");
        Parser p(inputfile);
        cout << "\n";
        //p.printBuffer();
        string data = p.get("owner", "name");
        cout << "\n" << data << "\n";
    };
        __try{
            ret();
        }
        __except (filter(GetExceptionCode(), GetExceptionInformation()))
        {
            cout << "in except\n";
        }
        unsigned long cend =
            std::chrono::system_clock::now().time_since_epoch() /
            std::chrono::microseconds(1);
        cout << "elasped time: " << cend - cstart;
        return 0;
}
