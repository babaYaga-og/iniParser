#pragma once
#include <memory>
#include "graph.h"

class GraphMaker {
public:

	GraphMaker()  { }

	~GraphMaker() { }
	std::unique_ptr<Graph> operator()(std::string& name)
	{
		return make_unique<Graph>(name);
	}

	/*Graph* operator()(std::string& name) //causes memory leak
	{
		g = new Graph(name);
		return g;
	} */ 

private:
	//unique_ptr<Graph> upg;
	//Graph* g;

};
