#ifndef _GRAPHDISCOVER_
#define _GRAPHDISCOVER_ 1

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#include "grafoPelicula.h"

using namespace std;

struct Path
{
    Pelicula *origen = nullptr;
    Pelicula *destino = nullptr;
    int peso;

    vector<Pelicula *> path;
};

struct DistancePath
{
    Pelicula *keyNode = nullptr;
    Pelicula *LastNodo = nullptr;
    bool procesado = false;
    int peso = 999999999;
};

class GraphDiscover
{
public:
vector<Path *> *getPathsByWarshall(Pelicula *pOrigen, Pelicula *pDestino, GrafoPeliculas *pGrafo)
{
    vector<vector<DistancePath *>> distMatrix;
    vector<Path *> *resultPaths = new vector<Path *>();

    // Initialize the distance matrix
    for (Pelicula *rowNode : pGrafo->getNodos())
    {
        vector<DistancePath *> row;
        for (Pelicula *colNode : pGrafo->getNodos())
        {
            DistancePath *distancePath = new DistancePath();
            distancePath->keyNode = colNode;
            row.push_back(distancePath);
        }
        distMatrix.push_back(row);
    }

    // Fill in the distance matrix with direct edges' weights
    for (Pelicula *node : pGrafo->getNodos())
    {
        for (Pelicula *neighbor : pGrafo->getVecinos(node))
        {
            int weight = pGrafo->getPesoArco(node, neighbor);
            distMatrix[node->getId()][neighbor->getId()]->peso = weight;
            distMatrix[node->getId()][neighbor->getId()]->LastNodo = node;
        }
    }

    // Warshall's algorithm
    for (Pelicula *k : pGrafo->getNodos())
    {
        for (Pelicula *i : pGrafo->getNodos())
        {
            for (Pelicula *j : pGrafo->getNodos())
            {
                if (distMatrix[i->getId()][k->getId()]->peso + distMatrix[k->getId()][j->getId()]->peso <
                    distMatrix[i->getId()][j->getId()]->peso)
                {
                    distMatrix[i->getId()][j->getId()]->peso =
                        distMatrix[i->getId()][k->getId()]->peso + distMatrix[k->getId()][j->getId()]->peso;
                    distMatrix[i->getId()][j->getId()]->LastNodo = distMatrix[k->getId()][j->getId()]->LastNodo;
                }
            }
        }
    }

    // Extract paths from the distance matrix
    for (Pelicula *startNode : pGrafo->getNodos())
    {
        for (Pelicula *endNode : pGrafo->getNodos())
        {
            if (startNode != endNode && startNode == pOrigen && endNode == pDestino &&
                distMatrix[startNode->getId()][endNode->getId()]->peso != numeric_limits<int>::max())
            {
                Path *path = new Path();
                path->origen = startNode;
                path->destino = endNode;
                path->peso = distMatrix[startNode->getId()][endNode->getId()]->peso;

                Pelicula *currentNode = endNode;
                while (currentNode != nullptr && currentNode != startNode)
                {
                    path->path.insert(path->path.begin(), currentNode);
                    currentNode = distMatrix[startNode->getId()][currentNode->getId()]->LastNodo;
                }

                resultPaths->push_back(path);
            }
        }
    }

    return resultPaths;
}

    Path *getShortestPath(Pelicula *pOrigen, Pelicula *pDestino, GrafoPeliculas *pGrafo)
    {
        vector<DistancePath *> pendingNodesV;
        vector<DistancePath *> processedNodesF;
        DistancePath *currentMin;

        // Initialize DistancePath for all nodes in the graph
        for (Pelicula *node : pGrafo->getNodos())
        {
            DistancePath *distancePath = new DistancePath();
            distancePath->keyNode = node;
            pendingNodesV.push_back(distancePath);
        }

        // Find the DistancePath for the starting node and set its weight to 0
    auto startDistancePathIt = find_if(pendingNodesV.begin(), pendingNodesV.end(),
        [&](DistancePath *dp) { return dp->keyNode == pOrigen; });

    // Check if the starting node is found
    if (startDistancePathIt != pendingNodesV.end()){
        DistancePath *startDistancePath = *startDistancePathIt;
        startDistancePath->peso = 0;

        // Dijkstra's Algorithm
        while (!pendingNodesV.empty())
        {
            auto minDistancePathIt = min_element(pendingNodesV.begin(), pendingNodesV.end(),
                                    [](DistancePath *a, DistancePath *b) { return a->peso < b->peso; });

        currentMin = *minDistancePathIt;  // Dereference the iterator to get the actual DistancePath
        pendingNodesV.erase(minDistancePathIt);

        // Relaxation step
        for (auto neighbor : pGrafo->getVecinos(currentMin->keyNode))
        {
            // Find the DistancePath for the neighbor
            auto neighborDistancePathIt = find_if(pendingNodesV.begin(), pendingNodesV.end(),
                                                [&](DistancePath *dp) { return dp->keyNode == neighbor; });

            // Check if the neighbor is found
            if (neighborDistancePathIt != pendingNodesV.end())
            {
                DistancePath *neighborDistancePath = *neighborDistancePathIt;

                if (!neighborDistancePath->procesado &&
                    currentMin->peso + pGrafo->getPesoArco(currentMin->keyNode, neighbor) < neighborDistancePath->peso)
                {
                    neighborDistancePath->peso = currentMin->peso + pGrafo->getPesoArco(currentMin->keyNode, neighbor);
                    neighborDistancePath->LastNodo = currentMin->keyNode;
                }
            }
        }

            // Move the processed node to processedNodesF
            processedNodesF.push_back(currentMin);
            currentMin->procesado = true;
        }

        // Reconstruct the path from pOrigen to pDestino
        Path *shortestPath = new Path();
        shortestPath->origen = pOrigen;
        shortestPath->destino = pDestino;
        shortestPath->peso = processedNodesF.back()->peso;

        Pelicula *currentNode = pDestino;
        while (currentNode != nullptr)
        {
            shortestPath->path.insert(shortestPath->path.begin(), currentNode);
            auto dpIt = find_if(processedNodesF.begin(), processedNodesF.end(),
                                [&](DistancePath *dp) { return dp->keyNode == currentNode; });
            currentNode = (*dpIt)->LastNodo;
        }

        return shortestPath;
        }else{
            cerr << "Error: Starting node not found in the graph." << endl;
            return nullptr; // or handle the error in an appropriate way
        }
    }
};

#endif