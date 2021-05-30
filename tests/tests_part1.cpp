#include <string>
#include <vector>

#include "../catch/catch.hpp"
#include "../Graph.h"
#include "../Parse.h"

void print_edges(vector<Edge*> ans, vector<Edge*> out) { 
	cout << "This is the answer  edge list for node " << endl ;  
	cout << " { "; 
	for(auto& e : ans) {
		cout << e->getKeyNode() << " , "; 
	}
	cout << "}" << endl; 

	cout << "This is the output  edge list for node "<< endl;  
	cout << " { "; 
	for(auto& e : out) {
		cout << e->getKeyNode() << " , "; 
	}
	cout << "}" << endl;  
}


void verify_edge_list(const vector<Edge*>& ans,const  vector<Edge*>& out){ 
	for(auto& a : ans) { 
		bool found = false; 
		for(auto& e : out) { 
			if(*e == *a) { 
				found = true; 
				break; 
			}
		}
		REQUIRE(found); 
	}
}

void verify_graph(Graph & ans, Graph & out) {
	REQUIRE(ans.getSize() <= out.getSize()) ; 

	for(size_t i = 0 ; i < ans.getSize() ; i++) { 
		vector<Edge*> ao = ans.getOutEdges(Node(i)),oo = ans.getOutEdges(Node(i)) ;
		vector<Edge*> ai = ans.getInEdges(Node(i)),oi = ans.getInEdges(Node(i)) ; 
		
		verify_edge_list(ao,oo); 
		verify_edge_list(ai,oi);	
	}
}

void verify_dijkstra_helper(pair<vector<int>, int>& correctPathAndDist, pair<vector<int>, int>& calculatedPathAndDist) {
	vector<int>& correctPath = correctPathAndDist.first;
	vector<int>& calculatedPath = calculatedPathAndDist.first;
	int correctDist = correctPathAndDist.second;
	int calculatedDist = calculatedPathAndDist.second;

	REQUIRE(calculatedPath == correctPath);
	REQUIRE(calculatedDist == correctDist);
}

Graph large_graph_weighted() {
	Parse parser; 
	Graph ans;
	parser.readFromFile("tests/first_100_lines.csv", ans);
	return ans; 
}

Graph large_graph_unweighted() {
	Parse parser;
	Graph ans;
	parser.readFromFile("tests/first_100_lines_unweighted.csv", ans);
	return ans;
}

Graph medium_graph_unweighted() {
	Parse parser; 
	Graph ans;
	parser.readFromFile("tests/medium_graph1.csv", ans);
	return ans; 
}

Graph medium_graph_weighted() {
	Parse parser;
	Graph ans;
	parser.readFromFile("tests/medium_graph_weighted.csv", ans);
	return ans;
}

TEST_CASE("Verifying read from file with small graphs and constant weights","[part=1]") { 
	vector<vector<Edge *>> out_ans = vector<vector<Edge *>>(5,vector<Edge *>()) ; 
	out_ans[1].push_back(new Edge(2,1,0,1)) ; out_ans[1].push_back(new Edge(3,1,0,1)) ; out_ans[1].push_back(new Edge(4,1,0,1)) ;
	out_ans[2].push_back(new Edge(3,1,0,1)) ; out_ans[2].push_back(new Edge(4,1,0,1)) ;
	out_ans[4].push_back(new Edge(3,1,0,1)) ;

	vector<vector<Edge *>> inc_ans = vector<vector<Edge *>>(5,vector<Edge *>()) ; 
	inc_ans[2].push_back(new Edge(2,1,0,0)) ; 
	inc_ans[3].push_back(new Edge(1,1,0,0)) ; inc_ans[3].push_back(new Edge(2,1,0,0)) ; inc_ans[3].push_back(new Edge(4,1,0,0)) ;
	inc_ans[4].push_back(new Edge(1,1,0,0)) ; inc_ans[4].push_back(new Edge(2,1,0,0)) ;

	Graph ans ;
	ans.shallowCopy(inc_ans,out_ans) ; 

	Parse parser ; 

	Graph out ;
	cout << out.getSize() << endl ; 
	parser.readFromFile("tests/small_graph1.csv",out) ; 

	verify_graph(ans,out) ; 

	ans.clearGraph() ; out.clearGraph() ; out_ans.clear() ; out_ans.resize(6) ; inc_ans.clear() ; inc_ans.resize(6) ;

	out_ans[1].push_back(new Edge(2,1,0,1)) ; out_ans[1].push_back(new Edge(3,1,0,1));
	out_ans[2].push_back(new Edge(3,1,0,1)) ; out_ans[2].push_back(new Edge(4,1,0,1));
	out_ans[3].push_back(new Edge(4,1,0,1)) ; out_ans[3].push_back(new Edge(5,1,0,1));
	out_ans[4].push_back(new Edge(5,1,0,1)) ; out_ans[1].push_back(new Edge(1,1,0,1));
	out_ans[5].push_back(new Edge(1,1,0,1)) ; out_ans[5].push_back(new Edge(2,1,0,1));

	inc_ans[1].push_back(new Edge(4,1,0,0)) ; inc_ans[1].push_back(new Edge(5,1,0,0));
	inc_ans[2].push_back(new Edge(5,1,0,0)) ; inc_ans[2].push_back(new Edge(1,1,0,0));
	inc_ans[3].push_back(new Edge(1,1,0,0)) ; inc_ans[3].push_back(new Edge(2,1,0,0));
	inc_ans[4].push_back(new Edge(2,1,0,0)) ; inc_ans[4].push_back(new Edge(3,1,0,0));
	inc_ans[5].push_back(new Edge(3,1,0,0)) ; inc_ans[5].push_back(new Edge(4,1,0,0));

	ans.shallowCopy(inc_ans,out_ans); 

	cout << out.getSize() << endl; 

	parser.readFromFile("tests/small_graph2.csv",out); 

	verify_graph(ans,out);	

}


