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
        //p.printBuffer();
        //int data = p.get("this is a section", "key1");

        //int charsRead = reader.printBuffer();
        //cout << "\nTotal Chars Read: " << charsRead;

        cout << "\n";
        return 0;
}