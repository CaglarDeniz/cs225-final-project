#include "Edge.h"

Edge::Edge() { 
    time_stamp_ = 0.0 ; 
    key_node_ = 0 ; 
    rating_ = 11 ; 
    isOutgoing_ = false ; 
}

Edge::Edge(unsigned key_node , int rating , double time_stamp,bool isOutgoing) { 

    key_node_ = key_node ; 

    rating_ = rating ; 

    time_stamp_ = time_stamp ; 

    isOutgoing_ = isOutgoing ; 
    
}

Edge::Edge(const Edge & other) { 

    time_stamp_ = other.time_stamp_ ; 

    key_node_ = other.key_node_ ; 

    rating_ = other.rating_ ; 

    isOutgoing_ = other.isOutgoing_ ;

}

double Edge::getTimeStamp() { 
    return time_stamp_ ; 
}

void Edge::setTimeStamp(double stamp) { 
    time_stamp_ = stamp ; 
}

unsigned Edge::getKeyNode() { 
    return key_node_ ; 
}

void Edge::setKeyNode(unsigned node_index) { 
    key_node_ = node_index ; 
}

int Edge::getRating() { 
    return rating_  ; 
}

void Edge::setRating(int rating) { 
    rating_ = rating ; 
}

bool Edge::getEdgeType() { 
    return isOutgoing_ ; 
}

void Edge::setEdgeType(bool type) { 
    isOutgoing_ = type ; 
}

bool Edge::operator==(Edge & other) { 
    return time_stamp_ == other.time_stamp_ && rating_ == other.rating_ && key_node_ == other.key_node_ && isOutgoing_ == other.isOutgoing_ ; 
}

bool Edge::operator!=(Edge & other) { 
    return time_stamp_ != other.time_stamp_ || rating_ != other.rating_ || key_node_ != other.key_node_ || isOutgoing_ != other.isOutgoing_ ; 
}