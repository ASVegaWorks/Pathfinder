#pragma once
#include"Node.h"
#include<iostream>
#include<map>
#include<set>
#include<memory>
#include<iomanip>
using namespace std;

class Node;

class NodeMap
{
public:
	map<int, map<int, shared_ptr<Node>>> NodeMapContainer;
	shared_ptr<bool> found = make_unique<bool>(false);
	set<shared_ptr<Node>> PathDrawn;
	shared_ptr<Node> StartNode;
	shared_ptr<Node> EndNode;
	void DisplayMap()const;
	static NodeMap& GetInstance(size_t size); // ensures only one instance possible
	void PlaceNode(shared_ptr<Node> &nodeToPlace);
	void ScanNodeAdjacents();
private:
	NodeMap(const size_t size);
	~NodeMap();
	const size_t MapSize;
};