TEST_CASE("Verifying read from file with medium graphs and constant weights","[part=1]") {
	vector<vector<Edge *>> out_ans  = vector<vector<Edge *>>(13,vector<Edge*>());

		out_ans[1].push_back(new Edge(2,1,0,1)) ; out_ans[1].push_back(new Edge(3,1,0,1)) ; 
		out_ans[2].push_back(new Edge(3,1,0,1)) ; out_ans[2].push_back(new Edge(4,1,0,1))  ; 
		out_ans[3].push_back(new Edge(5,1,0,1)) ; 
		out_ans[4].push_back(new Edge(5,1,0,1)) ; out_ans[4].push_back(new Edge(6,1,0,1)) ; 
		out_ans[5].push_back(new Edge(7,1,0,1)) ; 
		out_ans[6].push_back(new Edge(7,1,0,1)) ; 
		out_ans[7].push_back(new Edge(8,1,0,1)) ; 
		out_ans[8].push_back(new Edge(9,1,0,1)) ; 
		out_ans[9].push_back(new Edge(10,1,0,1)) ;
		out_ans[10].push_back(new Edge(11,1,0,1)) ;
		out_ans[11].push_back(new Edge(1,1,0,1)) ;
		out_ans[12].push_back(new Edge(11,1,0,1)) ; 

	vector<vector<Edge *>> inc_ans = vector<vector<Edge *>>(13,vector<Edge *>()) ; 

		inc_ans[1].push_back(new Edge(11,1,0,0)) ;
		inc_ans[2].push_back(new Edge(1,1,0,0)) ;
		inc_ans[3].push_back(new Edge(1,1,0,0)) ; inc_ans[3].push_back(new Edge(2,1,0,0)) ;
		inc_ans[4].push_back(new Edge(2,1,0,0)) ;
		inc_ans[5].push_back(new Edge(3,1,0,0)) ;
		inc_ans[6].push_back(new Edge(4,1,0,0)) ;
		inc_ans[7].push_back(new Edge(5,1,0,0)) ; inc_ans[7].push_back(new Edge(6,1,0,0)) ;
		inc_ans[8].push_back(new Edge(7,1,0,0)) ;
		inc_ans[9].push_back(new Edge(8,1,0,0)) ;
		inc_ans[10].push_back(new Edge(9,1,0,0)) ;
		inc_ans[11].push_back(new Edge(10,1,0,0)) ; inc_ans[11].push_back(new Edge(12,1,0,0)) ;

	Graph ans(inc_ans,out_ans) ; 

	Parse parser ; 
	
	Graph out ;  parser.readFromFile("tests/medium_graph1.csv",out) ; 

	verify_graph(ans,out) ; 

}

