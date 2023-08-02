//
// Created by abraham on 10/07/23.
//

#ifndef SOCKETS_SOCKET_H
#define SOCKETS_SOCKET_H


class Socket {
private:
    Socket(int fd);

    bool closed;
    int skt;

public:
    Socket(const char* hostName, const char* serviceName);
    Socket(const char* serviceName);

    int recvSome(void *data, unsigned int sz, bool *wasClosed);

    int sendSome(void *data, unsigned int sz, bool *wasClosed);

    int sendAll(const void *data, unsigned int sz, bool *wasClosed);

    int recvAll(void *data, unsigned int sz, bool *wasClosed);

    Socket accept();

    // Ahora hacemos el sktAceptador movible:
    Socket(Socket &&); //constructor por movimiento
    Socket& operator=(Socket&& other); //copia por movimiento

    //Eliminamos la construccion de sktAceptador por copia y la asignacion por copia de un sktAceptador.
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    void shutdown(int how);

    int close();

    void chk_skt_or_fail() const;

    ~Socket();

    void closeSkt();
};


#endif //SOCKETS_SOCKET_H
