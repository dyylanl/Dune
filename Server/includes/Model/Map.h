#ifndef __MAP_H__
#define __MAP_H__


#include <iostream>
#include <vector>

#include "Unit/Unit.h"
#include "../../../Common/includes/Exceptions/Exception.h"

class Map {

private:
    int rows, columns;
    std::vector<std::vector<std::string>> world;
     // METODOS PRIVADOS
    std::string getPos(int x, int y) const;
public:
    /*
     * Crea una matriz de x filas por y columnas.
     */
    Map(int x, int y);
    /*
     * Imprime el mapa por stdin.
     */
    void showMap();

    ~Map();

    /*
     * Establece el valor value en la posicion x e y del mapa.
     */
    void setValue(int x, int y, char value);


    bool canMove(Unit& unit, Position pos);

    /*
     * Retorna true si es una posicion valida del mapa.
     */
    bool isValid(Position& pos) const;

    /*
     *
     */
};


#endif
