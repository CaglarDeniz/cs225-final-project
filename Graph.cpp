#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

Graph::Graph() { 
    outgoingEdges.resize(1) ; 
    incomingEdges.resize(1) ; 
}

Graph::Graph(vector<vector<Edge*>> inc, vector<vector<Edge *>> out) { 
    outgoingEdges.resize(out.size());
    incomingEdges.resize(inc.size()); 

    incomingEdges = inc;
    outgoingEdges = out;
}

Graph::~Graph() { 
    destroy_(); 
}

void Graph::resize(unsigned size) { 
    if(size <= getSize()) { 
        return;  
    } else { 
        outgoingEdges.resize(size+1); 
        incomingEdges.resize(size+1); 
    }
}

size_t Graph::getSize() const { 
    return outgoingEdges.size() - 1; 
}

void Graph::addEdge(vector<double> edge_data) {
    if(getSize() < edge_data[0] || getSize() < edge_data[1]) { 
        resize(std::max(edge_data[0], edge_data[1]));
    }
    Edge* outgoing = new Edge(edge_data[1], edge_data[2], edge_data[3],true) ; 
    Edge* incoming = new Edge(edge_data[0], edge_data[2], edge_data[3],false) ;

    outgoingEdges[edge_data[0]].push_back(outgoing) ; 
    incomingEdges[edge_data[1]].push_back(incoming) ; 
}

const vector<Edge*>& Graph::getInEdges(Node vertex) const { 
    return incomingEdges[vertex.getIndex()]; 
}

const vector<Edge*>& Graph::getOutEdges(Node  vertex)const { 
    return outgoingEdges[vertex.getIndex()]; 
}

void Graph::destroy_() { 
    for(auto& vector : incomingEdges ) { 
        for(auto& edge_ptr : vector) { 
            if(edge_ptr != nullptr)
                delete edge_ptr;
        }
        vector.clear() ; 
    }
    incomingEdges.resize(1);
    for(auto& vector : outgoingEdges ) { 
        for(auto& edge_ptr : vector) { 
            if(edge_ptr != nullptr) {
                delete edge_ptr; 
            }
        }
        vector.clear(); 
    }
    outgoingEdges.resize(1) ; 

    scc.clear() ; 
}

void Graph::clearGraph() { 
    destroy_(); 
}

void Graph::shallowCopy(vector<vector<Edge*> > inc , vector<std::vector<Edge*> > out ) { 
    outgoingEdges = out; 
    incomingEdges = inc; 
}

vector<int> Graph::bfsSearch(int startNode, int endNode) {
    vector<bool> visitedSet = vector<bool>(getSize() + 1, false);
    visitedSet[startNode] = true;
    
    std::queue<int> q;
    q.push(startNode);

    vector<int> path = vector<int>(getSize() + 1, -1); //fill the path with dummy values
    bool foundNode = false;
    while (!q.empty()) {
        int currentNode = q.front();      
        q.pop();
        
        vector<int> neighbors = getNeighbors(currentNode);
        for (int i = 0; i < (int) neighbors.size(); i++) {
            int neighbor = neighbors[i];
            if (!visitedSet[neighbor]) {
                q.push(neighbor);
                visitedSet[neighbor] = true;
                path[neighbor] = currentNode;
            }
        }
        if (currentNode == endNode) {
            foundNode = true;
            break;
        }
    }

    if (foundNode == false) {
        path = { -1 };
        return path;
    }
    vector<int> shortestPath = {endNode};
    int currentNode = endNode;
    for (unsigned i = 0; i < path.size(); i++) {
        if (i < path.size() - 1) {
        }
    }

    //backtracking step. Use the path vector to find the path we took
    while (currentNode != startNode) {
        int previousNode = path[currentNode];
        shortestPath.insert(shortestPath.begin(), previousNode);
        currentNode = previousNode;
    }
    return shortestPath;
}

vector<int> Graph::bfsTraversal(int startNode) {
    vector<bool> visitedSet = vector<bool>(getSize() + 1, false);

    std::queue<int> q;

    q.push(startNode);
    visitedSet[startNode] = true;
    vector<int> path = vector<int>(getSize() + 1, -1); //fill the path with dummy values

    while (!q.empty()) {
        int currentNode = q.front();      
        q.pop();
        
        vector<int> neighbors = getNeighbors(currentNode);
        for (int i = 0; i < (int) neighbors.size(); i++) {
            int neighbor = neighbors[i];
            if (!visitedSet[neighbor]) {
                q.push(neighbor);
                visitedSet[neighbor] = true;
                path[neighbor] = currentNode;
            }
        }
    }
    return path;
}

