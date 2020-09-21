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
	this->NodeMapContainer[nodeToPlace->GetNodeCoords().first][nodeToPlace->GetNodeCoords().second] = nodeToPlace;
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


void NodeMap::Pathfind() {
	this->StartNode->StartScan(*this);
	this->TracePath();
	this->DisplayMap();

	if (*this->endNodeFound == true) {
		cout << "Path drawn! type anything to continue: ";
	}
	else {
		cout << "No path found. type anything to continue: ";
	}
	ClearInput();
	cin.get();
	TurnPathIntoWall();
	ClearInput();
	this->DisplayMap();
}

void NodeMap::TracePath() {
	this->Path.emplace_back(this->EndNode->ParentNode);
	Node *PrevNode = 0;
	for (int i = 0; i < this->Path.size(); i++) {
		PrevNode = (*--this->Path.end());
		if (PrevNode != NULL && PrevNode->ParentNode != NULL && *this->startNodeFound == false && PrevNode->GetNodeType() == 1) {
			*this->startNodeFound = true;
			break;
		}
		else if (PrevNode != NULL && PrevNode->ParentNode != NULL){
			PrevNode->SetIcon('o');
			this->Path.emplace_back(PrevNode->ParentNode);
		}
	}
}

void NodeMap::TurnPathIntoWall() {
	vector<Node*> ::iterator transformNode;
	for (transformNode = this->Path.begin(); transformNode != this->Path.end(); transformNode++) {
		if ((*transformNode) != NULL && (*transformNode)->ParentNode != NULL && (*transformNode)->GetNodeType() == 1) {
			break;
		}
		else if ((*transformNode) != NULL && (*transformNode)->ParentNode != NULL && *this->endNodeFound == true) {
			(*transformNode)->SetIcon('X');
			(*transformNode)->SetNodeType(3);
			(*transformNode)->ParentNode->SetIcon('X');
			(*transformNode)->ParentNode->SetNodeType(3);
		}
	}
	for (auto &nodeToReset : this->Path) {
		if (nodeToReset != NULL) {
			nodeToReset->ResetNode();
		}
	}
	for (auto &nodeToReset : this->VisitedNodes) {
		if (nodeToReset != NULL) {
			nodeToReset->ResetNode();
		}
	}
	this->StartNode->SetIcon('X');
	this->StartNode->SetNodeType(3);
	this->StartNode->ParentNode = 0;
	this->StartNode->ResetNode();
	this->EndNode->SetIcon('X');
	this->EndNode->SetNodeType(3);
	this->EndNode->ParentNode = 0;
	this->EndNode->ResetNode();
	*this->endNodeFound = false;
	*this->startNodeFound = false;
	while (!this->ScannedNodes.empty()) {
		this->ScannedNodes.pop();
	}
	this->VisitedNodes.clear();
	this->Path.clear();

}

void NodeMap::TestMap() {
	this->NodeMapContainer.at(0).at(3)->SetNodeType(3);
	this->NodeMapContainer.at(0).at(3)->SetIcon('X');
	this->NodeMapContainer.at(1).at(3)->SetNodeType(3);
	this->NodeMapContainer.at(1).at(3)->SetIcon('X');
	this->NodeMapContainer.at(2).at(3)->SetNodeType(3);
	this->NodeMapContainer.at(2).at(3)->SetIcon('X');
	this->NodeMapContainer.at(3).at(3)->SetNodeType(3);
	this->NodeMapContainer.at(3).at(3)->SetIcon('X');
	this->NodeMapContainer.at(4).at(3)->SetNodeType(3);

	this->NodeMapContainer.at(4).at(3)->SetIcon('X');
	this->NodeMapContainer.at(4).at(2)->SetNodeType(3);
	this->NodeMapContainer.at(4).at(2)->SetIcon('X');
	this->NodeMapContainer.at(4).at(1)->SetNodeType(3);
	this->NodeMapContainer.at(4).at(1)->SetIcon('X');
}

void NodeMap::ClearInput() { // Clears buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores everything up to end of line.
}
