//
//  graphm.cpp
//  Graph
//
//  Created by Diana Gutierrez on 2/7/20.
//  Copyright © 2020 Diana Gutierrez. All rights reserved.
//

#include <stdio.h>
#include "graphm.h"
using namespace std;

GraphM::GraphM()
{
    
}

GraphM::~GraphM()
{
    
}

void GraphM::buildGraph(ifstream& infile)
{
    int from;
    int to;
    int edge;
    
    infile >> size; //read number of nodes into size
    
    for(int i = 0; i <= size; i++)
    {
        data[i].setData(infile);
    }
    
    infile >> from >> to >> edge;
    while(from != 0)
    {
        insertEdge(from, to, edge);
        infile >> from >> to >> edge;
    }
}

bool GraphM::insertEdge(int from, int to, int edge)
{
    return true;
}

void GraphM::findShortestPath()
{
    int v; 
    for(int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        
        for(int i = 1; i <= size; i++)
        {
            v = 0;
            T[source][v].visited = true; //marked as visited
            
            for(int w = 0; w < size; w++)
            {
                if(C[v][w] != 0)
                {
                    if(T[v][w].visited == false)
                    {
                        T[source][w].dist =min(T[source][w].dist,T[source][v].dist + C[v][w]);
                        
                    }
                }
            }
        }
    }
}

int GraphM::minDist(int source)
{
    int v = -1;
    int dist = 0;
    for (int i =0 ; i < MAXNODES; i++) {
        if (source != i) {
            if (C[source][i] > 0 && !T[source][i].visited) {
                if (v < 0) {
                    v = i;
                    dist = T[source][i].dist;;
                } else {
                    if (T[source][i].dist < dist) {
                        v = i;
                        dist = T[source][i].dist;
                    }
                }
            }
        }
    }
    return v;
}
