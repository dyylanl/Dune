
#ifndef LIB_ERROR_H
#define LIB_ERROR_H

#include <exception>

/*
 * Clase para encapsular el errno de C, "el ultimo error".
 * Es una excepcion generica que se encarga de los detalles
 * de decodificar el errno en un mensaje mas entendible.
 * */
class LibError : public std::exception {
    char msg_error[256];

public:
    // Make this public but constant.
    const int error_code;

    /*
     * Dado que errno es una variable global y puede ser modificada por
     * cualquier funcion, hay que hacer una copia apenas se haya detectado
     * el error, para luego lanzar LibError o bien lanzar LibError apenas
     * ya se haya detectado el error.
     *
     * El constructor LibError es variadico y recibe, ademas del errno,
     * un format-string (como printf()) y cero o mas argumentos que
     * formaran parte del mensaje.
     *
     * int ret = foo();
     * if (ret == -1)
     *      throw LibError(errno, "La funcion %s ha fallado: ", "foo");
     *  */
    LibError(int error_code, const char* fmt, ...) noexcept;

    virtual const char* what() const noexcept;

    // Por que estamos heredando y usando polimorfismo
    // es importantisimo definir un destructor virtual
    // Estrictamente hablando basta con poner virtual al
    // destructor de la clase padre (std::exception) pero
    // GCC requiere de la definicion de los destructores
    // de las clases hijas para que pueda colocar la VTable.
    virtual ~LibError();
};

#endif