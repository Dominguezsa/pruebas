#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

// Función para calcular potencias de 7
int obtener_cuadrado(int n, int exponente) {
    int resultado = 1;
    for (int i = 0; i < exponente; i++) {
        resultado *= n;
    }
    return resultado;
}

// Convierte un número en base 7 (almacenado como bytes) a decimal
int obtener_decimal(const std::vector<uint8_t>& bytes) {
    int decimal = 0;
    for (size_t i = 0; i < bytes.size(); i++) {
        decimal += bytes[i] * obtener_cuadrado(7, bytes.size() - i - 1);
    }
    return decimal;
}

int main() {
    std::ifstream file("nros7.bin", std::ios::binary);
    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::vector<uint8_t> bytes;
    uint8_t byte;

    // Leer todos los bytes del archivo
    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        bytes.push_back(byte);
    }
    file.close();

    // Verificar que el tamaño de bytes sea múltiplo de 3 (ya que cada número es de 3 símbolos)
    if (bytes.size() % 3 != 0) {
        std::cerr << "Error: El archivo no contiene múltiplos de 3 bytes." << std::endl;
        return 1;
    }

    // Convertir y mostrar los números
    std::cout << "Números en decimal:" << std::endl;
    for (size_t i = 0; i < bytes.size(); i += 3) {
        std::vector<uint8_t> numBase7 = {bytes[i], bytes[i + 1], bytes[i + 2]};
        std::cout << obtener_decimal(numBase7) << " ";
    }
    std::cout << std::endl;

    return 0;
}
