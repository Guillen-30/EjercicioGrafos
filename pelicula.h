#include <iostream>
#include <vector>
#include <string>

class Pelicula {
    private:
        std::string titulo;
        std::vector<std::string> generos;
    public:
        // Constructor de la clase Pelicula
        Pelicula(const std::string& titulo, const std::vector<std::string>& generos) {
            this->titulo = titulo;
            this->generos = generos;
        }

        // Método para obtener el título de la película
        std::string getTitulo() const {
            return titulo;
        }

        // Método para obtener los géneros de la película
        std::vector<std::string> getGeneros() const {
            return generos;
        }

        // Método para agregar un género a la película
        void agregarGenero(const std::string& genero) {
            generos.push_back(genero);
        }

        // Método para mostrar información de la película
        void mostrarInformacion() const {
            std::cout << "Título: " << titulo << std::endl;
            std::cout << "Géneros: ";
            for (const std::string& genero : generos) {
                std::cout << genero << " ";
            }
            std::cout << std::endl;
        }
};

