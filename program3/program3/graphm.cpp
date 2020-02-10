//
//  graphm.cpp
//  Graph
//
//  Created by Diana Gutierrez on 2/7/20.
//  Copyright © 2020 Diana Gutierrez. All rights reserved.
//

#include <stdio.h>
#include "graphm.h"
#include <vector>
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
    string t;
    infile >> size; //read number of nodes into size
    getline(infile, t);
    
    for(int i = 1; i <= size; i++)
    {
        if (!data[i].setData(infile)) {
            return; // hit eof, therefore break and finish
        }
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
        T[from][to].dist = edge;
        T[from][to].path = from;
        return true;
    }
    return false;
}

bool GraphM::removeEdge(int from, int to)
{
    if ( from >= 0 && from < MAXNODES && to >= 0 && to < MAXNODES) {
        C[from][to] = 0;
        T[from][to].dist = 0;
        return true;
    }
    return false;
}

void GraphM::findShortestPath()
{
    for(int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        T[source][source].visited = true;
        
        for(int i = 1; i <= size; i++)
        {
            if (source == i) {
                continue;
            }
            // find the first neighbor with shortest distance
            int v = minDist(source);
            if (v >= 0 && !T[source][v].visited) { // only if not visited yet
                T[source][v].visited = true; //marked as visited
                
                // find all the nodes adjacent to v
                for(int w = 1; w <= size; w++)
                {
                    if(C[v][w] != 0 && w != source) // only select the neighbors but skip the source
                    {
                        if(T[source][w].visited == false)
                        {
                            if ((T[source][w].dist == 0) || (T[source][v].dist + C[v][w] < T[source][w].dist)) {
                                T[source][w].dist = T[source][v].dist + C[v][w];
                                T[source][w].path = v;
                            }
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
    for(int i = 1; i <= size; i++ )
    {
        if (T[source][i].dist > 0 && !T[source][i].visited) {
            if (v == -1) {
                v = i;
                dist = T[source][i].dist;
            } else {
                if (T[source][i].dist < dist) {
                    dist = T[source][i].dist;
                    v = i;
                }
            }
        }
    }
    return v;
}

void GraphM::displayAll()
{
    int dist;
    for(int i = 1; i <= size; i++ )
    {
        std::cout << data[i] << endl;
        for(int to = 1; to <= size; to++)
        {
            if (i != to) {
                std::cout << "\t\t\t\t";
                dist = display(i, to);
                // used to display a human readable string for the endpoint
                if (dist > 0) {
                    //std::cout << "\t\t\t\t\t(" << data[to] << ")" << endl;
                }
            }
        }
        std::cout << "---------------------------" << endl;
        std::cout << endl;
    }
}

int GraphM::display(int from, int to)
{
    int dist = 0;
    int step = to;
    vector<int> path;
    
    std::cout << "from: " << from << " to: " << to << " distance: " ;
    if (T[from][to].path == 0) {
        std::cout << "--" << std::endl;
    } else {
        while(step != from) {
            path.insert(path.begin(), step);
            step = T[from][step].path;
        }
        path.insert(path.begin(), from);
        dist = T[from][to].dist;

        std::cout << dist << "  path: ";
        std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " "));
        std:: cout << std::endl;
    }
    return dist;
}
