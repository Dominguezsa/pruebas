#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <cstdint>

/*
int main() {
    FILE * archivo = fopen("a.txt", "r+b");
    if (!archivo) {
        perror("Error abriendo archivo");
        return EXIT_FAILURE;
    }
    fseek(archivo, 0, SEEK_END);
    long tamaño_original = ftell(archivo);
    int pos2 = tamaño_original;
    for (int i = 0; i < (tamaño_original/2); i++) {
       char read1[2];
       char read2[2];
       fseek(archivo, i, SEEK_SET);
       fread(read1, 1, 1, archivo);
       pos2--;
       fseek(archivo, pos2, SEEK_SET);
       fread(read2, 1,1, archivo);

       fseek(archivo, i, SEEK_SET);
       fwrite(read2, 1, 1, archivo);
       fseek(archivo, pos2, SEEK_SET);
       fwrite(read1, 1, 1, archivo);
    }
    fclose(archivo);
    return 0;
}

*/


//vos lees int16_t y escribis hexa4


void int16_to_hexa4(int16_t num, char* hexa4) {
    hexa4[4] = '\0';
    for (int i = 3; i >= 0; i--) {
        int digit = num % 16;
        hexa4[i] = (digit < 10) ? ('0' + digit) : ('A' + (digit - 10));
        num /= 16;
    }
}

#include <arpa/inet.h>

int main() {
    FILE * archivo = fopen("b.bin", "r+b");
    if (!archivo) {
        perror("Error abriendo archivo");
        return EXIT_FAILURE;
    }
    fseek(archivo, 0, SEEK_END);
    long tamaño_original = ftell(archivo);
    int numeros = tamaño_original / 2;
    int nuevo_tamaño = numeros * 4;
    int write_pos = nuevo_tamaño;
    fprintf(stdout, "Nuevo tamaño: %d\n", nuevo_tamaño);
    for(int i = numeros - 1; i >= 0; i--) {
        long read_pos = i * 2;
        fseek(archivo, read_pos, SEEK_SET);
        int16_t num;
        fread(&num, sizeof(int16_t), 1, archivo);
        char hexa4[5];
        fprintf(stdout, "Numero leido: %d\n", num);
        int16_to_hexa4(num, hexa4);
        fprintf(stdout, "Hexa4: %s\n", hexa4);
        write_pos -= 4;
        fseek(archivo, write_pos, SEEK_SET);
        fwrite(hexa4, 1, 4, archivo);
    }
    ftruncate(fileno(archivo), nuevo_tamaño);
    fclose(archivo);
    return 0;
}
