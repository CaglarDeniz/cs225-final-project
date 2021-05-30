#include <iostream>
#include "Parse.h"
#include "Graph.h"

using namespace std;

void print_usage() { 

    cerr << "Usage : " << endl << 

                "\t" << "-i <input_file>, --infile <input_file> to pass an input filename\n\n" <<
                "\t" << "-o <output_file>, --ofile <output_file> to pass an output filename\n\n" <<
                "\t" << "use --strongly-connected to get strongly connected component analysis\n\n"<<
                "\t" << "use --bfs-search <start_index> <end_index> to conduct a breadth-first search starting at start and searching for end\n\n"<<
                "\t" << "use --bfs-traversal <start_index> to conduct a traversal starting at start and reaching every connected node\n\n"<<
                "\t" << "use --bfs-comprehensive to conduct a traversal  reaching every node on graph\n\n"<<
                "\t" << "use --dijkstra-search <start_index> <end_index> to run dijkstras and get shortest path,distance from start to end\n\n"<<
                "\t" << "use --dijkstra-traversal <start_index> to run dijkstras and get shortest path,distance from start to every single node\n\n"<<
                "\t" << "use --predict-rating <start_index> <end_index> to predict what the start node would rate the end node\n\n" ;

}

enum Options {
    Help,
    InputFile,
    OutputFile,
    StronglyConnected,
    BFSSearch,
    BFSTraverse,
    BFSComprehensive,
    DijkstraSearch,
    DijkstraTraverse,
    predictRating,
    Option_Invalid
};

Options resolveOption(string argument) {
    if (argument == "-h")                           return Help;
    if (argument == "-i" || argument == "--infile") return InputFile;
    if (argument == "-o" || argument == "--ofile")  return OutputFile;
    if (argument == "--strongly-connected")         return StronglyConnected;
    if (argument == "--bfs-search")                 return BFSSearch;
    if (argument == "--bfs-traversal")              return BFSTraverse;
    if (argument == "--bfs-comprehensive")          return BFSComprehensive;
    if (argument == "--dijkstra-search")            return DijkstraSearch;
    if (argument == "--dijkstra-traversal")         return DijkstraTraverse;
    if(argument == "--predict-rating")              return predictRating;
    return Option_Invalid;
}

