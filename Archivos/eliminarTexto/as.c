#include <stdio.h>
#include <ctype.h>

int contar_palabras(const char *str) {
    int count = 0;
    int en_palabra = 0; // Indica si estamos dentro de una palabra

    while (*str) {
        if (isspace((unsigned char)*str)) {
            en_palabra = 0; // Si encontramos un espacio, terminamos una palabra
        } else if (!en_palabra) {
            en_palabra = 1; // Encontramos el inicio de una nueva palabra
            count++;
        }
        str++;
    }

    return count;
}

int main() {
    char texto[] = "  Hola, esto es una   prueba.  ";
    printf("Número de palabras: %d\n", contar_palabras(texto));
    return 0;
}
