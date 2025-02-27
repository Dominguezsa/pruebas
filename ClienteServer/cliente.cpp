#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}


void manejo_con_servidor(int cliente_fd) {
    std::string mensaje;
    char buffer[256];

    while (true) {
        std::cout << "Ingrese una palabra (o 'Cortar' para salir): ";
        std::getline(std::cin, mensaje);

        // Enviar mensaje al servidor
        mensaje += " "; // Agregar espacio al final
        if (send(cliente_fd, mensaje.c_str(), mensaje.size(), 0) < 0) {
            error("Error al escribir en el socket");
        }
    }
    std::cout << "Cerrando conexión..." << std::endl;

    close(cliente_fd);
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <IP_servidor> <puerto>" << std::endl;
        return 1;
    }

    const char *ip_servidor = argv[1];
    const char *puerto = argv[2];

    // Resolver la dirección del servidor
    addrinfo hints{}, *res;
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // Socket de flujo (TCP)

    if (getaddrinfo(ip_servidor, puerto, &hints, &res) != 0) {
        perror("Error en getaddrinfo");
        return 1;
    }

    // Crear socket
    int cliente_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (cliente_fd < 0) {
        perror("Error al abrir el socket");
        freeaddrinfo(res); // Liberar memoria de `getaddrinfo`
        return 1;
    }

    // Conectar al servidor
    if (connect(cliente_fd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("Error al conectar con el servidor");
        close(cliente_fd);
        freeaddrinfo(res); // Liberar memoria de `getaddrinfo`
        return 1;
    }

    freeaddrinfo(res); // Liberar memoria de `getaddrinfo`
    std::cout << "Conectado al servidor." << std::endl;

    manejo_con_servidor(cliente_fd);
    return 0;
}


void sacarOcurrencias(std::string a, std::string b ) {
    int length = b.size();
    while(true) {
        a = std::find(a.begin(), a.end(), b);
        if (a == a.end()) {
            break;
        }
        a.erase(a, length);
    }
}