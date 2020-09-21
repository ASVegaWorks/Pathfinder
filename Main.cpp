#include<iostream>
#include"NodeMap.h"
#include"Node.h"
#include<iomanip>
#include<vector>
#include<memory>

using namespace std;

void PlaceNodeInput(NodeMap &map);

int main() {

	size_t mapSize = 8;
	static NodeMap &PathMap =  NodeMap::GetInstance(mapSize);
	//PathMap.TestMap();
	PlaceNodeInput(PathMap);
	PathMap.ClearInput();
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
			map.Pathfind();
			nodeType = 1;
		}
		else if (coord1 < map.NodeMapContainer.size() && coord2 < map.NodeMapContainer.size() && map.NodeMapContainer[coord1][coord2]->GetNodeType() != 0) {
			map.DisplayMap();
			cout << "That space is occupied. \n";
}
		else  {
			map.DisplayMap();
			cout << "Invalid input. \n"; 
			map.ClearInput();
		}
	} while ( nodeType  <= 3);
}


