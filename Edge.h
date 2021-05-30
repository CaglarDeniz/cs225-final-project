#pragma once
#include <vector>
using namespace std;

class Edge {
    public:

    //various edge constructors for general purpose use

    Edge() ; 

    Edge(unsigned key_node, int rating, double time_stamp, bool isOutGoing) ; 

    Edge(const Edge& other) ; 

    //getter and setter functions for private variables

    double getTimeStamp() ; 

    void setTimeStamp(double) ; 

    unsigned getKeyNode() ; 

    void setKeyNode(unsigned) ;

    int getRating() ; 

    void setRating(int) ; 

    bool getEdgeType() ; 

    void setEdgeType(bool type) ; 

    bool operator==(Edge & other) ; // logical comparison operator for use in testing

    bool operator!=(Edge & other) ; //logical comparison operator for use in testing 

    private:
        
        double  time_stamp_; // time stamp information for establishing when the trust rating was made
        unsigned key_node_;  // if the edge is an outgoing edge the node will represent the destination node, if its an incoming edge this will be the origin.
        int rating_;  //can be a better type
        bool isOutgoing_ ; // a boolean value indicating if an edge is outgoing or not
};