#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include <iostream>
using namespace std;

class Graph {
public:
	struct Node;
	//static unsigned int numberofnodes;

	Graph(string name_) : _id(name_) { //root = createNode(std::string("root"), 0);
		root = &rootNode;
	}
	Graph(unsigned int numnode_, string name_) : _id(name_) {
		root = &rootNode;
	}
	~Graph() { }

	unique_ptr<Node> createNode(std::string name, std::string value)
	{
		//numberofnodes++;
		//struct Node* node_ = new Node(name, value);
		unique_ptr<Node> node_ = make_unique<Node>(name, value);
		upn[numberofnodes++] = std::move(node_);

		return nullptr;
	}

	string getNodeID(shared_ptr<Node> node)
	{
		return node->getid();
	}
	string getNodeData(shared_ptr<Node> node)
	{
		return node->getdata();
	}
	int getnumnodes() {
		return numberofnodes;
	}
	string getGraphID() {
		
		return _id;
	}
	shared_ptr<Node> getNodePtr(int index) {
		std::shared_ptr<Node> spn = (upn[index]);
		return spn;
	}

	struct Node {
	public:
		Node() {
			id = "root", list.data = "";
		}
		Node(std::string name_, std::string val)
		{
			id = name_; list.data = val;
		}

		string getdata()
		{
			return this->list.data;
		}
		string getid()
		{
			return id;
		}

	private:
		struct List {
			string data;
			struct Graph::Node* prev;
			struct Graph::Node* next;

			List() {
				data = ""; prev, next = nullptr;
			}

			string getData() {
				return this->data;
			}
			void setNext(Node* next) {
				this->next = next;
			}
			void setData(int data) {
				this->data = data;
			}
		};
		struct List list;
		std::string id;
	};

private:
	struct Node* root;
	struct Node rootNode;
	unsigned int numberofnodes = 0;
	string _id;
	//Node* nodes[100] = { root };
	shared_ptr<Node> upn[100];
};

#endif
