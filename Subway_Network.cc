// Rafael Ramírez Salas - Ingeniería de Computadores - Universidad de Málaga
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Estructura para almacenar las coordenadas de un punto.
struct Coord {
    int x, y;
};

// Calcula la distancia perpendicular del punto (x, y) a la línea con el ángulo (angle).
double calcDistancia(int x, int y, double angle){
    return fabs(x * sin(angle) - y * cos(angle));
}

// Calcula el número mínimo de líneas de metro necesarias para resolver el problema.
int contarLineas(int n, double d, const vector<Coord>& points){
    vector<bool> revisado(n, false);  // Vector para marcar los puntos revisados.
    int lineasNec = 0;  // Variable líneas necesarias.
    
    // Bucle hasta que todos los puntos estén cubiertos
    while(true){
        int mejorInd = -1;  // Índice del mejor punto para comenzar una línea.
        int maxCubierto = 0;  // Mayor número de puntos cubiertos en una iteración.
         vector<int> currentCub;  // Vector de puntos cubiertos en esta iteración.
        
        // Itera sobre todos los puntos.
        for(int i = 0; i < n; ++i){
            if(revisado[i]){
                continue;  // Obvia los puntos ya cubiertos.
            }
            
            double angulo = atan2(points[i].y, points[i].x);  // Calcula el ángulo de la línea.
            int pCubiertos = 0;  // Puntos cubiertos en esta iteración.
            vector<int> tempCub;  // Vector temporal para puntos cubiertos en esta iteración.
            
            // Comprobar cada punto con la línea definida por el ángulo actual
            for(int j = 0; j < n; ++j){
                if(revisado[j]){
                    continue;  // Obvia los puntos ya cubiertos.
                }
                
                // Calcular la distancia perpendicular del punto a la línea.
                double distancia = calcDistancia(points[j].x, points[j].y, angulo);
                
                // Comprobar si el punto está cubierto.
                if(distancia <= d + 1e-9){ // Se añade un pequeño margen para evitar errores de redondeo.
                    pCubiertos++;
                    tempCub.push_back(j);
                }
            }
            
            // Actualizar el mejor punto si se cubren más puntos en esta iteración.
            if(pCubiertos > maxCubierto){
                maxCubierto = pCubiertos;
                mejorInd = i;
                currentCub = tempCub;  // Actualizar los puntos cubiertos en esta iteración.
            }
        }
        
        // Si no se encuentra un mejor punto, salir del bucle.
        if(maxCubierto == 0){
            break;
        }
        
        // Marca los puntos cubiertos como revisados.
        for(int ind : currentCub){
            revisado[ind] = true;
        }

        // Incrementar el contador de líneas necesarias.
        lineasNec++;
    }
    
    return lineasNec;
}

int main(void){
    int conjuntos;
    cin >> conjuntos;  // Número de conjuntos de datos.
    
    // Procesamiento de cada conjunto de datos.
    for(int i = 0; i < conjuntos; i++){
        int n;
        double d;
        cin >> n >> d;  //Número de puntos y distancia máxima permitida.
        
        vector<Coord> puntos(n); // Vector para almacenar las coordenadas de los puntos del conjunto.
        for(int j = 0; j < n; ++j){
            cin >> puntos[j].x >> puntos[j].y;  // Coordenadas de cada punto del conjunto.
        }
        
        int result = contarLineas(n, d, puntos);  // Calcular el número mínimo de líneas necesarias para estas coordenadas.
        cout << result << endl;  // Mostrar el resultado para este conjunto.
    }

    // Se devuelve 0 si todo se ejecuta correctamente.
    return 0;
}
