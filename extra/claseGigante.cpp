#include <iostream>
#include <string>

class Gigante {
private: 
    std::string numero;

public:

    Gigante() : numero("0") {}

    explicit Gigante(const std::string& valor) {
        if (valor.size() > 1000) {
            perror("El número excede el tamaño máximo permitido de 1000 caracteres");
            return -1;
        }
            
        numero = valor;
    }

    //MOVE

    Gigante(Gigante&& other) noexcept : numero(std::move(other.numero)) {}

    //constructor por copia

    Gigante(const Gigante& other) : numero(other.numero) {}


    Gigante& operator=(const Gigante& other) {
        if (this != &other) {
            numero = other.numero;
        }
        return *this;
    }

    Gigante operator+(const Gigante& other) const {
        Gigante resultado;
        //convierto los string a int
        int a = std::stoi(numero);
        int b = std::stoi(other.numero);
        //sumo los int
        int c = a + b;
        //convierto el int a string
        resultado.numero = std::to_string(c);
        if (resultado.numero.size() > 1000) {
            throw std::overflow_error("Resultado excede el tamaño máximo permitido de 1000 caracteres");
        }
        return resultado;
    }

    friend std::ostream& operator<<(std::ostream& os, const Gigante& gigante) {
        os << gigante.numero;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Gigante& gigante) {
        is >> gigante.numero;
        return is;
    }

    bool operator==(const Gigante& other) {
        return numero == other.numero;
    }

    explicit operator unsigned int() const {
        return static_cast<unsigned int>(std::stoul(numero));
    }
};

class Nodo {
public:
    Gigante data;
    Nodo* next;
    Nodo* prev;

    Nodo(const Gigante& data) : data(data), next(nullptr), prev(nullptr) {}
};

class ListaDoble {
private:
    Nodo* head;
    Nodo* tail;

public:
    ListaDoble() : head(nullptr), tail(nullptr) {}

    ~ListaDoble() {
        Nodo* current = head;
        while (current != nullptr) {
            Nodo* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_front(const Gigante& data) {
        Nodo* new_node = new Nodo(data);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    void push_back(const Gigante& data) {
        Nodo* new_node = new Nodo(data);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
    }

    void pop_front() {
        if (head == nullptr) return;
        Nodo* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }

    void pop_back() {
        if (tail == nullptr) return;
        Nodo* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
    }

    bool empty() const {
        return head == nullptr;
    }

    void print() const {
        Nodo* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
        }

    friend std::ostream& operator<<(std::ostream& os, const ListaDoble& lista) {
        Nodo* current = lista.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
        }

    friend std::istream& operator>>(std::istream& is, ListaDoble& lista) {
        Gigante data;
        while (is >> data) {
            lista.push_back(data);
        }
        return is;
        }
};

class Guerrero {
private:
    int vida;
    std::string nombre;

public:
    Guerrero(const std::string& nombre, int vida) : nombre(nombre), vida(vida) {}

    virtual void atacar(Guerrero& other) {}

    void recibirAtaque(int ataque) {
        vida = vida - ataque;
        if (vida <= 0) {
            std::cout << "El guerrero " << nombre << " ha muerto" << std::endl;
        }
    }

    int getVida() const {
        return vida;
    }
};


#define VIDA_GIGANTE 100

class GiganteGuerrero : public Guerrero {


public:

    GiganteGuerrero(const std::string& nombre) : Guerrero(nombre, VIDA_GIGANTE) {}

    void atacar(Guerrero& other) override {
       other.recibirAtaque(100);
    }
};

class Mago : public Guerrero {

public:

    Mago(const std::string& nombre) : Guerrero(nombre, 50) {}

    void atacar(Guerrero& other) override {
        other.recibirAtaque(50);
    }
};


//implementar una funcion que recibe dos lista y devuelve una nueva duplicando los elementos de la primera que no estan en la segunda

std::list<T> duplicarElementos(const std::list<T>& lista1, const std::list<T>& lista2) {
    std::list<T> resultado;
    for (const T& elemento : lista1) {
        if (std::find(lista2.begin(), lista2.end(), elemento) != lista2.end()) {
            resultado.push_back(elemento);
        }
        resultado.push_back(elemento);

    }
    return resultado;
}