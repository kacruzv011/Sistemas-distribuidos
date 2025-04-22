#include <iostream>
#include <chrono>
#include <fstream>
#include "Particula.h"

void simular(const std::string& nombreArchivo, const Vector2D& campo, const Particula& inicial, int pasos, double dt) {
    std::ofstream archivo(nombreArchivo);
    archivo << "Paso,Posicion_X,Posicion_Y,Velocidad_X,Velocidad_Y\n";

    Particula p = inicial;
    for (int i = 0; i < pasos; ++i) {
        archivo << i << "," << p.posicion.x << "," << p.posicion.y << ","
                << p.velocidad.x << "," << p.velocidad.y << "\n";
        p.actualizar(campo, dt);
    }

    archivo.close();
    std::cout << "Simulación guardada en " << nombreArchivo << "\n";
}

int main() {
    double dt = 0.01;
    int pasos = 1000;

    // Simulación 1
    Vector2D campo1(6.0, -1.0);
    Particula particula1(Vector2D(0, 0), Vector2D(0, 0), 5.0, 21.0);
    simular("simulacion_1.csv", campo1, particula1, pasos, dt);

    // Simulación 2
    Vector2D campo2(27.0, 2.0);
    Particula particula2(Vector2D(3, 9), Vector2D(9, 3), 2.0, -1.0);
    simular("simulacion_2.csv", campo2, particula2, pasos, dt);

    return 0;
}


