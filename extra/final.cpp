#include <iostream>

// Clase base
class Animal {
public:
    virtual void hacerSonido() const { // Función virtual para polimorfismo
        std::cout << "El animal hace un sonido.\n";
    }
};

// Clase derivada: Perro
class Perro : public Animal {
public:
    void hacerSonido() const override { // Sobreescribe la función
        std::cout << "El perro ladra: ¡Guau guau!\n";
    }
};

// Clase derivada: Gato
class Gato : public Animal {
public:
    void hacerSonido() const override {
        std::cout << "El gato maúlla: ¡Miau miau!\n";
    }
};
/*
int main() {
    Animal* a1 = new Perro(); // Polimorfismo: tratamos un Perro como un Animal
    Animal* a2 = new Gato();  // Polimorfismo: tratamos un Gato como un Animal

    a1->hacerSonido(); // Llamará a Perro::hacerSonido()
    a2->hacerSonido(); // Llamará a Gato::hacerSonido()

    delete a1;
    delete a2;

    return 0;
}
*/

#include <iostream>
#include <cstdlib> // Para strtol

void ValorHex(char *hex, int *ent) {
    *ent = std::strtol(hex, nullptr, 12);
}

int main() {
    char hex[] = "0000011"; // Ejemplo de número hexadecimal
    int valor;
    
    ValorHex(hex, &valor);
    
    std::cout << "El valor decimal es: " << valor << std::endl;
    
    return 0;
}
