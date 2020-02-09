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
    for(int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {
            C[i][j] = 0;
            T[i][j].visited = false;
            T[i][j].dist = 0;
            T[i][j].path = 0;
        }
    }
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
    
    for(int i = 0; i < size; i++)
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
    if ( from >= 0 && from < MAXNODES && to >= 0 && to < MAXNODES && edge > 0) {
        C[from][to] = edge;
        return true;
    }
    return false;
}

bool GraphM::removeEdge(int from, int to)
{
    if ( from >= 0 && from < MAXNODES && to >= 0 && to < MAXNODES) {
        C[from][to] = 0;
        return true;
    }
    return false;
}

void GraphM::findShortestPath()
{
    int v; 
    for(int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        
        for(int i = 1; i <= size; i++)
        {
            v = minDist(source);
            if (v >= 0) {
                T[source][v].visited = true; //marked as visited
                
                for(int w = 1; w <= size; w++)
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
