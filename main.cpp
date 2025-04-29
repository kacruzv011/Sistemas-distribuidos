#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Particula.h"

void simular(const std::string& nombreCSV, const Vector2D& campo, const Particula& inicial, int pasos, double dt) {
    std::ofstream archivo(nombreCSV);
    archivo << "Paso,Posicion_X,Posicion_Y,Velocidad_X,Velocidad_Y\n";

    Particula p = inicial;
    for (int i = 0; i < pasos; ++i) {
        archivo << i << "," << p.posicion.x << "," << p.posicion.y << ","
                << p.velocidad.x << "," << p.velocidad.y << "\n";
        p.actualizar(campo, dt);
    }
    archivo.close();
    std::cout << "Datos guardados en " << nombreCSV << "\n";
}

int main() {
    double dt = 0.01;
    int pasos = 1000;

    // Simulación 1 - Electrón
    Vector2D campo1(6.0, -1.0);
    double masa_electron = 9.11e-31;           // kg
    double carga_electron = -1.6e-19;          // C
    Particula particula1(Vector2D(0, 0), Vector2D(0, 0), masa_electron, carga_electron);
    simular("simulacion_1.csv", campo1, particula1, pasos, dt);

    // Simulación 2 - Ion Ca2+
    Vector2D campo2(27.0, 2.0);
    double masa_calcio = 6.64e-26;             // kg (aprox. 40 u)
    double carga_calcio = 3.2e-19;             // C (2 * carga elemental)
    Particula particula2(Vector2D(3, 9), Vector2D(9, 3), masa_calcio, carga_calcio);
    simular("simulacion_2.csv", campo2, particula2, pasos, dt);

    // Script de Gnuplot
    std::ofstream gp("graficas_combinadas.gp");
    if (!gp.is_open()) {
        std::cerr << "No se pudo crear el script de Gnuplot.\n";
        return 1;
    }

    gp << "set datafile separator ','\n";
    gp << "set grid\n";
    gp << "set terminal pngcairo size 1000,800 enhanced font 'Verdana,10'\n";

    // Gráfica 1: Simulación 1
    gp << "set output 'grafica_1.png'\n";
    gp << "set title 'Simulación 1 (Electrón): Posición y Velocidad'\n";
    gp << "set xlabel 'Paso'\n";
    gp << "set ylabel 'Magnitud'\n";
    gp << "plot 'simulacion_1.csv' using 1:2 with lines title 'Posición X', \\\n";
    gp << "     'simulacion_1.csv' using 1:3 with lines title 'Posición Y', \\\n";
    gp << "     'simulacion_1.csv' using 1:4 with lines title 'Velocidad X', \\\n";
    gp << "     'simulacion_1.csv' using 1:5 with lines title 'Velocidad Y'\n";

    // Gráfica 2: Simulación 2
    gp << "set output 'grafica_2.png'\n";
    gp << "set title 'Simulación 2 (Ion Ca²⁺): Posición y Velocidad'\n";
    gp << "plot 'simulacion_2.csv' using 1:2 with lines title 'Posición X', \\\n";
    gp << "     'simulacion_2.csv' using 1:3 with lines title 'Posición Y', \\\n";
    gp << "     'simulacion_2.csv' using 1:4 with lines title 'Velocidad X', \\\n";
    gp << "     'simulacion_2.csv' using 1:5 with lines title 'Velocidad Y'\n";

        // Gráfica 3: Tiempo vs Pasos (Debug y Release)
    gp << "set output 'grafica_tiempos.png'\n";
    gp << "set title 'Tiempo de ejecución vs Pasos'\n";
    gp << "set xlabel 'Número de pasos'\n";
    gp << "set ylabel 'Tiempo (s)'\n";
    gp << "plot 'tiempos.csv' using 1:2 with linespoints title 'Debug', \\\n";
    gp << "     'tiempos.csv' using 1:3 with linespoints title 'Release'\n";

    gp << "set output\n";
    gp.close();

    gp << "set output\n";
    gp.close();

    system("gnuplot graficas_combinadas.gp");

    return 0;
}
