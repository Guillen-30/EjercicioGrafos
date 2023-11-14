#ifndef _PELICULA_
#define _PELICULA_ 1

#include <iostream>
#include <vector>
#include <string>

class Pelicula {
private:
    std::string* titulo;
    std::vector<std::string>* generos;
    int id=-1;

public:
    // Constructor de la clase Pelicula
    Pelicula(const std::string& titulo, const std::vector<std::string>& generos) {
        this->titulo = new std::string(titulo);
        this->generos = new std::vector<std::string>(generos);
    }

    // Copy constructor
    Pelicula(const Pelicula& other) {
        this->titulo = new std::string(*other.titulo);
        this->generos = new std::vector<std::string>(*other.generos);
    }

    // Destructor
    ~Pelicula() {
        delete titulo;
        delete generos;
    }

    // Assignment operator
    Pelicula& operator=(const Pelicula& other) {
        if (this != &other) {
            delete titulo;
            delete generos;
            titulo = new std::string(*other.titulo);
            generos = new std::vector<std::string>(*other.generos);
        }
        return *this;
    }

    // Método para obtener el título de la película
    std::string getTitulo() const {
        return *titulo;
    }

    // Método para obtener los géneros de la película
    std::vector<std::string> getGeneros() const {
        return *generos;
    }

    // Método para agregar un género a la película
    void agregarGenero(const std::string& genero) {
        generos->push_back(genero);
    }

    // Método para mostrar información de la película
    void mostrarInformacion() const {
        std::cout << "Título: " << *titulo << std::endl;
        std::cout << "Géneros: ";
        for (const std::string& genero : *generos) {
            std::cout << genero << " ";
        }
        std::cout << std::endl;
    }

    void mostrarTitulo() const{
        std::cout << "Título: " << *titulo << std::endl;
    }

    void setId(int id){
        this->id = id;
    }
    int getId(){
        return id;
    }
};

#endif