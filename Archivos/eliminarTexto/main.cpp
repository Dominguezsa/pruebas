#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

bool esLineaDeUnaPalabra(const std::string& linea) {
    std::istringstream iss(linea);
    std::string palabra;
    int contador = 0;
    
    while (iss >> palabra) {
        contador++;
        if (contador > 1) {
            return false;
        }
    }
    return contador == 1;
}

void procesarArchivoEnLugar(const std::string& archivo) {
    std::fstream archivoStream(archivo, std::ios::in | std::ios::out);
    if (!archivoStream) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }
    
    std::string linea;
    std::streampos lectura = 0, escritura = 0;
    
    while (archivoStream.seekg(lectura), std::getline(archivoStream, linea)) {
        lectura = archivoStream.tellg();
        if (!esLineaDeUnaPalabra(linea)) {
            archivoStream.seekp(escritura);
            archivoStream << linea << '\n';
            escritura = archivoStream.tellp();
        }
    }
    
    archivoStream.close();
    std::fstream truncar(archivo, std::ios::in | std::ios::out);
    truncar.seekp(escritura);
    truncar.close();
    if (truncate(archivo.c_str(), escritura) != 0) {
        std::cerr << "Error al truncar el archivo." << std::endl;
    }
}

int main() {
    std::string archivo = "entrada.txt";
    
    procesarArchivoEnLugar(archivo);
    
    std::cout << "Proceso completado en el archivo: " << archivo << std::endl;
    return 0;
}
