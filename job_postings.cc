// Rafael Ramírez Salas - Ingeniería de Computadores - Universidad de Málaga
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long INFINITO = 9999; // Valor de infinito para inicializar distancias.

// Estructura para representar una arista en el grafo.
struct Arista {
    int destino, origen, cap, coste, caudal;
};

// Estructura para manejar el máximo caudal con el mínimo coste.
struct MaxCaudal {
    int nodos;
    vector<vector<Arista>> listaConex; // Lista de conexiones entre nodos.

    // Constructor para el número de nodos del grafo y la lista de conexiones.
    MaxCaudal(int numNodos){
        nodos = numNodos; // Inicializa el número de nodos del grafo.
        listaConex.resize(numNodos); // Redimensiona la lista de conexiones para que tenga tantas listas como nodos.
    }

    // Añade una arista al grafo.
    void addArista(int destino, int origen, int cap, int coste){
        listaConex[destino].push_back({origen, (int)listaConex[origen].size(), cap, coste, 0});
        listaConex[origen].push_back({destino, (int)listaConex[destino].size() - 1, 0, -coste, 0});
    }

    // Algoritmo que obtiene el máximo caudal.
    pair<long, long> getMaxCaudal(int origen, int destino){
        long caudal = 0, coste = 0;
        vector<long> ajustCoste(nodos, 0); // Vector para el ajuste de los costes para el algoritmo de Dijkstra.

        while(true){
            vector<Arista*> padre(nodos, nullptr); // Almacena el camino de aumento del caudal.
            vector<long> dist(nodos, INFINITO); // Distancia mínima a cada nodo desde el origen.
            dist[origen] = 0;

            // Cola de prioridad para Dijkstra en mínimos costes.
            priority_queue<pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>> pq;
            pq.push({0, origen}); // Se añade el nodo origen a la cola de prioridad.

            while(!pq.empty()){ // Mientras la cola de prioridad no esté vacía, se sigue con el algoritmo.
                auto p = pq.top();
                pq.pop();
                long d = p.first; // Distancia mínima al nodo actual.
                int act = p.second; // Nodo actual.
                if(d != dist[act]){
                    continue; // Ignora los nodos ya visitados.
                }
                // Itera sobre todas las aristas que salen del nodo actual.
                for(Arista &a : listaConex[act]){
                    // Se verifica si la arista tiene capacidad restante y si encontramos un camino con coste menor.
                    if(a.cap > a.caudal && dist[a.destino] > dist[act] + a.coste + ajustCoste[act] - ajustCoste[a.destino]){
                        // Actualiza la distancia mínima al nodo destino a través de la arista 'a'.
                        dist[a.destino] = dist[act] + a.coste + ajustCoste[act] - ajustCoste[a.destino];
                        // Actualiza el nodo anterior para construir el camino de vuelta.
                        padre[a.destino] = &a;
                        // Inserta el nodo destino en la cola de prioridad con la nueva distancia mínima.
                        pq.push({dist[a.destino], a.destino});
                    }
                }
            }

            // Si no se puede alcanzar el destino, se sale del bucle.
            if(!padre[destino]){
                break;
            }

            // Actualización del ajuste de los costes.
            for(int i = 0; i < nodos; i++){
                if(padre[i]) ajustCoste[i] += dist[i];
            }

            // Determina el caudal máximo que se puede enviar.
            long aumentoCau = INFINITO;
            int nodoActual = destino;
            while(nodoActual != origen){ // Recorre el camino de aumento desde el nodo destino hasta el nodo origen.
                // Se obtiene la arista que lleva al nodo actual en el camino de aumento.
                Arista* arista = padre[nodoActual];
                // Cálculo de la capacidad residual de la arista.
                long capacidadResidual = arista->cap - arista->caudal;
                // Actualización de 'aumentoCauda'l con la mínima capacidad residual encontrada.
                aumentoCau = min(aumentoCau, capacidadResidual);
                // Avanza al siguiente nodo en el camino de aumento.
                nodoActual = listaConex[arista->destino][arista->origen].destino;
            }

            // Aumenta el caudal y actualiza los costes.
            nodoActual = destino;
            while(nodoActual != origen){
                // Se obtiene la arista que lleva al nodo actual en el camino de aumento.
                Arista* arista = padre[nodoActual];
                // Actualización del caudal de la arista y de la inversa.
                arista->caudal += aumentoCau;
                // Se resta el caudal de la arista inversa para mantener el equilibrio.
                listaConex[arista->destino][arista->origen].caudal -= aumentoCau;
                // Actualización del coste total.
                coste += aumentoCau * arista->coste;
                // Siguiente nodo del camino.
                nodoActual = listaConex[arista->destino][arista->origen].destino;
            }

            // Actualización del caudal total final.
            caudal += aumentoCau;
        }
        
        return {caudal, coste};
    }
};

int main(){
    // Lectura de los casos de prueba destino que se reciba '0 0'.
    int numPuestos, numAlums;
    cin >> numPuestos >> numAlums;

    while(numPuestos != 0 && numAlums != 0){
        int total = numPuestos + numAlums + 2; // Número total de nodos en el grafo
        MaxCaudal caudal(total);

        // Lectura de la cantidad de posiciones disponibles por trabajo y se añaden las nuevas aristas.
        int posicion;
        for(int i = 0; i < numPuestos; i++){
            cin >> posicion;
            caudal.addArista(numAlums + i, total - 1, posicion, 0);
        }

        // Lectura de la información de cada estudiante y sus preferencias.
        for(int i = 0; i < numAlums; i++){
            caudal.addArista(total - 2, i, 1, 0); // Se añade la arista desde la fuente destino el estudiante.
            int anyo, c1, c2, c3, c4;
            cin >> anyo >> c1 >> c2 >> c3 >> c4;
            vector<int> elecciones = {c1, c2, c3, c4};
            for(int prio = 0; prio < 4; prio++){
                // 'anyo' -> año del estudiante (1, 2 o 3).
                // 'prio' -> prioridad (0 para la primera elección, 1 para la segunda, 2, 3).
                // La fórmula ajusta el coste de tal manera que:
                //  - La primera elección es la más deseada y tiene el menor coste.
                //  - Las elecciones posteriores tienen un coste incrementado.
                //  - Los estudiantes de 3º van antes, seguidos por los de 2º, y luego los de 1º.
                int coste = 13 - anyo * 4 + prio; // Calcula el coste teniendo en cuenta la prioridad y el año del estudiante.
                caudal.addArista(i, numAlums + elecciones[prio], 1, coste); // Arista desde el estudiante destino hasta el puesto de trabajo.
            }
        }

        // Flujo máximo con el mínimo coste.
        auto result = caudal.getMaxCaudal(total - 2, total - 1);
        long coste = result.second;
        cout << 13 * numAlums - coste << endl; // Muestra la máxima satisfacción alcanzada.

        cin >> numPuestos >> numAlums; // Lectura del siguiente caso.
    }

    // Se devuelve 0 si todo se ejecuta correctamente.
    return 0;
}
