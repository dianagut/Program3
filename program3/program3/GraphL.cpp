//
//  GraphL.cpp
//  program3
//
//  Created by Diana Gutierrez on 2/12/20.
//  Copyright © 2020 Diana Gutierrez. All rights reserved.
//

#include "GraphL.hpp"
#include <queue>

GraphL::GraphL()
{
    
}
GraphL::~GraphL()
{

    if (nodes) {
        delete[] nodes;
    }
}

void GraphL::buildGraph(ifstream& infile)
{
    int from;
    int to;
    infile >> size; //read number of nodes into size
    nodes = new GraphNode[size+1];
    // element 0 won't be used.

    string t;
    getline(infile, t);
    
    for(int i = 1; i <= size; i++)
    {
        nodes[i].data = new NodeData();
        if (!nodes[i].data->setData(infile)) {
            return; // hit eof, therefore break and finish
        }
    }
    
    infile >> from >> to;
    while(from != 0)
    {
        insertEdge(from, to);
        infile >> from >> to;
    }
}

void GraphL::insertEdge(int from, int to)
{
    EdgeNode *newNode = new EdgeNode(to);
    newNode->nextEdge = nodes[from].edgeHead;
    nodes[from].edgeHead = newNode;
}

void GraphL::displayGraph()
{
    for(int n=1; n <= size; n++) {
        std::cout << "Node " << n << "\t" << *nodes[n].data << endl;
        EdgeNode *node = nodes[n].edgeHead;
        while (node) {
            std::cout << "\t\tedge " << n << " " << node->adjGraphNode << endl;
            node = node->nextEdge;
        }
        std::cout << endl;
    }
}
void GraphL::depthFirstSearch()
{
    for(int i = 1; i <= size; i++ )
    {
        std::cout << "Depth-first ordering: ";
        depthFirstSearch(1);
        std::cout << endl;
    }
}

void GraphL::depthFirstSearch(int node)
{
    if(!nodes[node].visited) {
        std::cout << node << " ";
        nodes[node].visited = true;
        EdgeNode *edge = nodes[node].edgeHead;
        while(edge) {
            depthFirstSearch(edge->adjGraphNode);
            edge=edge->nextEdge;
        }
    }
}
