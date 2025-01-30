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

        if (mensaje.find("Cortar") != std::string::npos) {
            std::cout << "Finalizando conexión con el servidor." << std::endl;
            break;
        }

        // Leer respuesta del servidor
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_leidos = recv(cliente_fd, buffer, sizeof(buffer), 0);
        if (bytes_leidos < 0) {
            error("Error al leer del socket");
        }
        if (bytes_leidos == 0) {
            std::cout << "Conexión cerrada por el servidor." << std::endl;
            break;
        }

        std::cout << "Respuesta del servidor: " << buffer << std::endl;
    }

    close(cliente_fd);
    return 0;
}