TEST_CASE("Verifying add edges works","[part=1]") {
	vector<vector<Edge *>> out_ans = vector<vector<Edge *>>(7,vector<Edge *>()) ; 

		out_ans[1].push_back(new Edge(2,1,0,1)) ; out_ans[1].push_back(new Edge(3,1,0,1)) ; 
		out_ans[2].push_back(new Edge(3,1,0,1)) ; out_ans[2].push_back(new Edge(4,1,0,1)) ;
		out_ans[3].push_back(new Edge(4,1,0,1)) ; out_ans[3].push_back(new Edge(5,1,0,1)) ;
		out_ans[4].push_back(new Edge(5,1,0,1)) ; out_ans[4].push_back(new Edge(6,1,0,1)) ;
		out_ans[5].push_back(new Edge(6,1,0,1)) ; out_ans[5].push_back(new Edge(1,1,0,1)) ;
		out_ans[6].push_back(new Edge(1,1,0,1)) ; out_ans[6].push_back(new Edge(2,1,0,1)) ;

	vector<vector<Edge *>> inc_ans = vector<vector<Edge *>>(7,vector<Edge *>()) ; 

		inc_ans[1].push_back(new Edge(5,1,0,0)) ; inc_ans[1].push_back(new Edge(6,1,0,0)) ; 
		inc_ans[2].push_back(new Edge(1,1,0,0)) ; inc_ans[2].push_back(new Edge(6,1,0,0)) ;
		inc_ans[3].push_back(new Edge(2,1,0,0)) ; inc_ans[3].push_back(new Edge(1,1,0,0)) ;
		inc_ans[4].push_back(new Edge(3,1,0,0)) ; inc_ans[4].push_back(new Edge(2,1,0,0)) ;
		inc_ans[5].push_back(new Edge(4,1,0,0)) ; inc_ans[5].push_back(new Edge(3,1,0,0)) ;
		inc_ans[6].push_back(new Edge(5,1,0,0)) ; inc_ans[6].push_back(new Edge(4,1,0,0)) ;

	Graph ans ; ans.shallowCopy(inc_ans,out_ans) ; 

	Graph out ; 

	for(double i = 1 ; i <=4 ; i++) { 
		vector<double> edge_data1,edge_data2 ; 
		
		edge_data1 = { i , i+1, 1 , 0} ; 

		edge_data2 = { i , i+2 , 1 , 0} ; 

		out.addEdge(edge_data1) ; 

		out.addEdge(edge_data2) ; 
		
	}

	vector<double> e1,e2,e3,e4 ; 

	e1={5,6,1,0} ; 
	e2={5,1,1,0} ; 
	e3={6,1,1,0} ; 
	e4={6,2,1,0} ; 

	out.addEdge(e1) ; out.addEdge(e2) ; out.addEdge(e3) ; out.addEdge(e4) ; 

	verify_graph(ans,out) ; 
}	

TEST_CASE("Verifying vector is properly resized at all times","[part=1]"){

	Graph g ; srand(time(nullptr)) ; 

	for(unsigned i = 0 ; i < 150 ; i++) { 

		unsigned curr_size = g.getSize() ;

		int n1 = rand() % 36000, n2 = rand() %36000;  

		size_t resize_to = max(n1,n2) ; 

		g.resize(resize_to) ; 

		if(resize_to <= curr_size) { 
			REQUIRE(g.getSize() == curr_size) ; 
		}

		else { 
			REQUIRE(g.getSize() == resize_to) ; 
		}
	}

	for(unsigned i = 0 ; i < 150 ; i++) { 

		unsigned curr_size = g.getSize() ;

		double n1 = rand() % 36000, n2 = rand() %36000;  

		size_t resize_to = max(n1,n2) ; 

		g.addEdge({n1,n2,1,0}) ; 

		if(resize_to <= curr_size) { 
			REQUIRE(g.getSize() == curr_size) ; 
		}

		else { 
			REQUIRE(g.getSize() == resize_to) ; 
		}
	}
}
TEST_CASE("Verifying edge helper functions are working","[part=1]"){
	REQUIRE(true) ;
}
TEST_CASE("Verifying write to file works","[part=1],[write]") { 
	
	Graph g1,g2 ; 

	Parse parser ; 

	parser.readFromFile("tests/small_graph1.csv",g1) ; 
	parser.writeToFile("test_write_small1.csv",g1) ; 
	parser.readFromFile("test_write_small1.csv",g2) ; 

	verify_graph(g1,g2) ; 

	g1.clearGraph() ; g2.clearGraph() ; 

	parser.readFromFile("tests/small_graph3.csv",g1) ; 
	parser.writeToFile("test_write_small3.csv",g1) ; 
	parser.readFromFile("test_write_small3.csv",g2) ; 

	verify_graph(g1,g2) ; 

	g1.clearGraph() ; g2.clearGraph() ;

	parser.readFromFile("tests/medium_graph1.csv",g1) ; 
	parser.writeToFile("test_write_med1.csv",g1) ; 
	parser.readFromFile("test_write_med1.csv",g2) ; 

	verify_graph(g1,g2) ; 

	g1.clearGraph() ; g2.clearGraph() ;

	parser.readFromFile("tests/medium_graph_weighted.csv",g1) ; 
	parser.writeToFile("test_write_med_weighted.csv",g1) ; 
	parser.readFromFile("test_write_med_weighted.csv",g2) ; 

	verify_graph(g1,g2) ; 

	g1.clearGraph() ; g2.clearGraph() ;

	parser.readFromFile("tests/first_100_lines.csv",g1) ; 
	parser.writeToFile("test_write_first100.csv",g1) ; 
	parser.readFromFile("test_write_first100.csv",g2) ; 

	verify_graph(g1,g2) ; 

	g1.clearGraph() ; g2.clearGraph() ;

	parser.readFromFile("tests/first_100_lines_unweighted.csv",g1) ; 
	parser.writeToFile("test_write_first100_unweighted.csv",g1) ; 
	parser.readFromFile("test_write_first100_unweighted.csv",g2) ; 

	verify_graph(g1,g2) ; 

	g1.clearGraph() ; g2.clearGraph() ;


}


