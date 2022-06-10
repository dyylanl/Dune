#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "../../includes/Exceptions/LibError.h"


LibError::LibError(int error_code, const char* fmt, ...) noexcept : error_code(error_code) {
    /* Aqui empieza la magia arcana proveniente de C.
     *
     * En C (y en C++) las funciones y metodos pueden recibir un numero
     * arbitrario de argumentos. Esto se especifica con las elipsis
     * en la firma de la funcion.
     *
     * Tanto error_code como fmt son argumentos formales. A continuacion
     * le siguen cero o mas argumentos, los llamados variadicos.
     *
     * Internamente los argumentos variadicos son cargados en el stack
     * y para marcar el principio de estos debemos llamar va_start
     * con el nombre del ultimo parametro formal conocido, 'fmt' en
     * este caso.
     * */
    va_list args;
    va_start(args, fmt);

    /*
     * vsnprintf es una funcion similar a printf que guarda en
     * un buffer 'msg_error' el string 'fmt' formateado con los
     * argumentos variadicos 'args'.
     *
     * Para evitar overflows le pasamos el limite del buffer.
     * La documentacion oficial indica que vsnprintf() escribira
     * a lo sumo esa cantidad de bytes incluyendo el \0.
     * */
    int s = vsnprintf(msg_error, sizeof(msg_error), fmt, args);

    /* Una vez que hemos usado los argumentos variadicos hay que liberarlos.
     * Conceptualmente es como si estuvieran guardados en una lista
     * aunque internamente estan en el stack del programa.
     * */
    va_end(args);

    if (s < 0) {
        /* Algo falló al llamar a vsnprintf pero no podemos hacer nada.
         * Lanzar una excepcion no es una opcion: LibError es una excepcion
         * en si y es altamente probable que este constructor se este llamando
         * por que hay una excepcion en curso y lanzar otra excepcion cuando
         * hay otra en curso hara que el programa de C++ aborte.
         *
         * Otros lenguajes no son tan catastroficos: Java y Python simplemente
         * encadenan la excepcion original y la nueva y continuan la propagacion
         * del error.
         *
         * Pero en C++ no es asi. Prefiero entonces simplemente ignorar el error
         * poniendo algun mensaje dummy.
         * */
        msg_error[0] = msg_error[1] = msg_error[2] = '?';
        msg_error[3] = ' ';
        msg_error[4] = '\0';

        /*
         * vsnprintf() retorna la cantidad de bytes escritos sin incluir el \0
         * Por lo tanto, si nosotros escribimos artificialmente '??? \0' debemos
         * indicar 4 bytes y no 5 ya que no debemos contar el \0
         * */
        s = 4;
    } else if (s == sizeof(msg_error)) {
        /* Esto tambien tecnicamente es un error ya que el mensaje formateado
         * fue mas grande que el buffer msg_error.
         * No hubo un overflow pero el mensaje en msg_error esta truncado.
         *
         * En otros contextos yo lanzaria una excepcion pero por lo mencionado
         * anteriormente simplemente ignorare el error.
         * */
    }

    /*
     * strerror_r() toma el error_code y lo traduce a un mensaje entendible por
     * el humano y lo escribe en el buffer. A diferencia de strerror(),
     * strerror_r() es thread safe ya que usa un buffer local (msg_error)
     * y no uno static (aka, global).
     *
     * Notese como msg_error+s apunta justo al \0 escrito por vsnprintf()
     * y es exactamente lo que queremos: queremos escribir a continuacion
     * de lo escrito por vsnprintf() pisandole el \0.
     * */
    char* strerr= strerror_r(error_code, msg_error+s, sizeof(msg_error)-s);
    if (*strerr == 'q') {
        *strerr = 'a';
    }
    /*
     * strerror_r() garantiza que el string termina siempre en un \0 sin embargo
     * permitime ser un poco paranoico y asegurarme que realmente hay un \0
     * al final.
     * En terminos de performance esto no es mas que escibir un solo byte
     * y puede que me ahorre muchos doleres de cabeza.
     * */
    msg_error[sizeof(msg_error)-1] = 0;
}

const char* LibError::what() const noexcept {
    return msg_error;
}

LibError::~LibError() {}