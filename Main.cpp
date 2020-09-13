#include<iostream>
#include"NodeMap.h"
#include"Node.h"
#include<iomanip>
#include<sstream>
#include<vector>
#include<memory>
using namespace std;

void PlaceNodeInput(NodeMap &map);
void Pathfind(NodeMap &map);
void TurnPathIntoWall(NodeMap &map);
void TestMap(NodeMap &map);
void ClearInput();

int main() {

	size_t mapSize = 8;
	static NodeMap &PathMap =  NodeMap::GetInstance(mapSize);
	PlaceNodeInput(PathMap);
}
/*Node types:
0 = empty space
1 = start node
2 = end node
3 = block node 
*/

void PlaceNodeInput(NodeMap &map) {
	size_t  coord1, coord2 = 0;
	char nodeType = 1;
	TestMap(map);
	map.DisplayMap();
	do {
		if (nodeType == 1) {
			cout << "Enter the starting node's coordinates seperated by a space: ";
		}
		else if (nodeType == 2) {
			cout << "Enter the ending node's coordinates seperated by a space: ";
		}
		coord1, coord2 = 0;
		cin >> coord2 >> coord1;

		if ( coord1 < map.NodeMapContainer.size() && coord2 < map.NodeMapContainer.size() && nodeType == 1 && map.NodeMapContainer[coord1][coord2]->GetNodeType() == 0) {
			map.StartNode = make_shared <Node>(coord1, coord2, 'S', nodeType);
			map.PlaceNode(map.StartNode);
			map.DisplayMap();
			cout << "Start node placed at: " << coord1 << "," << coord2 << "\n";
			nodeType = 2;
		}
		else if (coord1 < map.NodeMapContainer.size() && coord2 < map.NodeMapContainer.size() && nodeType == 2 && map.NodeMapContainer[coord1][coord2]->GetNodeType() == 0) {
			map.EndNode = make_shared <Node>(coord1, coord2, 'E', nodeType);
			map.PlaceNode(map.EndNode);
			map.DisplayMap();
			cout << "End node placed at: " << coord1 << "," << coord2 << "\n";
			Pathfind(map);
			nodeType = 1;
		}
		else if (coord1 < map.NodeMapContainer.size() && coord2 < map.NodeMapContainer.size() && map.NodeMapContainer[coord1][coord2]->GetNodeType() != 0) {
			map.DisplayMap();
			cout << "That space is occupied. \n";
}
		else  {
			map.DisplayMap();
			cout << "Invalid input. \n"; 
			ClearInput();
		}
	} while ( nodeType  <= 3);
}

void ClearInput() { // Clears buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores everything up to end of line.
}

void Pathfind(NodeMap &map) {
	map.StartNode->StartScan(map);
	map.DisplayMap();
	
	if (*map.found == true) {
		cout << "Path drawn! type anything to continue: ";
	}
	else {
		cout << "No path found. type anything to continue: ";
	}
	ClearInput();
	cin.get();
	TurnPathIntoWall(map);
	ClearInput();
	map.DisplayMap();
}

void TurnPathIntoWall(NodeMap &map) {
	for (auto &node : map.PathDrawn) {
		node->SetIcon('X');
		node->SetNodeType(3);
		node->ResetNode();
	}
	map.StartNode->SetIcon('X');
	map.StartNode->SetNodeType(3);
	map.StartNode->ParentNode = 0;
	map.EndNode->SetIcon('X');
	map.EndNode->SetNodeType(3);
	map.EndNode->ParentNode = 0;
	*map.found = false;
	map.StartNode = 0;
	map.EndNode = 0;
	map.PathDrawn.clear();
}

void TestMap(NodeMap &map) {
	map.NodeMapContainer.at(0).at(3)->SetNodeType(3);
	map.NodeMapContainer.at(0).at(3)->SetIcon('X');
	map.NodeMapContainer.at(1).at(3)->SetNodeType(3);
	map.NodeMapContainer.at(1).at(3)->SetIcon('X');
	map.NodeMapContainer.at(2).at(3)->SetNodeType(3);
	map.NodeMapContainer.at(2).at(3)->SetIcon('X');
	map.NodeMapContainer.at(3).at(3)->SetNodeType(3);
	map.NodeMapContainer.at(3).at(3)->SetIcon('X');
	map.NodeMapContainer.at(4).at(3)->SetNodeType(3);

	map.NodeMapContainer.at(4).at(3)->SetIcon('X');
	map.NodeMapContainer.at(4).at(2)->SetNodeType(3);
	map.NodeMapContainer.at(4).at(2)->SetIcon('X');
	map.NodeMapContainer.at(4).at(1)->SetNodeType(3);
	map.NodeMapContainer.at(4).at(1)->SetIcon('X');
}
