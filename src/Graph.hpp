#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <tuple>
#include <unordered_map>
#include "Node.hpp"

using namespace std;

class TuplePtrComp {
public:
    bool operator()( tuple<int,int,int>& left, tuple<int,int,int>& right ) const {
        return get<2>(left) < get<2>(right);
    }
};

class Graph {
protected:
    unordered_map<int,Node*> nodes;

public:
    Graph(void);

    ~Graph(void);

    //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA

    /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

    bool loadFromFile(const char* in_filename);

    vector<pair<int,int>> maxSpanning( int idSource );
};

#endif  // GRAPH_HPP
