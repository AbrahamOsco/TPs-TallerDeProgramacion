//
// Created by abraham on 27/09/23.
//

#include "common_protocol.h"

#include <stdexcept>
#include <utility>
#include <vector>

#include <netdb.h>


Protocol::Protocol(Socket& unSocket): socket(unSocket), wasClosed(false) {}

bool Protocol::isAvailable() const { return !wasClosed; }


void Protocol::sendString(const std::string& aString) {
    size_t s = 0;
    sendNum2Bytes(aString.size());
    s += socket.sendall(aString.data(), aString.size(), &wasClosed);
    if (s != aString.size()) {
        throw std::runtime_error("Error al enviar la cadena: " + aString + "\n");
    }
}

std::string Protocol::recvString() {
    size_t s = 0;
    size_t tamanioBuffer = recvNum2Bytes();
    std::vector<char> buffer(tamanioBuffer);
    s += socket.recvall(buffer.data(), tamanioBuffer, &wasClosed);
    if (s != tamanioBuffer) {
        throw std::runtime_error("Error al recibir la cadena\n");
    }
    return std::string(buffer.begin(), buffer.end());
}


void Protocol::sendANumberByte(const unsigned int& aNumber) {
    uint8_t operacion = aNumber;
    size_t s = 0;
    s += socket.sendall(&operacion, sizeof(operacion), &wasClosed);
    if (s != sizeof(operacion)) {
        throw std::runtime_error("Error al enviar la operacion Numerica\n");
    }
}

int Protocol::recvANumberByte() {
    uint8_t operacion;
    size_t s = 0;
    s += socket.recvall(&operacion, sizeof(operacion), &wasClosed);
    if (s != sizeof(operacion)) {
        return CIERRA_CONEXION;
    }
    return (int)operacion;
}

void Protocol::sendNum2Bytes(const unsigned int& aNumber) {
    uint16_t sendNumber = aNumber;
    sendNumber = htons(sendNumber);
    size_t s = 0;
    s += socket.sendall(&sendNumber, sizeof(sendNumber), &wasClosed);
    if (s != sizeof(sendNumber)) {
        throw std::runtime_error("Error al enviar la operacion Numerica\n");
    }
}

int Protocol::recvNum2Bytes() {
    uint16_t unNumero;
    size_t s = 0;
    s += socket.recvall(&unNumero, sizeof(unNumero), &wasClosed);
    if (s != sizeof(unNumero)) {
        throw std::runtime_error("Error al recibir 2 Bytes\n");
    }
    unNumero = ntohs(unNumero);
    return (int)unNumero;
}
