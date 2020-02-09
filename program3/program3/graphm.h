//
//  graphm.h
//  Graph
//
//  Created by Diana Gutierrez on 2/7/20.
//  Copyright © 2020 Diana Gutierrez. All rights reserved.
//

#ifndef graphm_h
#define graphm_h
#include "nodedata.h"

const int MAXNODES = 6;

class GraphM
{
    public:
    
    GraphM();
    ~GraphM();
    void buildGraph(ifstream&); // insert data from file
    bool insertEdge(int,int,int);
    bool removeEdge(int, int);
    void findShortestPath();
    void displayAll();
    void display(int, int);
    
    private:
    
    struct TableType
       {
              bool visited;          // whether node has been visited
              int dist;              // shortest distance from source known so far
              int path;              // previous node in path of min dist
       };

       NodeData data[MAXNODES];              // data for graph nodes

       int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix

       int size;                             // number of nodes in the graph

       TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

        int minDist(int source);
    void debugC();
    void debugT();
    
};

#endif /* graphm_h */
