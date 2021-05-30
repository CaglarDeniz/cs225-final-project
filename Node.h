#pragma once

class Node {
    public:
        Node(unsigned index,double avgRating = 11.0) ; // Node constructor for use with get(In/Out)Edges function of graphs
        Node();    //set it to default value
        unsigned getIndex() ; // helper for getting private index variable

    private:
        unsigned index_ ; // index needed when calling get(In/Out)Edges
        double avgRating_ = 11.0;  //might change 11 to a diff number later. Prob a variable that represents a number outside of range(-10 to 10)

};