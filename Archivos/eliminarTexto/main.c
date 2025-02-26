#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    FILE *archivo = fopen("archivo.txt", "r+");
    if (archivo == NULL){return 1;}

    char linea[1024];
    long write_pos = 0, read_pos = 0;
    fseek(archivo, 0, SEEK_END);
    int size = ftell(archivo);
    fprintf(stdout, "Tamaño original: %d\n", size);
    fseek(archivo, 0, SEEK_SET);
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        read_pos = ftell(archivo);

        if (strchr(linea, ' ') != NULL)
        {
            fseek(archivo, write_pos, SEEK_SET);
            fputs(linea, archivo);
            write_pos = ftell(archivo);
        }
        fseek(archivo, read_pos, SEEK_SET);
    }

    ftruncate(fileno(archivo), write_pos);
    fclose(archivo);
    
    return 0;
}

