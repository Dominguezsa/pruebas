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

// Convierte un número en base 7 (almacenado como 3 bytes) a decimal
int obtener_decimal(const std::vector<uint8_t>& bytes) {
    int decimal = 0;
    for (size_t i = 0; i < bytes.size(); i++) {
        decimal += bytes[i] * obtener_cuadrado(7, bytes.size() - i - 1);
    }
    return decimal;
}

// Convierte un número en decimal a base 7 (3 bytes)
std::vector<uint8_t> decimal_a_base7(int numero) {
    std::vector<uint8_t> base7(3);
    for (int i = 2; i >= 0; i--) {
        base7[i] = numero % 7;
        numero /= 7;
    }
    return base7;
}

int main() {
    std::string filename = "nros7.bin";

    // Abrimos el archivo en modo lectura y escritura (actualización)
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::vector<uint8_t> bytes(3);
    int numero_actual, numero_auxiliar;
    std::streampos read_pos = 0;  // Posición de lectura
    std::streampos write_pos = 0; // Posición de escritura

    while (file.seekg(read_pos), file.read(reinterpret_cast<char*>(bytes.data()), 3)) {
        numero_actual = obtener_decimal(bytes);
        read_pos = file.tellg();  // Guardar la posición después de leer 3 bytes

        if (numero_actual % 5 == 0) {
            // Leer el siguiente número y guardarlo en número_auxiliar
            if (file.read(reinterpret_cast<char*>(bytes.data()), 3)) {
                numero_auxiliar = obtener_decimal(bytes);
                read_pos = file.tellg();
            } else {
                // Si no hay más números, solo duplicamos el actual y terminamos
                numero_auxiliar = -1;
            }

            // Escribir número_actual (se duplica)
            file.seekp(write_pos);
            std::vector<uint8_t> base7_actual = decimal_a_base7(numero_actual);
            file.write(reinterpret_cast<char*>(base7_actual.data()), 3);
            write_pos = file.tellp();

            // Escribir nuevamente número_actual (duplicado)
            file.write(reinterpret_cast<char*>(base7_actual.data()), 3);
            write_pos = file.tellp();

            // Si hay número auxiliar, escribirlo
            if (numero_auxiliar != -1) {
                std::vector<uint8_t> base7_aux = decimal_a_base7(numero_auxiliar);
                file.write(reinterpret_cast<char*>(base7_aux.data()), 3);
                write_pos = file.tellp();
            }

        } else {
            // Si el número no es múltiplo de 5, lo copiamos sin cambios
            file.seekp(write_pos);
            file.write(reinterpret_cast<char*>(bytes.data()), 3);
            write_pos = file.tellp();
        }
    }

    file.close();
    std::cout << "Archivo procesado y modificado correctamente." << std::endl;
    return 0;
}
