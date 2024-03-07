//
// Created by abraham on 10/07/23.
//

#ifndef SOCKETS_RESOLVER_H
#define SOCKETS_RESOLVER_H


class Resolver {
private:
    struct addrinfo* results;
    struct addrinfo* next;
    bool  pasivo;

public:

    Resolver(const char *hostName, const char *serviceName, bool tipoPasivo);


    bool hasNext();

    struct addrinfo* getNext();

    ~Resolver();

};


#endif //SOCKETS_RESOLVER_H
