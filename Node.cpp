#include "Node.h"

Node::Node(size_t rowNum, size_t columnNum, char icon, size_t nodeType): icon(icon), nodeType(nodeType)
{
	locationCoords.first = rowNum;
	locationCoords.second = columnNum;
	this->AdjacentNodes.reserve(8);
	//cout << "Node constructed" <<endl;
}

Node::~Node()
{
	this->ResetNode();
	cout << "Node destroyed" << endl;
}

Node::Node(const Node &source) {
	cout << "Node copied" << endl;
	this->icon = source.icon;
	this->nodeType = source.nodeType;
	this->locationCoords = source.locationCoords;
	this->AdjacentNodes = source.AdjacentNodes;
	this->distanceToStart = source.distanceToStart;
	this->distanceToEnd = source.distanceToEnd;
	this->distanceCost = source.distanceCost;
	this->isDiagonal = source.isDiagonal;
	this->ParentNode = source.ParentNode;
}

Node::Node( const Node &&source) {
	this->icon = source.icon;
	this->nodeType = source.nodeType;
	this->locationCoords = source.locationCoords;
	this->AdjacentNodes = source.AdjacentNodes;
	this->distanceToStart = source.distanceToStart;
	this->distanceToEnd = source.distanceToEnd;
	this->distanceCost = source.distanceCost;
	this->isDiagonal = source.isDiagonal;
	this->ParentNode = source.ParentNode;
	cout << "Node moved" << endl;
}

void Node::ScanAdjacents(map<int, map<int, shared_ptr<Node>>> &mapContainer) {
	int coord1 = this->locationCoords.first; // row
	int coord2 = this->locationCoords.second; // column

	this->AdjacentNodes.clear();
		if ((coord1 - 1) >= 0 && mapContainer[coord1 - 1][coord2]->GetNodeType() != 3) { // Top of node
			this->AdjacentNodes.emplace_back(mapContainer[coord1 - 1][coord2]);
			mapContainer[coord1 - 1][coord2]->isDiagonal = false;
		}
		if ((coord1 + 1) < mapContainer.size() && mapContainer[coord1 + 1][coord2]->GetNodeType() != 3){ // Underneath of node
			this->AdjacentNodes.emplace_back(mapContainer[coord1 + 1][coord2]);
			mapContainer[coord1 + 1][coord2]->isDiagonal = false;
		}
		if ((coord2 - 1) >= 0 && mapContainer[coord1][coord2 - 1]->GetNodeType() != 3) { // Leftside of node
			this->AdjacentNodes.emplace_back(mapContainer[coord1][coord2- 1]);
			mapContainer[coord1][coord2 - 1]->isDiagonal = false;
		}
		if ((coord2 + 1) < mapContainer.size() && mapContainer[coord1][coord2 + 1]->GetNodeType() != 3) { // Leftside of node
			this->AdjacentNodes.emplace_back(mapContainer[coord1][coord2 + 1]);
			mapContainer[coord1][coord2 + 1]->isDiagonal = false;
		}
		 // Corners

		if ((coord1 - 1) >= 0 && (coord2 - 1) >= 0 && mapContainer[coord1 - 1][coord2 - 1]->GetNodeType() != 3) { // TL
			this->AdjacentNodes.emplace_back(mapContainer[coord1 - 1][coord2 - 1]);
			mapContainer[coord1 - 1][coord2 - 1]->isDiagonal = true;
		}
		if ((coord1 - 1) >= 0 &&  (coord2 + 1) < mapContainer.size() && mapContainer[coord1 - 1][coord2 + 1]->GetNodeType() != 3) { // TR
			this->AdjacentNodes.emplace_back(mapContainer[coord1 - 1][coord2 + 1]);
			mapContainer[coord1 - 1][coord2 + 1]->isDiagonal = true;
		}
		if ((coord1 + 1) < mapContainer.size() && (coord2 - 1) >= 0 && mapContainer[coord1 + 1][coord2 - 1]->GetNodeType() != 3) { // BL
			this->AdjacentNodes.emplace_back(mapContainer[coord1 + 1][coord2 - 1]);
			mapContainer[coord1 + 1][coord2 - 1]->isDiagonal = true;
		}
		if ((coord1 + 1) < mapContainer.size() && (coord2 + 1) < mapContainer.size() && mapContainer[coord1 + 1][coord2 + 1]->GetNodeType() != 3) { // BR
			this->AdjacentNodes.emplace_back(mapContainer[coord1 + 1][coord2 + 1]);
			mapContainer[coord1 + 1][coord2 + 1]->isDiagonal = true;
		}
}

