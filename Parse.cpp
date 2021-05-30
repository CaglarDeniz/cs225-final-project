#include "Parse.h"
using namespace std;

void Parse::readFromFile(std::string filename, Graph & graph) {
    fstream parser(filename);
    vector<std::string> row ; 
    string line ; 

    if(!parser.is_open()) { 
        std::cerr << "Trouble opening file, please check filename" << std::endl ; 
        return ;
    }
    else {  

        while(std::getline(parser,line)) {  
            //std::cout << line << std::endl ; 
            //std::cout << line.size() << std::endl ; 
            std::vector<double> literal  ; 
            std::vector<Edge*> out ; 
            //unsigned maxIndex ; 
            std::string temp = "" ; 
            for(auto & c : line) { 
                if(c == ',') {
                    literal.push_back(std::stod(temp)) ; 
                    temp = "" ; 
                    continue ; 
                }
                else{ 
                    temp += c ; 
                }

            }

            literal.push_back(std::stod(temp)) ; 

            graph.addEdge(literal) ; 
        }                                                                   
    }
}

void Parse::writeToFile(std::string filename, const Graph & g )  { 

    std::ofstream o_file ; 

    o_file.open(filename) ; 

    for(unsigned i = 1 ; i <= g.getSize() ; i++) { 

        const std::vector<Edge*> & edges = g.getOutEdges(Node(i)) ; 

        if(edges.empty()) { 
            continue ;
        }
        else { 
            for(auto & edge : edges) { 

                o_file << i << "," << edge->getKeyNode() << "," << edge->getRating() << "," << edge->getTimeStamp() << std::endl ; 

            }
        }
    } 
}


