#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Node {
public:
    vector<pair<int,int>> adj;
    bool visited;
    int prev;
   
    Node(): visited(false), prev(-1) { }

};
#endif // NODE_HPP
