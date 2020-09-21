#pragma once
#include"Node.h"
#include<iostream>
#include<map>
#include<memory>
#include<iomanip>
#include<vector>
#include<queue>
using namespace std;

class Node;

template<class T>
struct PrioQueueAscending {
	bool operator()(const T &lhs, const T &rhs)const {
		return (lhs->GetDistanceCost() > rhs->GetDistanceCost());
	}
};

class NodeMap
{
public:

	map<int, map<int, shared_ptr<Node>>> NodeMapContainer;
	vector<shared_ptr<Node>> VisitedNodes;
	vector<Node*> Path;
	priority_queue<shared_ptr<Node>,vector<shared_ptr<Node>>, PrioQueueAscending<shared_ptr<Node>>> ScannedNodes;
	shared_ptr<bool> endNodeFound = make_unique<bool>(false);
	shared_ptr<bool> startNodeFound = make_unique<bool>(false);
	shared_ptr<Node> StartNode;
	shared_ptr<Node> EndNode;
	void DisplayMap()const;
	void ClearInput();
	static NodeMap& GetInstance(size_t size); // ensures only one instance possible
	void PlaceNode(shared_ptr<Node> &nodeToPlace);
	void TracePath();
	void Pathfind();
	void TurnPathIntoWall();
	void TestMap();

private:
	NodeMap(const size_t size);
	~NodeMap();
	const size_t MapSize;
};
