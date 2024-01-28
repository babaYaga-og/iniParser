# iniParser
Date: 27/01/2024  
Simple INI Parser written in C++.  
(Special thanks to the generous folks at discord who helped me when I faced numerous challenges.)
# Usage:
## Example:
 
```cpp
#include <iostream>
#include <fstream>
#include "parser.h"

using namespace std;

int main()
{
        ifstream inputfile("temp.txt");

        Parser p(inputfile);
        p.printBuffer();
        string data = p.get("some section", "someKey");
        return 0;
}
```
## TODO
1. Rewrite all of this and make it better
2. Fix Duplicate Key-Value pair handling (as of now it will print the last duplicate item in a given section)
3. ...other problems I find