void Node::CalcDistances(const NodeMap &map) { 
	pair<int, int>thisNodeCoords = this->GetNodeCoords();
	pair<int, int>startNodeCoords = map.StartNode->GetNodeCoords();
	pair<int, int>endNodeCoords = map.EndNode->GetNodeCoords();

	this->distanceCost = 0;
	this->distanceToEnd = 0;
	this->distanceToStart = 0;

	// From this node to end node
	int A = (thisNodeCoords.first - endNodeCoords.first) * 100; // larger the number, the more accurate
	int B = (thisNodeCoords.second - endNodeCoords.second) * 100;
		if (A < 0) {
			A = A * (-1);
		}
		if (B < 0) {
			B = B * (-1);
		}
	A = A * A; B = B * B;
	int C = sqrt(A + B);
	//int C = A + B; // uncomment for manhattan distance calculation,  comment out pythogrean calculation.
	this->distanceToEnd = C;

	// From this node to start node
	int E =  (thisNodeCoords.first - startNodeCoords.first);
	int F =	 (thisNodeCoords.second - startNodeCoords.second);
		if (E < 0) {
			E = E * (-1);
		}
		if (F < 0) {
			F = F * (-1);
		}
	E = E * E; F = F * F;
	int G = sqrt(E + F);
	this->distanceToStart = G;

	this->distanceCost = (this->distanceToEnd + this->distanceToStart);

}

void Node::StartScan(NodeMap &map) {
	map.StartNode->ScanAdjacents(map.NodeMapContainer);
	map.StartNode->CalcDistances(map);
	for (auto &adjacentNode : this->AdjacentNodes) {
		if (adjacentNode->GetNodeType() != 3) {
			adjacentNode->CalcDistances(map);
			adjacentNode->ParentNode = map.StartNode.get();
			adjacentNode->isInOpenList = true;
			map.ScannedNodes.emplace(adjacentNode);
		}
	}
	map.VisitedNodes.emplace_back(map.StartNode);

	this->RecursiveScan(map);
}

void Node::RecursiveScan(NodeMap &map) {

	shared_ptr<Node> NextNode = 0;
	
	while (!map.ScannedNodes.empty()) {

		NextNode = map.ScannedNodes.top();

		if (NextNode != NULL && NextNode->GetNodeType() == 2 && *map.endNodeFound == false) {
			*map.endNodeFound = true;
			map.EndNode->ParentNode = NextNode->ParentNode;
			map.VisitedNodes.emplace_back(map.EndNode);
			return;
		}
		else if (NextNode != NULL && NextNode->GetNodeType() == 0 && *map.endNodeFound == false) {

			NextNode->nodeVisited = true;
			NextNode->isInOpenList = false;

			map.VisitedNodes.emplace_back(NextNode);

			map.ScannedNodes.pop();

			NextNode->ScanAdjacents(map.NodeMapContainer);

			for (auto &nextNodeAdjacents : NextNode->AdjacentNodes) {
				nextNodeAdjacents->CalcDistances(map);
			}

			for (auto &nextNodeAdjacents : NextNode->AdjacentNodes) {
				if (nextNodeAdjacents->isInOpenList == false && nextNodeAdjacents->nodeVisited == false && nextNodeAdjacents->GetNodeType() != 1
					&& nextNodeAdjacents->GetNodeType() != 3) {
					nextNodeAdjacents->isInOpenList = true;
					nextNodeAdjacents->ParentNode = NextNode.get();
					map.ScannedNodes.emplace(nextNodeAdjacents);
				}
			}
		}
	}
}

 void Node::ResetNode() {
	 for (auto &adjacentNode : this->AdjacentNodes) {
		 adjacentNode->isDiagonal = false;
		 adjacentNode->distanceCost = 0;
		 adjacentNode->distanceToEnd = 0;
		 adjacentNode->distanceToStart = 0;
		 adjacentNode-> ParentNode = 0;
		 adjacentNode-> isInOpenList = false;
		 adjacentNode->nodeVisited = false;
	 }
	 this->ParentNode = 0;
	 this->isDiagonal = false;
	 this->isInOpenList = false;
	 this->nodeVisited = false;
	 this-> distanceCost = 0;
	 this-> distanceToEnd = 0;
	 this-> distanceToStart = 0;
	 this->AdjacentNodes.clear();
 }

 void Node::SetNodeType(size_t nodeType) {
	 this->nodeType = nodeType;
 }

 size_t Node::GetNodeType()const {
	 return this->nodeType;
 }

 void Node::SetIcon(char icon) {
	 this->icon = icon;
 }

 char Node::GetIcon()const {
	 return icon;
 }

 pair<int, int> &Node::GetNodeCoords() {
	 return this->locationCoords;
 }

 int  Node::GetDistanceCost()const {
	 return this->distanceCost;
 }
