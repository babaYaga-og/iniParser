#pragma once
#include <sstream>
#include <unordered_map>
#include "reader.h"
#include "graph.h"
#include "graphmaker.h"

#define BOUND 10000

class Parser {
public:
    Parser(std::ifstream& inputfile) : error(0) {
        //cout << "inside Parser::Parser(ifstream&)\n";
        Reader reader(inputfile);
        length = reader.length;
        for (int i = 0; i < reader.length; i++)
        {
            buffer[i] = reader.buffer[i];
            //std::cout << buffer[i]; 
        }
        error = parseBuffer();
    }

    int printBuffer() {
        for (int i = 0; i < length; i++) { 
            std::cout << buffer[i];
        }
        return length;
    }

    std::string get(std::string secn, std::string keyn) {

        std::string sectname = secn;
        std::string keytofind = keyn;
        std::string data;

        for (int i = 0; i < numberofsection; i++) {
            shared_ptr<Graph> currentgraph = upg[i + 1];
            string id = currentgraph->getGraphID();
            if (id == secn) {
                int numofnode = currentgraph->getnumnodes();

                for (int j = 0; j < numofnode; j++) {
                    string nodeid = currentgraph->getNodeID(currentgraph->getNodePtr(j));
                    if (nodeid == keyn) {
                       data = currentgraph->getNodeData(currentgraph->getNodePtr(j));
                        break;
                      // cout << data;
                    }
                }
            }
            else {
                continue;
            }
        }
        return data;
    }

    ~Parser() { 
       // cout << "\ninside Parser::~Parser()\n";
    }

private:
    shared_ptr<Graph> upg[100];
    //Graph* g[100] = { nullptr };
    int length;
    char buffer[BOUND];
    int error;
    unsigned int numberofsection = 0;
    int* sectionIndex;

    bool COMPLETE = false;
    int currentState = 0;
    
    GraphMaker gm;

    string findSections(unsigned int cursor, unsigned int next)
    {
        string buf;
        int length = next - cursor;
        stringstream ss;
        
            while (buffer[cursor] != ']')
            {
                ss << buffer[cursor]; // append(buffer[cursor]);
                buf = ss.str();
                length--;
                cursor++;
            }
           // std::cout << numberofsection;

            upg[numberofsection] = gm(buf);
        return buf;
    }

    std::unordered_map<std::string, std::string>
    findKeys (unsigned int cursor, unsigned int next)
    {
        string kbuf;
        string vbuf;
        int length = next - cursor;
        stringstream sk;
        
        bool keydone = false;

        while (length > 0) {
            
            if (buffer[cursor] != '=')
            {
                if (buffer[cursor] == ' ') {
                    length--;
                    cursor++;
                    continue;
                }
                else {
                    if (!keydone) {
                        sk << buffer[cursor]; // append(buffer[cursor]);
                        kbuf = sk.str();
                        length--;
                        cursor++;
                        continue;
                    }
                    else {
                        goto done;
                    }
                }
            }
            else if (buffer[cursor] != '\n' && buffer[cursor] != ' ')
            {  
                done:
                keydone = true;
                vbuf = findValues(cursor+1, length-1);
                break;
            }
            length--;
            cursor++;
        }
        std::unordered_map<std::string, std::string> kvPair = { {kbuf, vbuf} };

        upg[numberofsection]->createNode(kbuf, vbuf);
        return kvPair;
    }

    std::string findValues(unsigned int cursor, int length)
    {
        stringstream sv;
        string vbuf;

        while (length > 0) {
            if (buffer[cursor] != ' ') {
                if (buffer[cursor] == ';') {
                    break;
                }
                else {
                    sv << buffer[cursor]; // append(buffer[cursor]);
                    vbuf = sv.str();
                    length--;
                    cursor++;
                }
            }
            else {
                length--;
                cursor++;
            }
        }
        return vbuf;
    }
    std::string findComments(unsigned int cursor, int next)
    {
        string buf;
        int length = next - cursor;
        stringstream ss;

        while (buffer[cursor] != '\n')
        {
            ss << buffer[cursor]; // append(buffer[cursor]);
            buf = ss.str();
            
            cursor++;
        }
        return buf;
    }

    int parseBuffer() {

       /* for (int i = 0; i < length; i++)
        {
            cout << "buffer[" << i << "] = " << buffer[i] << "\n";
        }*/

        while (!COMPLETE)
        {
            unsigned int newlineindex[BOUND] = { 0 };
            unsigned int newlineindexCount = 0;

            for (unsigned int i = 0; i < BOUND; i++)
            {
                if (buffer[i] == '\n')
                {
                    newlineindex[++newlineindexCount] = i;
                   // cout << newlineindex[newlineindexCount] << "\n"; // success
                }
            }
            unsigned int totalLineNo = newlineindexCount;
            cout << "\ntotal number of lines = " << totalLineNo << "\n"; // success

            cout << "\n\n===============PARSED DATA==============\n";
            for (unsigned int i = 0; i <= totalLineNo; i++)
            {
                if (buffer[newlineindex[i]] == '[') {
                    numberofsection++;
                    cout << "init section: " << findSections(newlineindex[i] + 1, newlineindex[i + 1]) << "\n";
                }
                else if (buffer[newlineindex[i]] == ';') {
                    cout << "init comment: " << findComments(newlineindex[i] + 1, newlineindex[i + 1]) << "\n";
                }
                else if(buffer[newlineindex[i]+1] != ' ' && buffer[newlineindex[i]+1] != '\n') {

                    if (buffer[newlineindex[i] + 1] == ';') { continue; }
                    else if (buffer[newlineindex[i]+1] == '[') {
                        numberofsection++;
                        cout << "section: " << findSections(newlineindex[i] + 2, newlineindex[i + 1]) << "\n";
                    }
                    else {
                        std::unordered_map<std::string, std::string>
                            kvpair = findKeys(newlineindex[i] + 1, newlineindex[i + 1]);
                        auto print_key_value = [](const auto& key, const auto& value)
                            {
                                std::cout << "Key:" << key << " Value:" << value << "\n";
                            };
                        for (const std::pair<const std::string, std::string>& n : kvpair)
                            print_key_value(n.first, n.second);
                    }
                }
                else {
                }
            }
            cout << "\n===============PARSED DATA==============\n\n";
            COMPLETE = true;
        }
        if (COMPLETE) {
            cout << "\nnumber of sections = " << numberofsection << "\n";
        }

        return 0;
    }


};

