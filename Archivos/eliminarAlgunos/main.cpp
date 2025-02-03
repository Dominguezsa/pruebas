#include <iostream>
#include <fstream>
#include <cstdint>
#include <arpa/inet.h> // Para ntohs y htons en sistemas Unix
#include <unistd.h> // Para ftruncate en sistemas POSIX

void processFile(const std::string& filename) {
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }
    
    uint16_t num;
    std::streampos readPos = 0, writePos = 0;
    
    while (file.seekg(readPos), file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        readPos = file.tellg();
        num = ntohs(num); // Convertir de big-endian a host-endian
        
        if (num % 3 != 0) {
            num = htons(num); // Convertir de host-endian a big-endian
            file.seekp(writePos);
            file.write(reinterpret_cast<char*>(&num), sizeof(num));
            writePos += sizeof(num);
        }
    }
    
    file.close();
    
    // Truncar el archivo al nuevo tamaño
    if (truncate(filename.c_str(), writePos) != 0) {
        std::cerr << "Error al truncar el archivo." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo>" << std::endl;
        return 1;
    }
    
    processFile(argv[1]);
    return 0;
}
