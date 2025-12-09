#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

//NOT USED
struct Edge
{
    int destination;
    int weight;

    Edge(int dest, int wight) : destination(dest), weight(wight) {}
};

class weightedDirectedGraph
{
public:
    int numOfVertices;
    std::vector<std::list<Edge>> adjList;

    weightedDirectedGraph(int vertices) : numOfVertices(vertices)
    {
        adjList.resize(vertices);
    }

    void addEdge(int source, int destination, int weight)
    {
        if (source >= 0 && source < numOfVertices && destination >= 0 && destination < numOfVertices)
        {
            adjList[source].emplace_back(destination, weight);
        }
        else
        {
            std::cout << "Invalid vertex index to add Edge at source: " << 
            source << " destination: " << destination << " weight: " << weight << std::endl;
        }
    }

    void toString(){
        for (size_t i = 0; i < numOfVertices; i++)
        {
            std::cout << "vertex: " << i << " outgoing edges: ";
            for (Edge& edge : adjList[i])
            {
                std::cout << " -> ( " << edge.destination << " weight: " << edge.weight << " )";
            }
                std::cout << std::endl;
        }
        
    }
};

#endif