int main(int argCount , char * argv[]) {

    Graph g; 
    Parse parser; 
    string ifile, ofile;
    bool hasInFile = false ; 
    bool hasOutFile = false ; 
    map<string,bool> args; 

    int start = 0, end = 0;

    if(argCount < 2 ) {
        print_usage(); 
        exit(2);
    } else {
        for(int i = 1 ; i < argCount ; i++) { 
            string argument = argv[i] ; 
            switch(resolveOption(argument)) {
                case Help: {
                    print_usage();
                    exit(0);
                    break;
                }
                case InputFile: {
                    if (i + 1 < argCount) {
                        string filename = argv[i + 1];
                        fstream infile(filename);

                        if (infile.is_open()) {
                            hasInFile = true;
                            ifile = filename;
                            i++;
                        } else {
                            cerr << "Please provide a valid inputfile name\n" << endl;
                            exit(1);
                        }
                    } else {
                        cerr << "Must include inputfile name after the -i or --infile flag\n" << endl;
                        exit(1);
                    }
                    break;
                }
                case OutputFile: {
                    if (i + 1 < argCount) {
                        string filename = argv[i + 1];
                        hasOutFile = true;
                        ofile = filename;
                        i++;
                    } else {
                        cerr << "Must include the outputfile name after the -o or --ofile flag\n" << endl;
                        exit(1);
                    }
                    break;
                }
                case StronglyConnected: {
                    args["strongly-connected"] = true;
                    break;
                }
                case BFSSearch: {
                    if (i + 2 < argCount) {
                        args["bfs-search"] = true;
                        start = stoi(argv[i + 1]);
                        end = stoi(argv[i + 2]);
                    } else {
                        cerr << "Must provide start and end indexes for --bfs-search\n" << endl;
                    }
                    i += 2;
                    break;
                }
                case BFSTraverse: {
                    if (i + 1 < argCount) {
                        args["bfs-traversal"] = true;
                        start = stoi(argv[i + 1]);
                    } else {
                        cerr << "Must provide start index for --bfs-traversal\n" << endl;
                        exit(1);
                    }
                    i++;
                    break;
                }
                case BFSComprehensive: {
                    args["bfs-comprehensive"] = true;
                    break;
                }
                case DijkstraSearch: {
                    if (i + 2 < argCount) {
                        args["dijkstra-search"] = true;
                        start = stoi(argv[i + 1]);
                        end = stoi(argv[i + 2]);
                    } else {
                        cerr << "Must provide start index and end index for --dijkstra-search\n" << endl;
                        exit(1);
                    }
                    i += 2;
                    break;
                }
                case DijkstraTraverse: {
                    if (i + 1 < argCount) {
                        args["dijkstra-traversal"] = true;
                        start = stoi(argv[i + 1]);
                    } else {
                        cerr << "Must provide start index for --dijkstra-traversal\n" << endl;
                        exit(1);
                    }
                    i++;
                    break;
                }
                case predictRating : { 
                    if(i+2 < argCount) { 
                        args["predict-rating"] = true ; 
                        start = stoi(argv[i+1]) ; 
                        end = stoi(argv[i+2]) ; 
                    }
                    else { 
                        cerr << "Must provide start and end indexes for the --predict-rating flag \n" ; 
                        exit(1) ; 
                    }
                    i+=2 ; 
                    break ; 
                }
                case Option_Invalid: {
                    cerr << "Invalid flag" << endl;
                    exit(1);
                    break;
                }
            }
        }
    }

    //default infile if one isn't provided
    if(!hasInFile) { 
        ifile = "graph.csv" ; 
        fstream def(ifile) ; 

        if(!def.is_open()) { 
            cerr<< "No input filename provided, default filename -graph.csv- does not exist in current directory\n" ; 
            exit(2) ; 
        }

        cout << "No input filename provided, using graph.csv\n" << endl ; 

    }

    //default outfile if one isn't provided
    if(!hasOutFile) { 
        ofile =  "graph_output" ; 
        cout << "No output filename provided, using graph_output\n" ; 
    }

    parser.readFromFile(ifile,g) ; 


    if(start < 0 || end < 0 || start > int(g.getSize()) || end > int(g.getSize())) { 
        cerr << "Please enter valid start/end node indexes\n" << endl ; 
        exit(2) ;
    }


    for(auto & p : args) { 

        if(p.first == "bfs-search" && p.second == true) { 

            if(start == 0  || end == 0 ){ 
                cerr << "Must provide start valid and end node indexes after the --bfs-search flag " << endl ; 
                exit(1) ;
            }

            vector<int> path = g.bfsSearch(start,end) ; 

            fstream out(ofile+"_bfs_search.txt", ios_base::out) ;

            cout << "{ " ; 

            for(int & i : path) { 
                cout << i << ", " ;
            }
            cout << "}" << endl ; 

            out << "{ " ; 

            for(int & i : path) { 
                out << i << ", " ;
            }
            out << "}" << endl ;

            out.close() ; 
        }

        if(p.first == "bfs-traversal" && p.second == true) { 

            if(start == 0) { 
                cerr << "Must provide valid start index after --bfs-traversal" << endl ; 
                exit(1) ;
            }

            vector<int> backtrack = g.bfsTraversal(start) ; 

            fstream out(ofile+"_bfs_traversal.txt", ios_base::out) ; 

            vector<vector<int>> allPaths = {{-1}};
            for(size_t i = 1 ; i < g.getSize() ; i++) { 
                vector<int> shortestPath;
                if (backtrack[i] == -1) {
                    shortestPath = {-1};
                } else {
                    shortestPath = {(int) i};
                    int currentNode = i;
                    while (currentNode != start) {
                        int previousNode = backtrack[currentNode];
                        shortestPath.insert(shortestPath.begin(), previousNode);
                        currentNode = previousNode;
                    }
                }
                allPaths.push_back(shortestPath);
            }

            //out << "Shortest path from " << start << " to each other node" << endl;
            for (unsigned i = 1; i < allPaths.size(); i++) {
                out << "{";
                for (unsigned j = 0; j < allPaths[i].size(); j++) {
                    out << allPaths[i][j];
                    if (j < allPaths[i].size() - 1) {
                        out << ", ";
                    }
                }
                out << "}" << endl;
            }
            out.close();
        }

        if(p.first == "bfs-comprehensive" && p.second == true) { 

            vector<int> path = g.comprehensiveBFSTraversal() ; 

            fstream out(ofile+"_bfs_comprehensive.txt",ios_base::out) ; 

            out << "Every traversal represented as one (backtrackable) path vector" << endl ; 

            out << "{ " ; 

            for(int & i : path) { 

                out << i << ", " ; 

            }

            out << "}" << endl ; 

            out.close() ; 

        }

        if(p.first == "dijkstra-search" && p.second == true) { 

            if(start == 0 || end == 0 ){ 
                cerr << "Must input both valid start and end node indexes after the --dijkstra-search flag" << endl ; 
                exit(1) ; 
            }

            pair<vector<int>,int> djk = g.dijkstraSearch(start,end) ; 

            fstream out(ofile + "_dijkstra_search.txt", ios_base::out) ;

            vector<int>& path = djk.first ; 

            int & distance = djk.second ; 

            cout << "Shortest path from " << start << " to " << end << " has distance: " << distance << endl ; 

            cout << "{" ; 

            for(auto & v : path) { 

                cout << v << ", " ; 

            } 
            cout << "}" << endl ; 

            out<< "Shortest path from " << start << " to " << end << endl ; 

            out<< "{" ; 

            for(auto & v : path) { 

                out<< v << ", " ; 

            } 

            out<< "}" << endl ; 

            out.close() ; 

        }

        if(p.first == "dijkstra-traversal" && p.second == true) { 

            if(start == 0 ) {
                cerr << "Must provide valid start index after --dijkstra-traversal" << endl ; 
                exit(1) ; 
            }

            pair<vector<int>, vector<int>> djk = g.dijkstraTraverse(start) ; 

            vector<int> backtrack = djk.first ; 

            vector<int> distances = djk.second ; 

            fstream out(ofile+"_dijkstra_traversal.txt", ios_base::out) ; 

            vector<vector<int>> allPaths = {{-1}};
            for(size_t i = 1 ; i < g.getSize() ; i++) { 
                vector<int> shortestPath;
                if (backtrack[i] == -1) {
                    shortestPath = {-1};
                } else {
                    shortestPath = {(int) i};
                    int currentNode = i;
                    while (currentNode != start) {
                        int previousNode = backtrack[currentNode];
                        shortestPath.insert(shortestPath.begin(), previousNode);
                        currentNode = previousNode;
                    }
                }
                allPaths.push_back(shortestPath);
            }

            //out << "Shortest path from " << start << " to each other node: " << endl;
            for (unsigned i = 1; i < allPaths.size(); i++) {
                out << "{";
                for (unsigned j = 0; j < allPaths[i].size(); j++) {
                    out << allPaths[i][j];
                    if (j < allPaths[i].size() - 1) {
                        out << ", ";
                    }
                }
                out << "} : " << distances[i] << endl;
            }
            out.close();
        }

        if(p.first == "strongly-connected" && p.second == true) { 

            g.SCCAlgorithm() ; 

            vector<vector<int>> sccs = g.scc ;

            fstream out(ofile+"_sccs.txt",ios_base::out) ; 

            for(auto & scc : sccs) { 

                out << "{ " ; 

                for(auto & v : scc) { 

                    out << v << ", " ; 
                }
                
                out << "}  " << endl;

            }

            out.close() ;
        }

        if(p.first == "predict-rating" && p.second == true) {
            if(start == 0 || end == 0 ) { 
                cerr << "Must input valid node indexes for the --predict-rating flag\n" ; 
                exit(1) ; 
            } 
            double predicted_rat = g.predictRating(start,end) ; 

            std::cout << "Prediction says " << start << " would rate " << end << " : " << predicted_rat << endl ; 
        }
    }
}