#include <iostream>
#include <fstream>
#include "parser.h"

using namespace std;

int main()
{
        ifstream inputfile("temp.txt");
        //Reader reader(inputfile);

        Parser p(inputfile);
        cout << "\n";
        p.printBuffer();
        string data = p.get("owner", "organization");

        cout << "\n" << data << "\n";
        return 0;
}
