#include "Node.h"

Node::Node(unsigned index , double avgRating) {
    index_ = index ; 
    avgRating_ = avgRating ; 
}

unsigned Node::getIndex() { 
    return index_ ; 
}