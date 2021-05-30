#pragma once 
#include "Graph.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class Parse {
    public:
        static void readFromFile(std::string filename, Graph & graph); // static method to read a graph from a csv file 

        static void writeToFile(std::string filename, const Graph &) ; // static method to write a graph to a csv file

};