#include "Socket.h"
#include "Resolver.h"
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <cassert>


Socket::Socket(const char* hostName, const char* serviceName){
    int skt = -1;
    int s = -1;
    this->closed = true;
    //haremos un socket del tipo  cliente queu se conecta. // no hace bind ni listen.
    Resolver aResolver(hostName, serviceName, false);
    struct addrinfo* addr;
    while(aResolver.hasNext()){
        addr = aResolver.getNext();

        //si volvemos del conectar debemos cerrar el skt antes.
        if(skt != -1 ){
            ::close(skt);
        }

        // (familia del protoclo que usara, tipoCapaAplicacion, protocolo probablemente null  )
        skt = socket(addr->ai_family,  addr->ai_socktype, addr->ai_protocol);
        if (skt == -1 ){
            continue;
        }
        //si llego aca es porque el socket se creo de forma correcta intentamos conectarnos. Connect es bloqueante recordarlo.
        s = connect(skt, addr->ai_addr, addr->ai_addrlen );
        if( s == -1 ){
            continue;
        }

        //Si llegamos aca la conexion fue un exito. Seteamos el estado del -> socket en false y   -> el skt lo asignamos al atributo.
        this->closed = false;
        this->skt = skt;
        return;
    }

    // si terminamos el while es porque no nos pudimos conectar.
    int saved_errno = errno;

    if (skt != -1){
        ::close(skt);
    }
    std::string strHostName = hostName;
    std::string strServiceName = serviceName;

    std::string mensaje = "No se pudo construir el socket del cliente con  " + strHostName + strServiceName + std::to_string(saved_errno) ;
    std:: cerr << mensaje;
    throw mensaje;
}

Socket::Socket(const char* serviceName){
    int skt = -1;
    int s = -1;
    Resolver aResolver(NULL, serviceName, true);
    this->closed = true;
    struct addrinfo* addr;
    while( aResolver.hasNext() ){
        addr = aResolver.getNext();
        //si volvemos del bind
        if(skt != -1 ){
            ::close(skt);
        }

        // (familia del protocolo que usara, tipoCapaAplicacion, protocolo probablemente null  )
        skt = socket(addr->ai_family,  addr->ai_socktype, addr->ai_protocol);
        if (skt == -1 ){
            continue;
        }
        //configuramos el socket para que no falle si la direcion local que queremos levantar
        // con el servidor (bind) estaba "ocupada hace  poco".

        //El OS no sabe si hay paquetes de red aun viajando hacia el puerto y prefiere reservar el puerto
        //evitando que el proximo server se morfe paquetes que no ivan para el. le dcimos todo ok con el flag.
        // SO_REUSEADDR (del nombre reuse address)

        int optval = 1;
        s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (s == -1) {
            continue;
        }

        //Estamos en el socket tipo servidor asi que hacemos bind para enlazarlo a una ip y puerto (direccion).
        s = bind(skt, addr->ai_addr, addr->ai_addrlen );
        if ( s == -1 ){
            continue;
        }
        //Con listen asignamos la cantidad de conexiones en esperan a ser toleradas.

        s = listen(skt, 20);
        if( s == -1 ){
            continue;
        }

        //Si llegamos aca es porque salio todo ok.
        this->closed = false;
        this->skt = skt;
        return;
    }

    int saved_errno = errno;

    if (skt != -1){
        ::close(skt);
    }
    std::string strServiceName = serviceName;

    std::string mensaje = "No se pudo construir al socket del servidor al " + strServiceName + std::to_string(saved_errno) ;
    std::cerr << mensaje;
    throw mensaje;
}

int Socket::recvSome(void* data, unsigned int sz, bool* wasClosed){
    *wasClosed = false;
    int s = recv(this->skt, (char *) data, sz, 0);

    if ( s == 0) {
        // Puede ser o no ser un error dependera del protocolo, ej protocolo donde se reciben datos hasta q la conexion se cierra.
        *wasClosed = true;
        return 0;
    } else if (s == -1 ){
        //99.9% que es un error
        std::cerr << "Error en el recvSome " + std::to_string(errno);
        throw "Error en el recvSome " + std::to_string(errno);
    } else {
        // si mando mas de 0 entonces mando unos bytes retornamos esa cantidad;
        return s;
    }

}