vector<int> Graph::comprehensiveBFSTraversal() {
    vector<bool> visitedSet = vector<bool>(getSize() + 1, false);
    vector<int> path = vector<int>(getSize() + 1, -1); //fill the path with dummy values
    int firstUnvisitedNode = findUnvisitedNode(visitedSet);
    while (firstUnvisitedNode != -1) {
        comprehensiveBFSHelper(visitedSet, path, firstUnvisitedNode);
        firstUnvisitedNode = findUnvisitedNode(visitedSet);
    }
    return path;
}

void Graph::comprehensiveBFSHelper(vector<bool>& visitedSet, vector<int>& path, int startNode) {

    queue<int> q;
    q.push(startNode);
    visitedSet[startNode] = true;
    //-2 used as sentinel value to indicate that a BFS traversal started at this node
    path[startNode] = -2;

    while (!q.empty()) {
        int currentNode = q.front();      
        q.pop();
        
        vector<int> neighbors = getNeighbors(currentNode);
        for (int i = 0; i < (int) neighbors.size(); i++) {
            int neighbor = neighbors[i];
            if (!visitedSet[neighbor]) {
                q.push(neighbor);
                visitedSet[neighbor] = true;
                path[neighbor] = currentNode;
            }
        }
    }
}

//returns -1 if there are no unvisited nodes left in the set
int Graph::findUnvisitedNode(vector<bool>& visitedSet) {
    for (unsigned i = 1; i < visitedSet.size(); i++) {
        //false is used to mark that a node has not yet been visited
        if (visitedSet[i] == false) {
            return i;
        }
    }
    return -1;
}

vector<int> Graph::getNeighbors(int originNode) {
    if (originNode >= (int) outgoingEdges.size() || originNode <= 0) {
        return vector<int>();
    }
    vector<Edge*> outEdges = outgoingEdges[originNode];

    vector<int> neighbors;
    for (unsigned i = 0; i < outEdges.size(); i++) {
        neighbors.push_back(outEdges[i]->getKeyNode());
    }

    return neighbors;
} 

pair<vector<int>, int> Graph::dijkstraSearch(int userOne, int userTwo) {
    pair<vector<int>, vector<int>> pathsAndDistances = dijkstraTraverse(userOne);
    vector<int>& paths = pathsAndDistances.first;
    vector<int>& distances = pathsAndDistances.second;
    vector<int> shortestPath = {userTwo};
    if(paths[userTwo] == -1) {
        shortestPath = {-1};
        return make_pair(shortestPath, -1);
    }

    //Backtracking step.
    int currentNode = userTwo;
    while (currentNode != userOne) { 
        int previousNode = paths[currentNode];
        shortestPath.insert(shortestPath.begin(), previousNode);
        currentNode = previousNode;
    }
    return make_pair(shortestPath, distances[userTwo]);
}

pair<vector<int>, vector<int>> Graph::dijkstraTraverse(int userOne) {
    vector<int> distances = vector<int> (getSize() + 1, numeric_limits<int>::max()); //use largest number as a place holder for infinity
    vector<bool> visitedSet = vector<bool> (getSize() + 1, false); 
    distances[userOne] = 0;
    vector<int> path = vector<int> (getSize() + 1, -1);

    //Custom compare function for our priority queue
    auto compare = [](UserToDist firstPair, UserToDist secondPair) {
        return firstPair.second > secondPair.second;
    };

    priority_queue<UserToDist, vector<UserToDist>, decltype(compare)> pQ(compare);
    pQ.push(make_pair(userOne, 0));

    while(!pQ.empty()) {
        int currentNode = pQ.top().first;
        pQ.pop();

        vector<int> neighbors = getNeighbors(currentNode);
        for (int i = 0; i < (int) neighbors.size(); i++) {
            int neighbor = neighbors[i];
            if (!visitedSet[neighbor]) {
                if (distances[neighbor] > distances[currentNode] + getDistance(currentNode, neighbor)) {
                    distances[neighbor] = distances[currentNode] + getDistance(currentNode, neighbor); 
                    path[neighbor] = currentNode;
                    pQ.push(make_pair(neighbor, distances[neighbor]));
                }
            }
        }
        visitedSet[currentNode] = true;
    }

    return make_pair(path, distances);
}




