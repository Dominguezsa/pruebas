int main(int argc,char* argv[]){
    if argc !=2 error

    struct adddrinfo hints{}, *res;

    hints.ai family = ad_inet;
    ai_socktype = sock_stream
    ai_flags = ai_passive;

    char * puerto = argv[1];
    char* ip = argv[2];

    if getaddrinfo(ip, puerto, &hints, &Res) !=0)
        return


    int server_fd = socket(res->family, socktype, protocol)

    if bind(server_fd, res addr,res  adrrlen )<0 close freeadrrinfo return

    if listen( ) <0 close freeaddrinfo return


    aceptar_Conexiones(server_fd);
    shutdown(server_fd, SHUT_RDWR);
    close
    freeadrr
    return
}



void aceptar_conexiones(int server_fd) {
    std::vector<ManejarCliente> vector;
    try {
        while(true) {
            int client_fd = accept(server_fd, nullptr, nullptr)
            
            ManejarCliente(clientefd) cliente;
            vector.push_back(cliente);
        }
        
    catch(std::exception e) {
        for (auto& manejo: vector) {
            manejo.finalizar();
        }
    }
}






