#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <queue>

using namespace std;

Graph::Graph(void): nodes(0) {}

Graph::~Graph(void) {
    for( auto itr : nodes ) {
        delete itr.second;
    }
}


vector<pair<int,int>> Graph::maxSpanning( int idSource ) {
    //set all nodes to false, -1
    for( auto it = nodes.begin(); it != nodes.end(); ++it ) {
        it->second->visited = false;
        it->second->prev = -1;
    }

    //retrieve starting node vertex
    Node* start = nodes.at( idSource );
    start->visited = true;

    //start pq and push in neighbors of start
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, TuplePtrComp> pq;
    for( unsigned int i = 0; i < start->adj.size(); i++ ) {
        pq.push( make_tuple( idSource, (start->adj)[i].first, (start->adj)[i].second ) );
    }
    
    //Prim's Algo
    tuple<int,int,int> curr;
    while( !pq.empty() ) {
        curr = pq.top();
        pq.pop();
        int vTo = get<1>(curr);
        Node* nodeTo = nodes.at(vTo);
        if( nodeTo->visited ) {
            continue;
        } else {
            nodeTo->visited = true;
            nodeTo->prev = get<0>(curr);
        }
        for( unsigned int j = 0; j < nodeTo->adj.size(); j++ ) {
            pq.push( make_tuple( vTo, (nodeTo->adj)[j].first, (nodeTo->adj)[j].second ) );
        }
    }

    //loop through all nodes and output MST edges
    vector<pair<int,int>> ret;
    for( auto it = nodes.begin(); it != nodes.end(); ++it ) {
        if( it->second->prev != -1 ) {
            ret.push_back( make_pair( it->first, it->second->prev ) );
        }
    }

    return ret;
}

/* Read in relationships from an inputfile to create a graph */
/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
bool Graph::loadFromFile(const char* in_filename) {
    ifstream infile(in_filename);

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string s;
            if (!getline(ss, s, ' ')) break;
            record.push_back(s);
        }

        if (record.size() != 2) {
            continue;
        }

        //record[0] and record[1] are used to store the id the were i/o'd in
        int id1 = stoi(record[0]);
        int id2 = stoi(record[1]);

        Node* n1;
        Node* n2;
        if( !nodes.count( id1 ) ) {
            n1 = new Node();
            nodes.emplace( id1, n1 );
        } else {
            n1 = nodes.at( id1 );
        }

        if( !nodes.count( id2 ) ) {
            n2 = new Node();
            nodes.emplace( id2, n2 );
        } else {
            n2 = nodes.at( id2 );
        }


        pair<int,int>* curr = nullptr;
        //go through adjacency list to find a pointer to vertex edge is pointing
        for( unsigned int i = 0; i < (n1->adj).size(); i++ ) {
            if( (n1->adj)[i].first == id2 ) {
                curr = &((n1->adj)[i]);
            }
        }
        if( curr ) {    //edge was found, increment weight
            curr->second = curr->second + 1;
        } else {        //edge was not found
            (n1->adj).push_back( make_pair(id2, 1) );
        }
        
        
        pair<int,int>* curr1 = nullptr;
        for( unsigned int i = 0; i < (n2->adj).size(); i++ ) {
            if( (n2->adj)[i].first == id1 ) {
                curr1 = &((n2->adj)[i]);
            }
        }
        if( curr1 ) {
            curr1->second = curr1->second + 1;
        } else {
            (n2->adj).push_back( make_pair(id1,1) );
        }
    }

    if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
    }

    infile.close();
    return true;
}