double Graph::predictRating(int userOne, int userTwo) {
    vector<int> neighbors = getNeighbors(userOne);
    int areDirectNeighbors = count(neighbors.begin(), neighbors.end(), userTwo);
    if (areDirectNeighbors != 0) {
        int distance = getDistance(userOne, userTwo);
        return 10 - distance;
    }

    pair<vector<int>, int> pathAndDist = dijkstraSearch(userOne, userTwo);
    vector<int>& path = pathAndDist.first;
    int& distance = pathAndDist.second;

    int edgeCount = path.size() - 1;
    double ratingPrediction = (double) distance / edgeCount;

    return 10 - ratingPrediction;
}

//Gets the distance while mapping the range [-10, 10] to [0, 20]. -10 is mapped to 20. -9 is mapped to 19, -8 is mapepd to 18 etc...
int Graph::getDistance(int userOne, int userTwo) {
    int offset = 10;
    vector<Edge*> edgesFromOne = outgoingEdges[userOne];
    vector<Edge*> edgesFromTwo = outgoingEdges[userTwo];
    int oneRatedTwo = -11; //Sentinel value for "unrated"
    for (int i = 0; i < (int) edgesFromOne.size(); i++) {
        if ((int) edgesFromOne[i]->getKeyNode() == userTwo) {
            oneRatedTwo = offset - edgesFromOne[i]->getRating(); 
        }
    }

    return oneRatedTwo;
}


void Graph::SCCAlgorithm() {
    std::vector<int>lowlink = vector<int>(getSize() + 1);
    std::vector<int>stack ; 
    std::vector<bool> visitedSetSCC = vector<bool>(getSize() + 1, false);
    int idNumber = 0 ;
    map<int,int> ids;
    int i = 0;
    for(auto& e : lowlink){
        e = i;
        i++;
    }
    
    for(unsigned i = 1 ; i < getSize() ; i++) { 
        if(getOutEdges(Node(i)).empty() && getInEdges(Node(i)).empty())
            continue ; 
        if(visitedSetSCC[i]) { 
            continue; 
        }
        else { 
            RecursiveDFS(i,idNumber,ids,stack,lowlink,visitedSetSCC) ; 
        }
    }

}

void Graph::RecursiveDFS(int curNode,int & idNumber, map<int,int>& ids,std::vector<int>& stack, std::vector<int> & lowlink,std::vector<bool>& visitedSetSCC) {
    ids[-1*curNode] = idNumber;
    ids[idNumber] = curNode;
    stack.push_back(idNumber);
    visitedSetSCC[curNode] = true;
    idNumber++;
    vector<int> nextNodes = getNeighbors(curNode);
        for(auto& neighbor : nextNodes) {
            if (visitedSetSCC[neighbor] == false) {
                RecursiveDFS(neighbor,idNumber,ids,stack,lowlink,visitedSetSCC);
            }
            auto it = find(stack.begin(),stack.end(),ids[-1*neighbor]);
            bool isStackElement = false;
            if (it != stack.end()) {
                isStackElement = true;
            }
            if (isStackElement) { 
                lowlink[ids[-1*curNode] ] = min(lowlink[ids[-1*curNode] ], lowlink[ids[-1*neighbor] ]);    
            }
        }
        // RETURN TO LOWLINK
        if(ids[-1 * curNode] == lowlink[ids[-1 * curNode]]) {
            std::vector<int> curr_scc; 
            for(auto it = stack.rbegin(); it != stack.rend(); ++it){
                curr_scc.push_back(ids[*it]);
                stack.pop_back();
                lowlink[*it] = ids[-1*curNode] ; 
                if(ids[-1*curNode] == *it ) { 
                    break ; 
                }
            }
            scc.push_back(curr_scc) ; 
        }
}

double Graph::averageRating(int user){
    int totalRating = 0;
    int count = 0;
    vector<Edge*> ratings = incomingEdges[user];
    if (user >= (int) incomingEdges.size() || user <= 0 || ratings.empty()) {
        return -11;
    }
    
    for(auto& e : ratings){
        if(e == nullptr)continue;
        else{
        totalRating = totalRating +e->getRating();
        count++;}
    }
    double averageRating = totalRating/count;
    return averageRating;
}
