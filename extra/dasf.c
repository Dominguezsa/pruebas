#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
  #include <io.h>
#else
  #include <unistd.h>
#endif

// Función para convertir una cadena de 4 caracteres en base 12 a entero.
int base12_to_int(const char *numStr) {
    int result = 0;
    for (int i = 0; i < 4; i++) {
        char c = numStr[i];
        int digit;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c == 'A' || c == 'a')
            digit = 10;
        else if (c == 'B' || c == 'b')
            digit = 11;
        result = result * 12 + digit;
    }
    return result;
}







/*

int main(void) {
    FILE *fp = fopen("numeros12.txt", "r+b");
    if (!fp) {
        perror("Error abriendo archivo");
        return EXIT_FAILURE;
    }

    // Obtener tamaño original del archivo.
    fseek(fp, 0, SEEK_END);
    long original_size = ftell(fp);

    int num_groups = original_size / 4;

    // Primer pase: calcular el nuevo tamaño.
    long new_size = num_groups * 5;
    char buffer[5];
    buffer[4] = '\0'; // Terminador para manejar la cadena

       long write_pos = new_size;
    fprintf(stdout, "Nuevo tamaño: %ld\n", new_size);


    for (int i = num_groups - 1; i >= 0; i--) {
        // Ubicar la posición de lectura del grupo i.
        long read_pos = i * 4;
        fseek(fp, read_pos, SEEK_SET);
        size_t leidos = fread(buffer, 1, 4, fp);
        
        if (leidos != 4) {
            perror("Error leyendo archivo en segundo pase");
            fclose(fp);
            return EXIT_FAILURE;
        }
        int valor = base12_to_int(buffer);

        char temp[6];
        sprintf(temp, "%05d", valor);
        // Ajustar la posición de escritura.
        write_pos -= 5;
        fseek(fp, write_pos, SEEK_SET);
        size_t escritos = fwrite(temp, 1, 5, fp);
        if (escritos != (size_t )5) {
            perror("Error escribiendo en el archivo en segundo pase");
            fclose(fp);
            return EXIT_FAILURE;
        }
    }

  
    int fd = fileno(fp);
    if (ftruncate(fd, new_size) != 0) {
        perror("Error truncando archivo");
        fclose(fp);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}


*/


int main(void) {
    FILE *fp = fopen("numeros12.txt", "r+b");
    if (!fp) {
        perror("Error abriendo archivo");
        return EXIT_FAILURE;
    }

    // Obtener tamaño original del archivo.
    fseek(fp, 0, SEEK_END);
    long original_size = ftell(fp);

    int num_groups = original_size / 4;

    // Primer pase: calcular el nuevo tamaño.
    long new_size = num_groups * 5;
    char buffer[5];
    buffer[4] = '\0'; // Terminador para manejar la cadena

    fseek(fp, 100, SEEK_SET);
    fwrite("1", 1, 1, fp);



  
    int fd = fileno(fp);
    if (ftruncate(fd, new_size) != 0) {
        perror("Error truncando archivo");
        fclose(fp);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}