//
//  GraphL.hpp
//  program3
//
//  Created by Diana Gutierrez on 2/12/20.
//  Copyright © 2020 Diana Gutierrez. All rights reserved.
//

#ifndef GraphL_hpp
#define GraphL_hpp
#include "nodedata.h"

class GraphL
{
public:
    GraphL();
    ~GraphL();
    void buildGraph(ifstream&); // insert data from file
    void displayGraph();
    void depthFirstSearch();

private:
    struct EdgeNode; // forward reference for the compiler

    struct GraphNode { // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data; // data information about each node
        bool visited;
        
        GraphNode() {
            edgeHead = NULL;
            data = NULL;
            visited = false;
        }
        
        ~GraphNode() {
            if (data) { delete data; }
            EdgeNode *node = edgeHead;
            while(node) {
                EdgeNode *next = node->nextEdge;
                delete node;
                node = next;
            }
        }
    };
    struct EdgeNode {
        int adjGraphNode; // subscript of the adjacent graph node
        EdgeNode* nextEdge;
        
        EdgeNode(int n) {
            adjGraphNode = n;
            nextEdge = NULL;
        }
    };
    
    int size;
    GraphNode *nodes = NULL;
    
    void insertEdge(int, int);
    void depthFirstSearch(int);
};
#endif /* GraphL_hpp */
