

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <puerto> <yes/no>" << std::endl;
        return 1;
    }
    struct addrinfo hints{}, *res;
    hints.ai_family = af_inet;
    hints.ai_socktype = sock_stream;
    hints.ai_flags = ai_passive;

    char* puerto = argv[1];

    if (getaddrinfo(nullptr, puerto, &hints, &res )!= 0 ) {return}

    int server_fd = socket(res->ai_family, socktype, ai_protocol)

    //if <0 return

    if bind(server_fd, res->ai_addr, res->ai_addrlen) <0 return CLOSE Y FREEADR

    if listen(Server_fd, 1) <0 return.

    void manejar_cliente();
    close(server_fd);

}


void manejar_cliente(int server_fd) {
    int cliente_fd = accept(server_fd, nullptr, nullptr);
    if (cliente_fd<0) return 

    char buffer[1];
    std::string mensajeAcumulado;
    while(true){
        ssize_t bytes_leidos = recv(cliente_fd, buffer, sizeof(buffer),0)

        if bytes_Leidos <0 close(cliente) return
        if bytes = 0 break

        char caracter = buffer[0];
        if (caracter == ' ') {
            if mensajeAcumulado == "Cortar" break
            }else {
                 std::string respuesta = std::to_string(mensajeAcumulado.length()) + " ";
                  sszize_t bytes_enviados = send(cliente_fd, respuesta.c_str(), sizeof(respuesta), 0);
                    if bytes_enviados < 0 return
                  mensajeAcumulado.clear();
            }
        else{
            mensajeAcumulado += caracter;
        }
    }
    close(cliente_fd);
}

#include <iostream>
#include <string>

std::vector<std::string> obtenerPalabrasCortas(const char * s, unsigned int l) {
    std::string palabraAcumulada;
    std::vector<std::string> respuesta;
    for (auto char: s) {
        if (char == ' ') {
            if (palabraAcumulada.size() <= l ){
                respuesta.append(palabraAcumulada);
                palabtaAcumulada.clear();
            }
        }else{
            palabraAcumulada += char;
        }
    }
    if (palabraAcumulada.size() <= l ){
        respuesta.append(palabraAcumulada);
        palabtaAcumulada.clear();
    }
}


#ifdef LOG_ENABLED
    #define LOG(m) printf("%s\n", m)
#else
    #define LOG(m)
#endif



#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

std::vector<int> vec;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

void producer() {
    for (int i = 1; i <= 100; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        vec.push_back(i);
        cv.notify_one();  // Notifica al consumidor
    }
    std::unique_lock<std::mutex> lock(mtx);
    finished = true;
    cv.notify_one();  // Notifica al consumidor que terminó
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !vec.empty() || finished; });

        if (vec.empty() && finished) {
            break;
        }

        if (!vec.empty()) {
            int value = vec.back();
            vec.pop_back();
            std::cout << "Consumido: " << value << std::endl;
        }
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}



#include <iostream>

class Sumar {
public: 
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    Sumar sumar;
    int resultado = sumar(3, 5);
    std::cout << resultado << std::endl;
    return 0;
}


#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        ++counter;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}