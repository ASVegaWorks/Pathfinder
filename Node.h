#pragma once
#include"NodeMap.h"
#include<iostream>
#include<vector>
#include<map>
#include<memory>
#include <thread>

using namespace std;

class NodeMap;

class Node 
{
public:
	Node() = default;
	Node(size_t rowNum, size_t columnNum, char icon, size_t nodeType);
	Node(const Node &source);
	Node(const Node &&source);
	~Node();
	char GetIcon()const;
	void SetIcon(char icon);
	void SetNodeType(size_t nodeType);
	void CalcDistances(const shared_ptr<Node> &endNode);
	void ScanAdjacents(map<int, map<int, shared_ptr<Node>>> &mapContainer);
	void ScanPath(NodeMap &map);
	void ResetNode();
	int GetDistanceCost()const;
	Node& operator=(const Node &rhs); // assignment operator overloaded
	pair<int,int> &GetNodeCoords();
	size_t GetNodeType()const;
	vector<shared_ptr<Node>> AdjacentNodes;
	vector<shared_ptr<Node>> DiagonalAdjacentNodes;
	bool pathScanned = false;
	bool isDiagonal = false;
private:
	int distanceCost = 0;
	int distanceToEnd = 0;
	int distanceToStart = 0;
	char icon;
	pair<int, int> locationCoords;
	int nodeType;
};

bool operator<(const shared_ptr<Node>lhs, const shared_ptr<Node> rhs);

