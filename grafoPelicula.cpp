#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include "pelicula.h"

class GrafoPeliculas {
private:
    std::unordered_map<std::string, int> idNodo;
    std::vector<Pelicula> nodos;
    std::vector<std::vector<std::pair<int, int>>> relaciones; // Grafo dirigido con peso

public:
    // Agregar una película como nodo en el grafo
    void agregarPelicula(const Pelicula& pelicula) {
        int id = nodos.size();
        nodos.push_back(pelicula);
        idNodo[pelicula.getTitulo()] = id;
        relaciones.emplace_back();
    }

    // Agregar una relación entre dos películas basada en los géneros en común
    void agregarRelacion(const Pelicula& pelicula1, const Pelicula& pelicula2) {
        int id1 = idNodo[pelicula1.getTitulo()];
        int id2 = idNodo[pelicula2.getTitulo()];
        
        // Calcular el peso como la cantidad de géneros en común
        int peso = 0;
        const std::vector<std::string>& generos1 = pelicula1.getGeneros();
        const std::vector<std::string>& generos2 = pelicula2.getGeneros();
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
    std::vector<std::vector<Pelicula>> obtenerComponentesConexas() {
        std::vector<bool> visitado(nodos.size(), false);
        std::vector<std::vector<Pelicula>> componentesConexas;
        for (int i = 0; i < nodos.size(); ++i) {
            if (!visitado[i]) {
                std::vector<Pelicula> componente;
                dfs(i, visitado, componente);
                componentesConexas.push_back(componente);
            }
        }
        return componentesConexas;
    }

    void dfs(int nodo, std::vector<bool>& visitado, std::vector<Pelicula>& componente) {
        visitado[nodo] = true;
        componente.push_back(nodos[nodo]);
        for (const auto& relacion : relaciones[nodo]) {
            int vecino = relacion.first;
            if (!visitado[vecino]) {
                dfs(vecino, visitado, componente);
            }
        }
    }
};

int main() {
    // Crear algunas películas
    std::vector<Pelicula> peliculas;
    std::vector<std::string> generos; 
    generos.push_back("Romance");
    generos.push_back("Comedy");
    Pelicula Grease("Grease",generos);//1
    peliculas.push_back(Grease);

    generos.clear();
    generos.push_back("Drama");
    generos.push_back("Romance");
    generos.push_back("Musical");
    Pelicula LaLaLand("La La Land",generos);//2
    peliculas.push_back(LaLaLand);

    generos.clear();
    generos.push_back("Drama");
    generos.push_back("Crime");
    Pelicula TheGodfather("The Godfather",generos);//3
    peliculas.push_back(TheGodfather);

    generos.clear();
    generos.push_back("Drama");
    generos.push_back("Comedy");
    Pelicula ForrestGump("Forrest Gump",generos);//4
    peliculas.push_back(ForrestGump);

    generos.clear();
    generos.push_back("Animation");
    generos.push_back("Romance");
    generos.push_back("Musical");
    Pelicula Sirenita("La Sirenita",generos);//5
    peliculas.push_back(Sirenita);

    generos.clear();
    generos.push_back("Adventure");
    generos.push_back("Action");
    Pelicula IndianaJones("Indiana Jones",generos);//6
    peliculas.push_back(IndianaJones);

    generos.clear();
    generos.push_back("Comedy");
    Pelicula TheHangover("The Hangover", generos);//7
    peliculas.push_back(TheHangover);

    generos.clear();
    generos.push_back("Science Fiction");
    generos.push_back("Action");
    Pelicula TheMatrix("The Matrix", generos);//8
    peliculas.push_back(TheMatrix);

    generos.clear();
    generos.push_back("Adventure");
    generos.push_back("Fantasy");
    Pelicula TheHobbit("The Hobbit", generos);//9
    peliculas.push_back(TheHobbit);

    generos.clear();
    generos.push_back("Horror");
    generos.push_back("Thriller");
    generos.push_back("Mystery");
    Pelicula TheShining("The Shining", generos);//10
    peliculas.push_back(TheShining);

    generos.clear();
    generos.push_back("Animation");
    generos.push_back("Adventure");
    Pelicula ToyStory("Toy Story", generos);//11
    peliculas.push_back(ToyStory);

    generos.clear();
    generos.push_back("Science Fiction");
    generos.push_back("Drama");
    generos.push_back("War");
    Pelicula BladeRunner("Blade Runner", generos);//12
    peliculas.push_back(BladeRunner);

    generos.clear();
    generos.push_back("Fantasy");
    generos.push_back("Adventure");
    Pelicula HarryPotter("Harry Potter", generos);//13
    peliculas.push_back(HarryPotter);

    generos.clear();
    generos.push_back("Action");
    generos.push_back("Thriller");
    Pelicula DieHard("Die Hard", generos);//14
    peliculas.push_back(DieHard);

    generos.clear();
    generos.push_back("Comedy");
    generos.push_back("Adventure");
    Pelicula PiratesOfTheCaribbean("Pirates of the Caribbean", generos);//15
    peliculas.push_back(PiratesOfTheCaribbean);

    generos.clear();
    generos.push_back("Mystery");
    generos.push_back("Crime");
    Pelicula SherlockHolmes("Sherlock Holmes", generos);//16
    peliculas.push_back(SherlockHolmes);

    generos.clear();
    generos.push_back("Animation");
    generos.push_back("Comedy");
    generos.push_back("Family");
    Pelicula Shrek("Shrek", generos);//17
    peliculas.push_back(Shrek);

    // Crear el grafo y agregar películas
    GrafoPeliculas grafo;
    grafo.agregarPelicula(Grease);
    grafo.agregarPelicula(LaLaLand);
    grafo.agregarPelicula(TheGodfather);
    grafo.agregarPelicula(ForrestGump);
    grafo.agregarPelicula(Sirenita);
    grafo.agregarPelicula(IndianaJones);
    grafo.agregarPelicula(TheHangover);
    grafo.agregarPelicula(TheMatrix);
    grafo.agregarPelicula(TheHobbit);
    grafo.agregarPelicula(TheShining);
    grafo.agregarPelicula(ToyStory);
    grafo.agregarPelicula(BladeRunner);
    grafo.agregarPelicula(HarryPotter);
    grafo.agregarPelicula(DieHard);
    grafo.agregarPelicula(PiratesOfTheCaribbean);
    grafo.agregarPelicula(SherlockHolmes);
    grafo.agregarPelicula(Shrek);

    // Agregar relaciones con peso entre películas
    grafo.agregarRelacion(Sirenita,Shrek);
    grafo.agregarRelacion(Grease,LaLaLand);
    grafo.agregarRelacion(Grease,ForrestGump);
    grafo.agregarRelacion(Grease,TheHangover);
    grafo.agregarRelacion(IndianaJones,TheMatrix);
    grafo.agregarRelacion(IndianaJones,TheHobbit);
    grafo.agregarRelacion(ToyStory,HarryPotter);
    grafo.agregarRelacion(ToyStory,Shrek);

    // Obtener componentes conexas y mostrarlas
    std::vector<std::vector<Pelicula>> componentesConexas = grafo.obtenerComponentesConexas();

    for (const auto& componente : componentesConexas) {
        std::cout << "Componente Conexa:" << std::endl;
        for (const Pelicula& pelicula : componente) {
            pelicula.mostrarInformacion();
        }
        std::cout << std::endl;
    }

    return 0;
}