int Socket::sendSome(void* data, unsigned int sz, bool* wasClosed){
    *wasClosed = false;

    //BrokenPipe: imagina que estamos enviando bytes por el socket y luego se cierra derrepente la extrada externa.
    // quedando data sin enviar esto es Broken Pipe. En linux se envia la señal  SIGPIPE. que si no es manejada mata al proceso
    // por suerte tenemos el flag MSG_NOSIGNAL

    int s = send(skt, (char*) data, sz, MSG_NOSIGNAL );
    if ( s == 0 ){
        //Jamas deberia pasar  almenos 1 byte debe enviar o devuelve -1 si es error..
        assert(false);
    }
    else if (s == -1 ){

        //Error cuando enviamos algo y en el medio se cierra el socket  no se sabe
        // cuanto se logro enviar y cuanto se perdio. esto es el brokenPipe
        if( errno == EPIPE){
            // puede o no ser un error.
            *wasClosed = true;
            return 0;
        }
        *wasClosed = true;
        std::cerr << "Error en el sendSome,  :" + std::to_string(errno);
        throw "Error en el sendSome,  :" + std::to_string(errno);
    } else {
        return s;
    }
}

int Socket::sendAll(const void* data, unsigned int sz, bool* wasClosed){
    *wasClosed = false;
    int bytesEnviados = 0;
    int s = 0;
    while( bytesEnviados < sz){
        s = sendSome((char*) data + bytesEnviados, sz - bytesEnviados, wasClosed);
        if (s == 0 && *wasClosed){ //agrege yo
            return sz;
        }
        if( s <= 0 ){
            //Esto nunca deberia pasar.
            assert(s == 0);
            if ( bytesEnviados){
                std::cerr << "Enviaste bytes pero ahora ocurrio un error en sendaAll:"+ std::to_string(errno);
                throw "Enviaste bytes pero ahora ocurrio un error en sendaAll:"+ std::to_string(errno);
            } else
                  return 0;
        }else{
            bytesEnviados +=s;
        }
    }
    return sz;
}

int Socket::recvAll(void* data, unsigned int sz, bool* wasClosed){
    *wasClosed = false;
    int bytesRecividos = 0;
    int s = 0;
    while( bytesRecividos < sz){
        s = recvSome((char*)data + bytesRecividos, sz - bytesRecividos, wasClosed);
        if (s == 0 && *wasClosed){ //agrege yo
            return sz;
        }
        if ( s<= 0 ){
            assert(s == 0);
            if (bytesRecividos){
                std::cerr << "Recibiste algunos bytes pero ahora ocurrio un error en recvAll: "+ std::to_string(errno);
                throw "Recibiste algunos bytes pero ahora ocurrio un error en recvAll: "+ std::to_string(errno);
            }
            else
                return 0;
        }
        else{
            bytesRecividos +=s;
        }
    }
    return sz;

}


Socket::Socket(int unSkt){
    this->skt = unSkt;
    this->closed = false;
}

Socket Socket::accept() {

    //El metodo accept lo usamos para el socket de tipo servidor. Nos bloqueara hasta que algun cliente se conecte.
    // Una vez que un cliente se conecte nos devolvera el socket peer que representara la conexion con ese cliente.
    int socketPeer = ::accept(this->skt, nullptr, nullptr );
    if(socketPeer == -1 ){
        std::cerr << "Error en el Accept el socketPeer fallo al aceptar peer Devolvio" + std::to_string(socketPeer)  + std::to_string(errno);
        throw "Error en el Accept el socketPeer fallo al aceptar peer Devolvio" + std::to_string(socketPeer)  + std::to_string(errno);
    }

    return Socket(socketPeer);
}

//Le sacamos el ownership del otroSocekt y lo movemos para nosotros.
Socket::Socket(Socket&& other){
    this->skt = other.skt;
    this->closed = other.closed;


    other.skt = -1;
    other.closed = true;
}

Socket& Socket::operator=(Socket&& other){

   //si nos movemos a nosotros mismo no hacemos nada.
    if (this == &other){
       return *this;
   }
    //Somos un sokcet completamente creado debemos desinicializar completo antes de tomar el onwership de otro.
    if (not this->closed){
        ::shutdown(this->skt, SHUT_RDWR);
        ::close(this->skt);
    }

    //ahora mismos pasos que el constructor por movimiento.

    this->skt = other.skt;
    this->closed = other.closed;

    other.skt = -1;
    other.closed = true;

    return *this;

}



