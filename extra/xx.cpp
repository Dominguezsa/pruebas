#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

void compute_powers(const std::vector<int>& input, std::vector<int>& output, int start, int end) {
    for (int i = start; i < end; ++i) {
        output[i] = std::pow(2, input[i]);
    }
}

int main() {
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8}; // Vector de entrada
    std::vector<int> output(input.size()); // Vector de salida del mismo tamaño

    int mid = input.size() / 2; // Punto de división del trabajo

    // Crear dos hilos para procesar mitades del vector
    std::thread t1(compute_powers, std::cref(input), std::ref(output), 0, mid);
    std::thread t2(compute_powers, std::cref(input), std::ref(output), mid, input.size());

    // Esperar a que los hilos terminen
    t1.join();
    t2.join();

    // Mostrar resultado
    for (int num : output) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
