#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main() {
    std::ofstream file("nros7.bin", std::ios::binary);
    if (!file) {
        std::cerr << "Error al crear el archivo." << std::endl;
        return 1;
    }

    // Declaramos los valores de forma separada
    uint8_t bytes[] = {1, 0, 0, 0, 2, 1, 0, 4, 0, 0, 4, 2};

    // Escribimos los valores en el archivo
    file.write(reinterpret_cast<char*>(bytes), sizeof(bytes));

    file.close();
    std::cout << "Archivo 'nros7.bin' creado correctamente." << std::endl;
    return 0;
}
