#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h> // Para ntohs y htons en sistemas Unix
#include <unistd.h> // Para ftruncate en sistemas POSIX

void processFile(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Error al abrir el archivo");
        return;
    }
    
    uint16_t num;
    long readPos = 0, writePos = 0;
    
    while (fseek(file, readPos, SEEK_SET) == 0 && fread(&num, sizeof(num), 1, file) == 1) {
        readPos = ftell(file);
        num = ntohs(num); // Convertir de big-endian a host-endian
        
        if (num % 3 != 0) {
            num = htons(num); // Convertir de host-endian a big-endian
            fseek(file, writePos, SEEK_SET);
            fwrite(&num, sizeof(num), 1, file);
            writePos += sizeof(num);
        }
    }
    
    fclose(file);
    
    // Truncar el archivo al nuevo tamaño
    if (truncate(filename, writePos) != 0) {
        perror("Error al truncar el archivo");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
        return 1;
    }
    
    processFile(argv[1]);
    return 0;
}
