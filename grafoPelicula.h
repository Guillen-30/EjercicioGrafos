#ifndef _GRAFOPELICULAS_
#define _GRAFOPELICULAS_ 1

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include "pelicula.h"

class GrafoPeliculas {
private:
    std::unordered_map<std::string, int> idNodo;
    std::vector<Pelicula*> nodos;  // Use pointers for Pelicula objects
    std::vector<std::vector<std::pair<int, int>>> relaciones; // Grafo dirigido con peso

public:
    GrafoPeliculas(){
        // Constructor
        }
    

    // Agregar una película como nodo en el grafo
    void agregarPelicula(Pelicula* pelicula) {
        int id = nodos.size();
        nodos.push_back(pelicula);
        idNodo[pelicula->getTitulo()] = id;
        relaciones.emplace_back();
        pelicula->setId(id);
    }

    // Agregar una relación entre dos películas basada en los géneros en común
    void agregarRelacion(const Pelicula* pelicula1, const Pelicula* pelicula2) {
        int id1 = idNodo[pelicula1->getTitulo()];
        int id2 = idNodo[pelicula2->getTitulo()];

        // Calcular el peso como la cantidad de géneros en común
        int peso = 0;
        const std::vector<std::string>& generos1 = pelicula1->getGeneros();
        const std::vector<std::string>& generos2 = pelicula2->getGeneros();
        for (const std::string& genero1 : generos1) {
            for (const std::string& genero2 : generos2) {
                if (genero1 == genero2) {
                    peso++;
                }
            }
        }

        relaciones[id1].emplace_back(id2, peso);
    }

    // Obtener las componentes conexas del grafo utilizando DFS
    std::vector<std::vector<Pelicula*>> obtenerComponentesConexas() {
        std::vector<bool> visitado(nodos.size(), false);
        std::vector<std::vector<Pelicula*>> componentesConexas;
        for (int i = 0; i < nodos.size(); ++i) {
            if (!visitado[i]) {
                std::vector<Pelicula*> componente;
                dfs(i, visitado, componente);
                componentesConexas.push_back(componente);
            }
        }
        return componentesConexas;
    }

    void dfs(int nodo, std::vector<bool>& visitado, std::vector<Pelicula*>& componente) {
        visitado[nodo] = true;
        componente.push_back(nodos[nodo]);
        for (const auto& relacion : relaciones[nodo]) {
            int vecino = relacion.first;
            if (!visitado[vecino]) {
                dfs(vecino, visitado, componente);
            }
        }
    }

    std::vector<Pelicula*> getNodos() {
        return nodos;
    }

    int getPesoArco(Pelicula* p1, Pelicula* p2){
        int peso = 0;
        const std::vector<std::string>& generos1 = p1->getGeneros();
        const std::vector<std::string>& generos2 = p2->getGeneros();
        for (const std::string& genero1 : generos1) {
            for (const std::string& genero2 : generos2) {
                if (genero1 == genero2) {
                    peso++;
                }
            }
        }
        return peso;
    }

    int getNumNodos(){
        return nodos.size();
    }

    bool isAdyacente(Pelicula* p1, Pelicula* p2){
        int id1 = idNodo[p1->getTitulo()];
        int id2 = idNodo[p2->getTitulo()];
        for (const auto& relacion : relaciones[id1]) {
            int vecino = relacion.first;
            if (vecino == id2) {
                return true;
            }
        }
        return false;
    }

    bool hayArco(Pelicula* p1, Pelicula* p2){
        int id1 = idNodo[p1->getTitulo()];
        int id2 = idNodo[p2->getTitulo()];
        for (const auto& relacion : relaciones[id1]) {
            int vecino = relacion.first;
            if (vecino == id2) {
                return true;
            }
        }
        return false;
    }

    std::vector<Pelicula*> getVecinos(Pelicula* p){
        std::vector<Pelicula*> vecinos;
        int id = idNodo[p->getTitulo()];
        for (const auto& relacion : relaciones[id]) {
            int vecino = relacion.first;
            vecinos.push_back(nodos[vecino]);
        }
        return vecinos;
    }
};

#endif