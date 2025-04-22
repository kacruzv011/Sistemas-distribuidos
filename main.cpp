#include <iostream>
#include "Particula.h"

void simular(const std::string& nombreSimulacion, const Vector2D& campo, const Particula& particulaInicial, int pasos, double dt) {
    std::cout << "\n--- Simulación: " << nombreSimulacion << " ---\n";
    Particula p = particulaInicial;

    for (int i = 0; i < pasos; ++i) {
        p.actualizar(campo, dt);
        std::cout << "Paso " << i << ": " << p << "\n";
    }
}

int main() {
    double dt = 0.01;
    int pasos = 100;

    // Simulación 1
    Vector2D campo1(6.0, -1.0);
    Particula particula1(Vector2D(0, 0), Vector2D(0, 0), 5.0, 21.0);
    simular("Partícula 1 - Campo (5, -3)", campo1, particula1, pasos, dt);

    // Simulación 2
    Vector2D campo2(27.0, 2.0);
    Particula particula2(Vector2D(3, 9), Vector2D(9, 3), 2.0, -1.0);
    simular("Partícula 2 - Campo (-2, 4)", campo2, particula2, pasos, dt);

    return 0;
}
