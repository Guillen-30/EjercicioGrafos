#ifndef _GRAPHDISCOVER_
#define _GRAPHDISCOVER_ 1

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_set>

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
        int numNodos = pGrafo->getNumNodos();
        vector<vector<int>> dist(numNodos, vector<int>(numNodos, numeric_limits<int>::max()));
        vector<vector<vector<Pelicula *>>> paths(numNodos, vector<vector<Pelicula *>>(numNodos));

        // Initialize the distance matrix and paths matrix with direct connections
        for (int i = 0; i < numNodos; ++i)
        {
            for (int j = 0; j < numNodos; ++j)
            {
                if (i == j)
                {
                    dist[i][j] = 0;
                }
                else if (pGrafo->hayArco(pGrafo->getNodos()[i], pGrafo->getNodos()[j]))
                {
                    dist[i][j] = pGrafo->getPesoArco(pGrafo->getNodos()[i], pGrafo->getNodos()[j]);
                    paths[i][j] = {pGrafo->getNodos()[i], pGrafo->getNodos()[j]};
                }
            }
        }

        // Warshall's algorithm
        for (int k = 0; k < numNodos; ++k)
        {
            for (int i = 0; i < numNodos; ++i)
            {
                for (int j = 0; j < numNodos; ++j)
                {
                    if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max() &&
                        dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        paths[i][j] = paths[i][k];
                        paths[i][j].insert(paths[i][j].end(), paths[k][j].begin() + 1, paths[k][j].end());
                    }
                }
            }
        }

        // Extract paths from the paths matrix
        vector<Path *> *allPaths = new vector<Path *>();
        for (int i = 0; i < numNodos; ++i)
        {
            for (int j = 0; j < numNodos; ++j)
            {
                if (i != j && dist[i][j] != numeric_limits<int>::max())
                {
                    Path *path = new Path();
                    path->origen = paths[i][j].front();
                    path->destino = paths[i][j].back();
                    path->peso = dist[i][j];
                    path->path = paths[i][j];
                    allPaths->push_back(path);
                }
            }
        }

        //Filter paths by nodes
        vector<Path *> *filteredPaths = new vector<Path *>();
        for (Path *path : *allPaths)
        {
            if (path->origen == pOrigen && path->destino == pDestino)
            {
                filteredPaths->push_back(path);
            }
        }

        return filteredPaths;
    }

//The result should be a vector of paths with information kind of like this:
//1
// "Grease"->"The Hangover"->"Indiana Jones"->"The Matrix"->"The Hobbit"->"Toy Story"->"Shrek"
// 2
// "Grease"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Hobbit"->"Toy Story"->"Pirates of the Caribbean"->"Sherlock Holmes"->"Shrek"
// 3
// "Grease"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Hobbit"->"Toy Story"->"Shrek"
// 4
// "Grease"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Matrix"->"The Hobbit"->"Toy Story"->"Pirates of the Caribbean"->"Sherlock Holmes"->"Shrek"
// 5
// "Grease"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Matrix"->"The Hobbit"->"Toy Story"->"Shrek"
// 6
// "Grease"->"La La Land"->"The Godfather"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Hobbit"->"Toy Story"->"Pirates of the Caribbean"->"Sherlock Holmes"->"Shrek"
// 7
// "Grease"->"La La Land"->"The Godfather"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Hobbit"->"Toy Story"->"Shrek"
// 8
// "Grease"->"La La Land"->"The Godfather"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Matrix"->"The Hobbit"->"Toy Story"->"Pirates of the Caribbean"->"Sherlock Holmes"->"Shrek"
// 9
// "Grease"->"La La Land"->"The Godfather"->"Forrest Gump"->"Grease"->"The Hangover"->"Indiana Jones"->"The Matrix"->"The Hobbit"->"Toy Story"->"Shrek"

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