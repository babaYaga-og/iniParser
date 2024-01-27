#include <iostream>
#include <fstream>
#include "parser.h"

using namespace std;

int main()
{
        ifstream inputfile("temp.txt");

        Parser p(inputfile);
        p.printBuffer();
        //string data = p.get("some section", "someKey");
        return 0;
}
