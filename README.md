# Pathfinder
                                                By Alonso S. Vega 2020
                                                
Traces a path from start to end, similar to the A* algorithm.

  H cost: distance from current node to the end node.
  
  G cost: distance from current node to start node.
  
  F cost: G + H costs.

The coordinates for the start node are entered, then the end node. The shortest path will be searched from the start to end, and insert the searched nodes into the container, 'ScannedNodes', where it sorts them based on their F cost, least to greatest. After the end has been reached, the algorithm stops then backtracks through the nodes based on their parent node, marking them each as the 'o' character and stops until it has found the start node.
Next the path will turn into wall nodes marked as the 'X' character. The next path will treat 'X' as walls and will try to avoid them.
