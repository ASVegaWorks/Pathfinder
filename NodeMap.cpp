#include "NodeMap.h"

NodeMap::NodeMap(const size_t size): MapSize(size*size)
{
	map<int, shared_ptr<Node>> InnerMap;
	for (size_t i = 0; i < sqrt(MapSize); i++) {
		for (size_t  j = 0; j < sqrt(MapSize); j++) {
			InnerMap.emplace(j, make_shared<Node>(i, j, '.', 0));
		}
		NodeMapContainer.emplace(i, move(InnerMap));
	}
}

NodeMap::~NodeMap()
{
}

NodeMap& NodeMap:: GetInstance(size_t size) {
	static NodeMap onlyInstance(size);
	return onlyInstance;
}

void NodeMap::PlaceNode(shared_ptr<Node> &nodeToPlace) {
	nodeToPlace->AdjacentNodes = move(this->NodeMapContainer[nodeToPlace->GetNodeCoords().first][nodeToPlace->GetNodeCoords().second]->AdjacentNodes);
	nodeToPlace->DiagonalAdjacentNodes = move(this->NodeMapContainer[nodeToPlace->GetNodeCoords().first][nodeToPlace->GetNodeCoords().second]->DiagonalAdjacentNodes);
	this->NodeMapContainer[nodeToPlace->GetNodeCoords().first][nodeToPlace->GetNodeCoords().second] = nodeToPlace;
	for (auto &node:nodeToPlace->AdjacentNodes)  {
		node->ScanAdjacents(this->NodeMapContainer);
	}
	for (auto &node : nodeToPlace->DiagonalAdjacentNodes) {
		node->ScanAdjacents(this->NodeMapContainer);
	}
}


void NodeMap::DisplayMap()const {

	for (int i = 0; i < this->NodeMapContainer.size(); i++) {

		int topNums = 0;
		while (topNums < this->NodeMapContainer.size() && i == 0) {
			cout<< right << setw(9) << topNums;
			topNums++;
		}
		if (i == 0) cout << "\n\n\n\n";
		cout << right << i  << setw(9); 
		for (int j = 0; j < this->NodeMapContainer.size(); j++) {
			cout << setw(9) << this->NodeMapContainer.at(i).at(j)->GetIcon() << setw(9);
		}
		cout << "\n\n\n";
	}
}

void NodeMap::ScanNodeAdjacents() {
	for (size_t i = 0; i < sqrt(MapSize); i++) {
		for (size_t j = 0; j < sqrt(MapSize); j++) {
			if (this->NodeMapContainer[i][j]->AdjacentNodes.empty()) {
				this->NodeMapContainer[i][j]->ScanAdjacents(this->NodeMapContainer);
			}
		}
	}
}