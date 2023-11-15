#include "grafoPelicula.h"
#include "clasePreguntas.h"

int main() {
    // Crear algunas películas
    std::vector<Pelicula*> peliculas;
    std::vector<std::string> generos; 
    generos.push_back("Romance");
    generos.push_back("Comedy");
    Pelicula*  Grease = new Pelicula("Grease",generos);//1
    peliculas.push_back(Grease);

    generos.clear();
    generos.push_back("Drama");
    generos.push_back("Romance");
    generos.push_back("Musical");
    Pelicula*  LaLaLand = new Pelicula("La La Land",generos);//2
    peliculas.push_back(LaLaLand);

    generos.clear();
    generos.push_back("Drama");
    generos.push_back("Crime");
    Pelicula*  TheGodfather = new Pelicula("The Godfather",generos);//3
    peliculas.push_back(TheGodfather);

    generos.clear();
    generos.push_back("Drama");
    generos.push_back("Comedy");
    Pelicula*  ForrestGump = new Pelicula("Forrest Gump",generos);//4
    peliculas.push_back(ForrestGump);

    generos.clear();
    generos.push_back("Animation");
    generos.push_back("Romance");
    generos.push_back("Musical");
    Pelicula*  Sirenita = new Pelicula("La Sirenita",generos);//5
    peliculas.push_back(Sirenita);

    generos.clear();
    generos.push_back("Adventure");
    generos.push_back("Action");
    Pelicula*  IndianaJones = new Pelicula("Indiana Jones",generos);//6
    peliculas.push_back(IndianaJones);

    generos.clear();
    generos.push_back("Comedy");
    Pelicula*  TheHangover = new Pelicula("The Hangover", generos);//7
    peliculas.push_back(TheHangover);

    generos.clear();
    generos.push_back("Science Fiction");
    generos.push_back("Action");
    Pelicula*  TheMatrix = new Pelicula("The Matrix", generos);//8
    peliculas.push_back(TheMatrix);

    generos.clear();
    generos.push_back("Adventure");
    generos.push_back("Fantasy");
    Pelicula*  TheHobbit = new Pelicula("The Hobbit", generos);//9
    peliculas.push_back(TheHobbit);

    generos.clear();
    generos.push_back("Horror");
    generos.push_back("Thriller");
    generos.push_back("Mystery");
    Pelicula*  TheShining = new Pelicula("The Shining", generos);//10
    peliculas.push_back(TheShining);

    generos.clear();
    generos.push_back("Animation");
    generos.push_back("Adventure");
    Pelicula*  ToyStory = new Pelicula("Toy Story", generos);//11
    peliculas.push_back(ToyStory);

    generos.clear();
    generos.push_back("Science Fiction");
    generos.push_back("Drama");
    generos.push_back("War");
    Pelicula*  BladeRunner = new Pelicula("Blade Runner", generos);//12
    peliculas.push_back(BladeRunner);

    generos.clear();
    generos.push_back("Fantasy");
    generos.push_back("Adventure");
    Pelicula*  HarryPotter = new Pelicula("Harry Potter", generos);//13
    peliculas.push_back(HarryPotter);

    generos.clear();
    generos.push_back("Action");
    generos.push_back("Thriller");
    Pelicula*  DieHard = new Pelicula("Die Hard", generos);//14
    peliculas.push_back(DieHard);

    generos.clear();
    generos.push_back("Comedy");
    generos.push_back("Adventure");
    Pelicula*  PiratesOfTheCaribbean = new Pelicula("Pirates of the Caribbean", generos);//15
    peliculas.push_back(PiratesOfTheCaribbean);

    generos.clear();
    generos.push_back("Mystery");
    generos.push_back("Crime");
    Pelicula*  SherlockHolmes = new Pelicula("Sherlock Holmes", generos);//16
    peliculas.push_back(SherlockHolmes);

    generos.clear();
    generos.push_back("Animation");
    generos.push_back("Comedy");
    generos.push_back("Family");
    Pelicula*  Shrek = new Pelicula("Shrek", generos);//17
    peliculas.push_back(Shrek);

    // Crear el grafo y agregar películas
    GrafoPeliculas grafo;
    GraphDiscover graphDiscover;
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
    grafo.agregarRelacion(LaLaLand, TheGodfather);
    grafo.agregarRelacion(TheGodfather, ForrestGump);
    grafo.agregarRelacion(ForrestGump, Grease);
    grafo.agregarRelacion(TheHangover, IndianaJones);
    grafo.agregarRelacion(TheMatrix, TheHobbit);
    grafo.agregarRelacion(TheHobbit, ToyStory);
    grafo.agregarRelacion(ToyStory, PiratesOfTheCaribbean);
    grafo.agregarRelacion(PiratesOfTheCaribbean, SherlockHolmes);
    grafo.agregarRelacion(SherlockHolmes, Shrek);
    grafo.agregarRelacion(Shrek, Grease);

    // //!Test componentes conexas

    // // Obtener componentes conexas y mostrarlas
    // std::vector<std::vector<Pelicula*>> componentesConexas = grafo.obtenerComponentesConexas();

    // for (const auto& componente : componentesConexas) {
    //     std::cout << "Componente Conexa:" << std::endl;
    //     for (const Pelicula* pelicula : componente) {
    //         pelicula->mostrarInformacion();
    //     }
    //     std::cout << std::endl;
    // }

    // //!End test componentes conexas

    // //!Test getPathsByWarshall
    std::vector<Path*>* caminos = graphDiscover.getPathsByWarshall(Grease, Shrek, &grafo);
    std::cout << "Todos los caminos entre Grease y Shrek" << endl;
    for (Path* path : *caminos) {
        std::cout << "Path: " << std::endl;
        for (Pelicula* pelicula : path->path) {
            pelicula->mostrarTitulo();
        }
        std::cout << std::endl;
    }
        
    // //!End test getPathsByWarshall

    //!Test buscarCaminoMasCorto
    Path* camino = graphDiscover.getShortestPath(Grease, Shrek, &grafo);
    std::cout << "Camino mas corto entre Grease y Shrek: " << std::endl;;
    for (Pelicula* pelicula : camino->path) {
        pelicula->mostrarTitulo();
    }
    //!End test buscarCaminoMasCorto

    return 0;
}

//TODO: Testear con Neo4j
//TODO: Hacer que nodo inicial se agregue al path en warshall