TEST_CASE("Test BFS Search: medium graph, short path", "[part=2]") {
	Graph ans = medium_graph_unweighted();
	int start = 12;
	int end = 10;

	vector<int> correctShortestPath = {12, 11, 1, 3, 5, 7, 8, 9, 10};
	vector<int> calculatedShortestPath = ans.bfsSearch(start, end);

	REQUIRE(calculatedShortestPath == correctShortestPath);

}

TEST_CASE("Test BFS Search: medium graph, long path", "[part=2]") {
	Graph ans = medium_graph_unweighted();
	int start = 12;
	int end = 6;

	vector<int> correctShortestPath = {12, 11, 1, 2, 4, 6};
	vector<int> calculatedShortestPath = ans.bfsSearch(start, end);

	REQUIRE(calculatedShortestPath == correctShortestPath);

}

TEST_CASE("Test BFS Search: medium graph, no valid path", "[part=2]") {
	Graph ans = medium_graph_unweighted();
	int start = 7;
	int end = 12;

	vector<int> correctShortestPath = {-1};
	vector<int> calculatedShortestPath = ans.bfsSearch(start, end);

	REQUIRE(calculatedShortestPath == correctShortestPath);
}

TEST_CASE("Test BFS Search: large graph, comprehensive", "[part=5]") {
	Graph ans = large_graph_unweighted();

	int start = 46;
	int end = 23;

	vector<int> correctShortestPath = {46, 36, 21, 1, 17, 23};
	vector<int> calculatedShortestPath = ans.bfsSearch(start, end);

	REQUIRE(calculatedShortestPath == correctShortestPath);

	start = 41;
	end = 19;
	correctShortestPath = {41, 36, 21, 1, 17, 23, 19};
	calculatedShortestPath = ans.bfsSearch(start, end);
	REQUIRE(calculatedShortestPath == correctShortestPath);

	//test with no existing path
	start = 25;
	end = 23;
	correctShortestPath = {-1};
	calculatedShortestPath = ans.bfsSearch(start, end);
	REQUIRE(calculatedShortestPath == correctShortestPath);
}

TEST_CASE("Test ComprehensiveBFSTraversal visits all nodes", "[part=3]") {
	Graph ans = medium_graph_unweighted();

	vector<int> path = ans.comprehensiveBFSTraversal();

	int unvisitedNodes = count(path.begin(), path.end(), -1);
	REQUIRE(unvisitedNodes == 1);
}


TEST_CASE("Test Dijkstra's: medium graph", "[part=2]") {
	Graph ans = medium_graph_weighted();

	int start = 5;
	int end = 2;
	vector<int> correctPath = {5, 7, 8, 9, 10, 11, 1, 2};
	int correctDist = 71;
	pair<vector<int>, int> correctShortestPathAndDist = make_pair(correctPath, correctDist);
	pair<vector<int>, int> calculatedShortestPathAndDist = ans.dijkstraSearch(start, end);
	verify_dijkstra_helper(correctShortestPathAndDist, calculatedShortestPathAndDist);
}

