#include <iostream>
#include <fstream>
#include <cstdlib>  // Para system()
#include "Particula.h"

void simular(const std::string& nombreCSV, const std::string& tituloGrafica, const Vector2D& campo, const Particula& inicial, int pasos, double dt) {
    std::ofstream archivo(nombreCSV);
    archivo << "Paso,Posicion_X,Posicion_Y\n";

    Particula p = inicial;
    for (int i = 0; i < pasos; ++i) {
        archivo << i << "," << p.posicion.x << "," << p.posicion.y << "\n";
        p.actualizar(campo, dt);
    }
    archivo.close();
    std::cout << "Datos guardados en " << nombreCSV << "\n";

    // Crear script de Gnuplot
    std::string nombreGP = nombreCSV.substr(0, nombreCSV.find('.')) + ".gp";
    std::ofstream gp(nombreGP);
    
    // Verificar si el archivo se abrió correctamente
    if (!gp.is_open()) {
        std::cerr << "Error al crear el archivo de Gnuplot: " << nombreGP << std::endl;
        return;
    }
    
    gp << "set title \"" << tituloGrafica << "\"\n";
    gp << "set xlabel \"Paso\"\n";
    gp << "set ylabel \"Posición\"\n";
    gp << "set grid\n";
    
    // Configuración del separador de columnas (si es CSV con comas)
    gp << "set datafile separator \",\"\n";
    
    // Graficar ambos archivos: simulacion_1.csv y simulacion_2.csv
    gp << "plot \"" << nombreCSV << "\" using 1:2 skip 1 with lines title 'Posición X 1', \\\n";
    gp << "     \"" << nombreCSV << "\" using 1:3 skip 1 with lines title 'Posición Y 1', \\\n";
    gp << "     \"simulacion_2.csv\" using 1:2 skip 1 with lines title 'Posición X 2', \\\n";
    gp << "     \"simulacion_2.csv\" using 1:3 skip 1 with lines title 'Posición Y 2'\n";
    
    gp << "pause -1\n";  // Espera a que el usuario cierre
    gp.close();
    
    // Ejecutar gnuplot
    std::string comando = "gnuplot " + nombreGP;
    system(comando.c_str());
    
}

int main() {
    double dt = 0.01;
    int pasos = 1000;

    // Simulación 1
    Vector2D campo1(6.0, -1.0);
    Particula particula1(Vector2D(0, 0), Vector2D(0, 0), 5.0, 21.0);
    simular("simulacion_1.csv", "Simulación 1: Campo (6, -1), Carga 21", campo1, particula1, pasos, dt);

    // Simulación 2
    Vector2D campo2(27.0, 2.0);
    Particula particula2(Vector2D(3, 9), Vector2D(9, 3), 2.0, -1.0);
    simular("simulacion_2.csv", "Simulación 2: Campo (27, 2), Carga -1", campo2, particula2, pasos, dt);

    return 0;
}


