#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
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

    // ======= Parte 1: Medición de tiempos =======
    std::ofstream tiempos("tiempos.csv");
    if (!tiempos.is_open()) {
        std::cerr << "No se pudo crear tiempos.csv\n";
        return 1;
    }
    tiempos << "Pasos,Debug,Release\n"; // puedes usar la misma columna para ambas si mides solo una vez

    Vector2D campo_tiempo(6.0, -1.0);
    double masa = 9.11e-31;
    double carga = -1.6e-19;
    Particula particula_tiempo(Vector2D(0, 0), Vector2D(0, 0), masa, carga);

    for (int pasos = 100; pasos <= 2000; pasos += 100) {
        auto inicio = std::chrono::high_resolution_clock::now();
        simular("simulacion_temp.csv", campo_tiempo, particula_tiempo, pasos, dt);
        auto fin = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duracion = fin - inicio;
        tiempos << pasos << "," << duracion.count() << ",\n";
        std::cout << "Pasos: " << pasos << ", Tiempo: " << duracion.count() << " s\n";
    }
    tiempos.close();

    // ======= Parte 2: Simulaciones fijas =======
    int pasos = 1000;

    // Simulación 1
    Vector2D campo1(6.0, -1.0);
    Particula particula1(Vector2D(0, 0), Vector2D(0, 0), 1.6e-27, 1.6e-19);
    simular("simulacion_1.csv", campo1, particula1, pasos, dt);

    // Simulación 2
    Vector2D campo2(27.0, 2.0);
    Particula particula2(Vector2D(3, 9), Vector2D(9, 3), 9.11e-31, -1.6e-19);
    simular("simulacion_2.csv", campo2, particula2, pasos, dt);

    // ======= Parte 3: Script de Gnuplot =======
    std::ofstream gp("graficas_combinadas.gp");
    if (!gp.is_open()) {
        std::cerr << "No se pudo crear el script de Gnuplot.\n";
        return 1;
    }

    gp << "set datafile separator ','\n";
    gp << "set grid\n";
    gp << "set terminal pngcairo size 1000,800 enhanced font 'Verdana,10'\n";

    // Gráfica 1
    gp << "set output 'grafica_1.png'\n";
    gp << "set title 'Simulación 1: Posición y Velocidad'\n";
    gp << "set xlabel 'Paso'\n";
    gp << "set ylabel 'Magnitud'\n";
    gp << "plot 'simulacion_1.csv' using 1:2 with lines title 'Posición X', \\\n";
    gp << "     'simulacion_1.csv' using 1:3 with lines title 'Posición Y', \\\n";
    gp << "     'simulacion_1.csv' using 1:4 with lines title 'Velocidad X', \\\n";
    gp << "     'simulacion_1.csv' using 1:5 with lines title 'Velocidad Y'\n";

    // Gráfica 2
    gp << "set output 'grafica_2.png'\n";
    gp << "set title 'Simulación 2: Posición y Velocidad'\n";
    gp << "set xlabel 'Paso'\n";
    gp << "set ylabel 'Magnitud'\n";
    gp << "plot 'simulacion_2.csv' using 1:2 with lines title 'Posición X', \\\n";
    gp << "     'simulacion_2.csv' using 1:3 with lines title 'Posición Y', \\\n";
    gp << "     'simulacion_2.csv' using 1:4 with lines title 'Velocidad X', \\\n";
    gp << "     'simulacion_2.csv' using 1:5 with lines title 'Velocidad Y'\n";

    // Gráfica 3
    gp << "set output 'grafica_tiempos.png'\n";
    gp << "set title 'Tiempo de ejecución vs Pasos'\n";
    gp << "set xlabel 'Número de pasos'\n";
    gp << "set ylabel 'Tiempo (s)'\n";
    gp << "plot 'tiempos.csv' using 1:2 with linespoints title 'Tiempo real (máquina)'\n";

    gp << "set output\n";
    gp.close();

    system("gnuplot graficas_combinadas.gp");

    return 0;
}

