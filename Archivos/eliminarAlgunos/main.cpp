#include <iostream>
#include <fstream>
#include <cstdint>
#include <arpa/inet.h> // Para ntohs y htons en sistemas Unix
#include <unistd.h> // Para ftruncate en sistemas POSIX




#include <iostream>

void modificarReferencia(int &a) {
    a = 10;
}

void modificarPuntero(int *a) {
    *a = 10;
}

int main() {
    int a = 5;
    int &ref = a;
    modificarReferencia(ref);
    std::cout << ref << std::endl; // Imprime 10

    int *pun = &a;
    modificarPuntero(pun);
    std::cout << pun << std::endl; // Imprime 10

    return 0;
}


#include <iostream>

// Template general para valores normales
template <typename T>
class Contenedor {
private:
    T valor;
public:
    Contenedor(T v) : valor(v) {}

    void mostrar() {std::cout << "Valor almacenado: " << valor << "\n";}
};

// Especialización parcial para punteros
template <typename T>
class Contenedor<T*> {
private:
    T* valor;
public:
    Contenedor(T* v) : valor(v) {}

    void mostrar() {
        if (valor){std::cout << "Puntero almacenado, valor apuntado: " << *valor << "\n";}
        else std::cout << "Puntero almacenado es NULL\n";
    }
};