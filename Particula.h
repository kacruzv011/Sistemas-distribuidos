#ifndef PARTICULA_H
#define PARTICULA_H

#include "utils.h"

class Particula {
public:
    Vector2D posicion, velocidad;
    double masa, carga;

    Particula(Vector2D posicion, Vector2D velocidad, double masa, double carga);

    void actualizar(const Vector2D& campo, double dt);

    friend std::ostream& operator<<(std::ostream& os, const Particula& p);
};

#endif
