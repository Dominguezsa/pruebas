#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread> // Para los hilos

void error(const std::string &mensaje) {
    std::cerr << mensaje << std::endl;
    exit(1);
}

// Función para manejar la lógica de cada cliente
void manejar_cliente(int cliente_fd) {
    char buffer[1]; // Leer un byte a la vez
    std::string mensajeAcumulado;

    while (true) {
        ssize_t bytes_leidos = read(cliente_fd, buffer, 1);
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
            ssize_t bytes_enviados = write(cliente_fd, respuesta.c_str(), respuesta.length());
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
    close(cliente_fd);
    std::cout << "Conexión cerrada." << std::endl;
}

// Función para aceptar conexiones y crear hilos para cada cliente
void aceptar_conexiones(int servidor_fd) {
    while (true) {
        int cliente_fd = accept(servidor_fd, nullptr, nullptr);
        if (cliente_fd < 0) {
            error("Error al aceptar la conexión");
        }
        std::cout << "Cliente conectado." << std::endl;

        // Crear un hilo para manejar al cliente
        std::thread hilo_cliente(manejar_cliente, cliente_fd);
        hilo_cliente.detach(); // El hilo se maneja por separado
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <puerto> <yes/no>" << std::endl;
        return 1;
    }

    int puerto = std::stoi(argv[1]);
    std::string aceptar_varios = argv[2];

    // Crear socket
    int servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor_fd < 0) {
        error("Error al abrir el socket");
    }

    // Configurar la dirección del servidor
    sockaddr_in direccion_servidor{};
    direccion_servidor.sin_family = AF_INET;
    direccion_servidor.sin_addr.s_addr = INADDR_ANY;
    direccion_servidor.sin_port = htons(puerto);

    // Asociar socket con el puerto
    if (bind(servidor_fd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) {
        error("Error en el bind");
    }

    // Ponerse en escucha
    if (listen(servidor_fd, 1) < 0) {
        error("Error en el listen");
    }
    std::cout << "Esperando conexión en el puerto " << puerto << "..." << std::endl;

    if (aceptar_varios == "yes") {
        // Aceptar múltiples conexiones en un hilo
        aceptar_conexiones(servidor_fd);
    } else if (aceptar_varios == "no") {
        // Aceptar solo una conexión
        int cliente_fd = accept(servidor_fd, nullptr, nullptr);
        if (cliente_fd < 0) {
            error("Error al aceptar la conexión");
        }
        std::cout << "Cliente conectado." << std::endl;

        // Manejar el cliente en el hilo principal
        manejar_cliente(cliente_fd);
    } else {
        std::cerr << "El segundo argumento debe ser 'yes' o 'no'." << std::endl;
        return 1;
    }
    close(servidor_fd);
    return 0;
}
