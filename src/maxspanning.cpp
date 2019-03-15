#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
       << " graph_filename vertexNum output_filename"
       << endl;
    exit(-1);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        usage(argv[0]);
    }
    
    char* graph_filename = argv[1];
    char* output_filename = argv[3];
    int start = stoi(argv[2]);

    Graph* g = new Graph();
    g->loadFromFile( graph_filename ); 
    
    ofstream outfile( output_filename );
    
    vector<pair<int,int>> maxSpan= g->maxSpanning(start);
    for( pair<int,int> x : maxSpan ) {
        outfile << x.first << " " << x.second << endl;
    }

    outfile.close();
    delete g;
}
