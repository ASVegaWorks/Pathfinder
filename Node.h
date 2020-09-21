#pragma once
#include"NodeMap.h"
#include<iostream>
#include<map>
#include<memory>
#include<queue>

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
	void StartScan(NodeMap &map);
	void ResetNode();
	int GetDistanceCost()const;
	pair<int,int> &GetNodeCoords();
	size_t GetNodeType()const;
	vector<shared_ptr<Node>> AdjacentNodes;
	Node* ParentNode = 0;


private:
	void ScanAdjacents(map<int, map<int, shared_ptr<Node>>> &mapContainer);
	void CalcDistances(const NodeMap &map);
	void RecursiveScan(NodeMap &map);
	bool isInOpenList = false;
	bool nodeVisited = false;
	bool isDiagonal = false;
	int distanceCost = 0; // F cost
	int distanceToEnd = 0; // H cost
	int distanceToStart = 0; //  G cost
	int nodeType;
	char icon;
	pair<int, int> locationCoords;
};