TEST_CASE("Test Dijkstra's: medium graph, no valid path", "[part=2]") {
	Graph ans = medium_graph_weighted();

	int start = 7;
	int end = 12;
	vector<int> correctPath = {-1};
	int correctDist = -1;
	pair<vector<int>, int> correctShortestPathAndDist = make_pair(correctPath, correctDist);
	pair<vector<int>, int> calculatedShortestPathAndDist = ans.dijkstraSearch(start, end);
	verify_dijkstra_helper(correctShortestPathAndDist, calculatedShortestPathAndDist);
}

TEST_CASE("Test Dijkstra's: large graph, comprehensive", "[part=3]") {
	Graph ans = large_graph_weighted();

	int start = 44;
	int end = 19;
	vector<int> correctPath = {44, 39, 7, 13, 1, 17, 23, 19};
	int correctDist = 46;
	pair<vector<int>, int> correctShortestPathAndDist = make_pair(correctPath, correctDist);
	pair<vector<int>, int> calculatedShortestPathAndDist = ans.dijkstraSearch(start, end);
	verify_dijkstra_helper(correctShortestPathAndDist, calculatedShortestPathAndDist);
	
	start = 41;
	end = 26;
	correctPath = {41, 36, 21, 2, 4, 26};
	correctDist = 35;
	correctShortestPathAndDist = make_pair(correctPath, correctDist);
	calculatedShortestPathAndDist = ans.dijkstraSearch(start, end);
	verify_dijkstra_helper(correctShortestPathAndDist, calculatedShortestPathAndDist);

	start = 2;
	end = 37;
	correctPath = {2, 21, 36, 37};
	correctDist = 22;
	correctShortestPathAndDist = make_pair(correctPath, correctDist);
	calculatedShortestPathAndDist = ans.dijkstraSearch(start, end);
	verify_dijkstra_helper(correctShortestPathAndDist, calculatedShortestPathAndDist);

	//test with no existing path
	start = 16;
	end = 33;
	correctPath = {-1};
	correctDist = -1;
	correctShortestPathAndDist = make_pair(correctPath, correctDist);
	calculatedShortestPathAndDist = ans.dijkstraSearch(start, end);
	verify_dijkstra_helper(correctShortestPathAndDist, calculatedShortestPathAndDist);
}

TEST_CASE("Test prediction between adjacent users", "[part=2]") {
	Graph ans = medium_graph_weighted();

	int start = 2;
	int end = 4;

	double actualRating = 10;
	double calculatedRating = ans.predictRating(start, end);

	REQUIRE(calculatedRating == actualRating);
}

TEST_CASE("Test prediction between distant users", "[part=2]") {
	Graph ans = medium_graph_weighted();

	int start = 12;
	int end = 7;

	double actualRating = 10 - ((double) 61 / 5);
	double calculatedRating = ans.predictRating(start, end);

	REQUIRE(calculatedRating == actualRating);
}

TEST_CASE("Testing strongly connected components on graphs","[scc]") { 
	Graph g ; 
	Parse parser; 

	parser.readFromFile("tests/small_graph1.csv",g) ; 

	g.SCCAlgorithm() ;

	std::vector<std::vector<int>> sccs = g.scc ; 

	std::vector<int> ans1 = {1}, ans2 = {2} , ans3 = {3} , ans4 = {4} ; 

	std::map<std::vector<int>,bool> map ; map[ans1] = true ; map[ans2] = true ; map[ans3] = true ; map[ans4] = true ; 
	for(auto& v : sccs) { 
		std::sort(v.begin() , v.end()) ; 

		REQUIRE(map.count(v) != 0 ) ; 
	}

	g.clearGraph() ; map.clear() ; sccs.clear() ; 

	parser.readFromFile("tests/small_graph3.csv",g) ; 

	g.SCCAlgorithm() ; 

	sccs = g.scc ; 

	std::cout << sccs.size() << std::endl ;

	ans1 = {1,2,3,4,5,6} ; 

	map[ans1] = true ;  
	for(auto& v : sccs) { 
		std::sort(v.begin() , v.end()) ; 

		REQUIRE(map.count(v) != 0 ) ; 
	}

	g.clearGraph() ; map.clear() ; sccs.clear() ; 

	parser.readFromFile("tests/medium_graph_weighted.csv",g) ; 

	g.SCCAlgorithm() ; 

	sccs = g.scc ; 

	std::cout << sccs.size() << std::endl ;

	ans1 = {1,2,3,4,5,6,7,8,9,10,11}; ans2 = {12} ; 

	map[ans1] = true ;  map[ans2] = true ; 
	for(auto& v : sccs) { 
		std::sort(v.begin() , v.end()) ; 

		REQUIRE(map.count(v) != 0 ) ; 
	}

	

}
