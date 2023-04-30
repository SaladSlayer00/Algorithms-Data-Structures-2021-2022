//Introduction

This project was assigned as final examination for the Algorithms and Data Structures (Algoritmi e principi dell'informatica) course in Politecnico di Milano. Its objective was examining the capabilities of students when managing the complexity of the code and the use of different known data structures.

It is evaluated considering the most efficient use of memory and time possible when accomplishing the given task.

//Description

The C language was used, given its memory management capabilities and lightweight computation.

The project involved creating a ranking of different direct weighted graphs, to find the shortest path between the reachable nodes. This is a useful algorithm that can find numerous applications, from networks to real-life mapping applications. 

The program always receives two parameters in input on the first row of the text file:

d: the number of nodes in the graphs.
k: the desired length of the ranking. d, k, and the number of graphs are representable with 32-bit integers.

The interface was made by the following operations:

"AggiungiGrafo" (AddGraph) followed by the adjacency matrix of a graph printed line by line with values separated by a comma.
"TopK": considering graphs from the start of the program until the TopK command, print the indices of the k graphs having the smallest value of the sum of the shortest path between the node 0 and all the other reachable nodes from 0 of the graph. 

If there are multiple graphs with the same metric value, priority is given to the ones that were added first. Distances of nodes that are not reachable from 0 are considered to be zero. The indices of the k graphs are printed on a single line, separated by a space, in any order.

//Implementation

To complete the task, I implemented:

Dijkstra's Algorithm, using a matrix as support when computing the selected metric on each graph.

A heap structure to keep track of the TopK graphs in an efficient way, and presenting the final list of candidate graphs.

I achieved the maximum score of 30/30 cum laude.


Documentation and testbenches can be found in the related folders.