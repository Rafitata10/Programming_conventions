// Rafael Ramírez Salas - Ingeniería de Computadores - Universidad de Málaga
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int tablero[255][255], distancia[255][255];

void matrizIni(const vector<vector<int>>& tableroIni, queue<int>& q, int m, int n){
    // Inicializa las matrices.
    for(int i = 0; i < 255; i++){
        for(int j = 0; j < 255; j++){
            tablero[i][j] = -2;
            distancia[i][j] = -1;
        }
    }

    // Copia los valores del tablero inicial al extendido.
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            tablero[i + 2][j + 2] = tableroIni[i][j];
            if(tableroIni[i][j] == -1){
                q.push(i + 2);
                q.push(j + 2);
                distancia[i + 2][j + 2] = 0;
            }
        }
    }
}

// Algoritmo buscador para encontrar las distancias mínimas.
void minDist(queue<int>& cola){
    while(!cola.empty()){
        int xr = cola.front();
        cola.pop();
        int xc = cola.front();
        cola.pop();

        if(tablero[xr+2][xc] >= 0 && tablero[xr+2][xc] == tablero[xr+1][xc] && distancia[xr+2][xc] == -1){
            cola.push(xr+2);
            cola.push(xc);
            distancia[xr+2][xc] = distancia[xr][xc] + 1;
        }

        if(tablero[xr-2][xc] >= 0 && tablero[xr-2][xc] == tablero[xr-1][xc] && distancia[xr-2][xc] == -1){
            cola.push(xr-2);
            cola.push(xc);
            distancia[xr-2][xc] = distancia[xr][xc] + 1;
        }

        if(tablero[xr][xc+2] >= 0 && tablero[xr][xc+2] == tablero[xr][xc+1] && distancia[xr][xc+2] == -1){
            cola.push(xr);
            cola.push(xc+2);
            distancia[xr][xc+2] = distancia[xr][xc] + 1;
        }

        if(tablero[xr][xc-2] >= 0 && tablero[xr][xc-2] == tablero[xr][xc-1] && distancia[xr][xc-2] == -1){
            cola.push(xr);
            cola.push(xc-2);
            distancia[xr][xc-2] = distancia[xr][xc] + 1;
        }
    }
}

// Reconstruye la secuencia de coches desplazados y devuelve el camino.
vector<int> caminoRec(int r, int c){
    stack<int> pila;
    vector<int> res;

    while(distancia[r][c] > 0){
        pila.push(tablero[r][c]);
        if(distancia[r + 2][c] == distancia[r][c] - 1 && tablero[r][c] == tablero[r + 1][c]){
            r += 2;
        } else if(distancia[r - 2][c] == distancia[r][c] - 1 && tablero[r][c] == tablero[r - 1][c]){
            r -= 2;
        } else if(distancia[r][c + 2] == distancia[r][c] - 1 && tablero[r][c] == tablero[r][c + 1]){
            c += 2;
        } else {
            c -= 2;
        }
    }

    while(!pila.empty()){
        res.push_back(pila.top());
        pila.pop();
    }

    return res;
}

// secuencia de movimientos necesaria para destapar el coche.
vector<int> secMovs(const vector<vector<int>>& tableroIni, int m, int n, int r, int c){
    queue<int> cola;

    // Inicializa las matrices y copia los valores del tablero inicial al extendido.
    matrizIni(tableroIni, cola, m, n);

    // Algoritmo buscador para encontrar las distancias mínimas.
    minDist(cola);

    r++; c++; // Ajuste de las coordenadas del hueco.

    // Comprueba si es posible o no destapar el coche deseado.
    if(distancia[r][c] == -1){
        return {-1}; // Imposible destapar el coche.
    }

    return caminoRec(r, c);
}

int main(void){
    int m, n;
    cin >> m >> n; // Dimensiones de la matriz.

    vector<vector<int>> tablero(m, vector<int>(n));

    // Leer la matriz de coches.
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cin >> tablero[i][j];
        }
    }
    
    int r, c;
    cin >> r >> c; // Coordenadas del hueco a destapar.

    // Secuencia de movimientos necesaria para destapar el coche.
    vector<int> result = secMovs(tablero, m, n, r, c);

    // Comprobación de si es posible o no destapar el coche deseado.
    if(result.size() == 1 && result[0] == -1){
        cout << "impossible" << endl; // No es posible destapar el coche.
    } else {
        for(int car : result){
            cout << car << " "; // Muestra la secuencia de coches desplazados.
        }
        cout << endl;
    }

    // Se devuelve 0 si todo se ejecuta correctamente.
    return 0;
}
