#include "Particula.h"

Particula::Particula(Vector2D posicion, Vector2D velocidad, double masa, double carga)
    : posicion(posicion), velocidad(velocidad), masa(masa), carga(carga) {}

void Particula::actualizar(const Vector2D& campo, double dt) {
    Vector2D fuerza = campo * carga;
    Vector2D aceleracion = fuerza / masa;
    velocidad = velocidad + aceleracion * dt;
    posicion = posicion + velocidad * dt;
}

std::ostream& operator<<(std::ostream& os, const Particula& p) {
    os << "Posición: " << p.posicion << ", Velocidad: " << p.velocidad
       << ", Masa: " << p.masa << ", Carga: " << p.carga;
    return os;
}
