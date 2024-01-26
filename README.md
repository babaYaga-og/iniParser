# iniParser  
Simple INI Parser written in C++.  
# Usage  
## Example  
I still have some work to do so this code will not work for now...  
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
        //string data = p.get("some section", "someKey");
        return 0;
}
```
##TODO
1. Rewrite all of this and make it better
2. idk yet

