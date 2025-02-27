#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread> // Para los hilos
#include <fcntl.h>
#include <errno.h>
#include <vector>

void error(const std::string &mensaje) {
    std::cerr << mensaje << std::endl;
    exit(1);
}


class ManejoCliente {
private:
    int cliente_fd;
    int numero_cliente;

public:

    ManejoCliente(int cliente_fd, int numero_cliente) : cliente_fd(cliente_fd), numero_cliente(numero_cliente) {}

    void manejar_cliente(){
        char buffer[1]; // Leer un byte a la vez
        std::string mensajeAcumulado;
        try {
            while (true) {
                ssize_t bytes_leidos = recv(cliente_fd, buffer, sizeof(buffer), 0);
                if (bytes_leidos < 0) {
                    error("Error al leer del socket");
                }
                if (bytes_leidos == 0) {
                    // Conexión cerrada por el cliente
                    break;
                }
                char caracter = buffer[0];
                if (caracter == ' ') {
                    // Procesar la palabra acumulada
                    if (mensajeAcumulado == "Cortar") {
                        std::cout << "Recibido 'Cortar'. Finalizando conexión." << std::endl;
                        break;
                    }
        
                    // Enviar la longitud de la palabra
                    std::string respuesta = std::to_string(mensajeAcumulado.length()) + " ";
        
                    ssize_t bytes_enviados = send(cliente_fd, respuesta.c_str(), respuesta.length(), 0);
        
                    if (bytes_enviados < 0) {
                        error("Error al escribir en el socket");
                    }
        
                    // Limpiar el acumulador
                    mensajeAcumulado.clear();
                } else {
                    // Seguir acumulando caracteres
                    mensajeAcumulado += caracter;
                }
            }
            std::cout << "Conexión cerrada." << std::endl;
        }catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void finalizarEjecucion() {
        shutdown(cliente_fd, SHUT_RDWR);
        close(cliente_fd);
    }
};


class AceptarConexiones {
private:
    int servidor_fd;
    std::vector<ManejoCliente> hilos;
public:

    AceptarConexiones(int servidor_fd) : servidor_fd(servidor_fd) {}

    void aceptar_conexiones() {
        int numero_cliente = 1;
        try {
            while (true) {
                int cliente_fd = accept(servidor_fd, nullptr, nullptr);
                if (cliente_fd < 0) {
                    error("Error al aceptar la conexión");
                }
                std::cout << "Cliente conectado." << std::endl;

                // Crear un hilo para manejar al cliente
                ManejoCliente cliente(cliente_fd, numero_cliente);
                hilos.push_back(cliente);
                cliente.manejar_cliente();
                numero_cliente++;
            }
            finalizar();
        }
        catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void finalizar() {
        for (auto& hilo : hilos) {
            hilo.finalizarEjecucion();
        }
        hilos.clear();
        shutdown(servidor_fd, SHUT_RDWR);
        close(servidor_fd);
    }  
};



int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <puerto> <yes/no>" << std::endl;
        return 1;
    }

    int puerto = std::stoi(argv[1]);
    std::string aceptar_varios = argv[2];

    // Obtener información de la dirección
    struct addrinfo hints{}, *res;
    hints.ai_family = AF_INET; // Permite tanto IPv4 como IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // Usar la dirección del servidor local

    char *puerto_str = argv[1];

    if (getaddrinfo(nullptr, puerto_str, &hints, &res) != 0) {
        error("Error al obtener información de la dirección");
    }

    // Crear socket
    int servidor_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (servidor_fd < 0) {
        error("Error al abrir el socket");
    }

    // Permitir la reutilización del puerto
    //int optval = 1;
    //if (setsockopt(servidor_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    //    error("Error al establecer opciones de socket");
    // }

    // Realizar el bind
   if (bind(servidor_fd, res->ai_addr, res->ai_addrlen) < 0) {
        std::cerr << "Error en el bind";
        close(servidor_fd);
        freeaddrinfo(res);
        return 1;
    }

    // Escuchar en el socket
    if (listen(servidor_fd, 1) < 0) {
        error("Error en el listen");
    }
    fprintf(stdout, "Escuchando en el puerto %d...\n", puerto);

    AceptarConexiones aceptar_conexiones(servidor_fd);
    aceptar_conexiones.aceptar_conexiones();
    freeaddrinfo(res); // Liberar la memoria de addrinfo
    return 0;
}
