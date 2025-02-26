#include <stdio.h>
#include <stdlib.h>

int Adelantar(FILE *f, unsigned OffsetTo, unsigned OffsetFrom, unsigned Length) {
    if (!f) return -1;  // Verificar si el archivo es válido

    unsigned char *buffer = malloc(Length);
    if (!buffer) return -2;  // Error de asignación de memoria

    // Leer desde OffsetFrom
    if (fseek(f, OffsetFrom, SEEK_SET) != 0) {
        free(buffer);
        return -3;
    }
    if (fread(buffer, 1, Length, f) != Length) {
        free(buffer);
        return -4;
    }

    // Escribir en OffsetTo
    if (fseek(f, OffsetTo, SEEK_SET) != 0) {
        free(buffer);
        return -5;
    }
    if (fwrite(buffer, 1, Length, f) != Length) {
        free(buffer);
        return -6;
    }

    free(buffer);
    return 0;  // Operación exitosa
}
