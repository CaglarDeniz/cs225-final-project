# Final Project Proposal

## Leading Question
The users of the bitcoin trading platform “Bitcoin OTC” are all anonymous. However, a new user will likely want to know if the person that they are going to initiate a transaction with is trustworthy. We seek to create a tool that will rank users “trustworthiness” based on ratings that other users have made. Users will input the ID of a user and will be shown general information about that user such as how trustworthy they are, the trustworthiness of users that they have traded with and so on. We will also be able to input 2 separate user IDs and see the shortest path between them. This would be an interesting way to see how many “degrees of separation” exist between two users. Our group project aims toward creating a graph data structure on a trading community, and using algorithms on the data structure to yield unique and applicable information for the user.

## Dataset Acquisition and processing
We are acquiring our dataset from the Stanford Large Network Dataset Collection. We have chosen the “Bitcoin OTC” dataset which contains data on who-trusts-whom network of people trading Bitcoin on a platform called Bitcoin OTC. Member’s interactions are rated on a scale of -10 to +10 representing legitimacy and trust. The file is a CSV file so we just need to make a node class where each node would be a user and each edge would be a transaction/rating, then we would simply parse the file as a string. Some potential errors include the existence of repeated ratings value between users and how to correctly identify updated ratings, otherwise our shortest path calculation may be erroneous.

## Graph Algorithms
We propose to use a shortest path algorithm ,to estimate the trust relationship between two users who have not rated each other as well as calculating the degrees of separation within the network. The input to this method would be the unique identfiers of the intitial and we would calculate the set  with the highest trust rating overall. This algorithm would potentially be Dijkstra’s Algorithm with a probability of using the A*- Algorithm. We are aiming for a time complexity of at maximum O(V^2), where V are the connecting vertices which represent the rating between users. Our shortest path algorithm must also be altered, in order to minimize the number of vertices while simultaneously maximising the rating values which are traversed.


The second graph algorithm that we propose to use would be to find strongly connected components in the dataset. The entire data structure will be inputted, and the algorithm would present us with "trust-circles"  from which we can see if there are internal communities inside the network. Identification of the internal networks within the Bitcoin OTC trading Platform, will allow us to run compartmentalized algorithms and extract further information from the graph.

We expect to use the breadth-first search algorithm to see if two users are in the same connected component of our graph. We decided on BFS as a result of the size of our data structure, in addition to being unaware of the distrubution of the graph. Our inputs into this algorithm would be a start node and an end node. If these two nodes are connected somehow, a path can be determined as an output, otherwise we will have to deal with the disconnected components

## Timeline
About 4 weeks till deadline -  May 12
### Tasks:
Data acquisition <br>
Data processing <br>
Algorithms <br>
Production<br>
	-	Week 1: Data acquisition, Data processing  
	-	Week 2: Algorithms  
	- 	Week 3: Production  
	- 	Week 4: Ensuring everything is ready to go  
	
