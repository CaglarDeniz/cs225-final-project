#pragma once
#include "Edge.h"
#include "Node.h"
#include <vector>
#include <map>
using namespace std;

typedef pair<int, int> UserToDist;

class Graph {
    public:
        /**Empty Graph constructor. */
        Graph();

        /**Full constructor. Make a graph from an edge list of incoming edes and outgoing edges. */
        Graph(std::vector<std::vector<Edge *>> inc, std::vector<std::vector<Edge *>> out);
        
        /**Destructor to prevent memory leaks. */
        ~Graph();

        /**Given a node will return a vector of refrences to that node's outgoing edges. */
        const vector<Edge*>& getOutEdges(Node) const;
        
        /**Given a node will return a vector of refrences to that node's incoming edges. */
        const vector<Edge*>& getInEdges(Node) const;
       
        /**A function to clear a graph's contents. */
        void clearGraph();

        /**Resizes the outgoing and incoming edges vectors to the correct size to handle newSize number of nodes. */
        void resize(unsigned newSize);

        /**Returns the number of nodes in the graph. */
        size_t getSize() const;

        /**Given an Edge adds it to the graph. */
        void addEdge(std::vector<double> edge_data) ; 

        /**Copies the given edge vectors into the graph. */
        void shallowCopy(vector<std::vector<Edge*>>, vector<std::vector<Edge*>>);

        /**Given two users, returns a vector<int> to represent the shortest path between them. */
        vector<int> bfsSearch(int userOne, int userTwo);

        /**Given one user, returns a vector<int> of all paths to each node. This can be backtracked to get the shortest (edge number)
         * path from the input user to any other user. */
        vector<int> bfsTraversal(int userOne);

        /**Will run multiple bfsTraversals until the entire graph is visited. Works on disconnected graphs. Returns a vector<int> to
         * represnet the paths that can be backtracked to recover the them. */
        vector<int> comprehensiveBFSTraversal();

        /**Given two users, returns a pair with the pair.first being a vector<int> of the shortest path between them (high trust path)
         * and pair.second being the actual distance. */
        pair<vector<int>, int> dijkstraSearch(int userOne, int userTwo);

        /**Given one user, returns a vector<int> of all paths to each node. This can be backtracked to get the shortest
         * (weighted edge distance) path from the input user to any other user where a valid path exists. */
        pair<vector<int>, vector<int>> dijkstraTraverse(int userOne);

        /**This algorithm identifes all of the strongly connected components within the graph. Stores the result into the scc private variables. */
        void SCCAlgorithm();

        /**Given two users, uses dijkstraSearch to find the shortest trust path between them and the distance. Using these values
         * calculates a prediction of what userOne would rate userTwo. */
        double predictRating(int userOne, int userTwo);

        /**Given a user, averages all of the incoming edges to return an average rating value. */
        double averageRating(int user);

        /**Each inner vector represents one group of strongly connected components. The overall vector contains multiple of these. */
        vector<vector<int>> scc ;

    private:

        /**Private helper function for the destructor and "=" operator. */
        void destroy_();

        /**Private helper function used for various algorithms. Given a user, returns a vector<int> containing all of the outgoing
         * nodes from that user. */
        vector<int> getNeighbors(int user);

        /**Private helper function used for Dijkstras. Will get the distance from the first node to the second. This is the rating that
         * the first user gave the second user remapped to the range [0, 20]. */
        int getDistance(int first, int second);

        /**Private helper function used for comprehensiveBFS. Runs one full BFS traversal, This may be reran multiple times by
         * comprehensivesBFSTraversal depending on the number of disconnected components in the graph. */
        void comprehensiveBFSHelper(vector<bool>& visitedSet, vector<int>& path, int startNode);

        /**Private helper function for comprehensiveBFSTraversal. Given a vector<int> representing the visited set, returns the first
         * node that is still unvisited or -1 if all nodes have been visited. */
        int findUnvisitedNode(vector<bool>& visitedSet);

        /**Helper function for the SCCAlgorithm that recursively traverses the graph. */
        void RecursiveDFS(int curNode,int&, map<int,int>& id,std::vector<int>&,std::vector<int>&,std::vector<bool>&);

        /**Each inner vector contains pointers to the edges from the node at the corresponding index in the larger vector. */
        vector<vector<Edge*>> outgoingEdges;
        
        /**Each inner vector contains pointers to the edges to the node at the corresponding index in the larger vector. */
        vector<vector<Edge*>> incomingEdges;
        
};