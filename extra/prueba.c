#include <stdio.h>
#include <stdint.h>

int main() {
    int16_t numbers[] = {0, 1, 2, 3, 4};
    FILE *file = fopen("b.bin", "wb");
    
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    
    fwrite(numbers, sizeof(int16_t), 5, file);
    fclose(file);
    
    return 0;
}
