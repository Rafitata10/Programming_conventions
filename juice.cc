// Rafael Ramírez Salas - Ingeniería de Computadores - Universidad de Málaga
#include <iostream>
#include <vector>

using namespace std;

// Estructura que representa cada nodo (casa).
struct Casa {
    int parent; // Nodo padre.
    vector<int> hijos; // Hijos del nodo actual.
    int energ; // Energía que necesita la casa.
    int maxEnerg; // Capacidad máxima del cable.
    vector<int> sol; // Mejor solución para cada capacidad.

    // Constructor para la estructura Casa.
    Casa(int myP, int myE, int max) : parent(myP), energ(myE), maxEnerg(max){
        sol.resize(maxEnerg + 1, 0);
    }

    // Función principal para llamar a la función recursiva.
    int contar(vector<Casa>& list){
        contarRec(list);
        int ret = 0;
        // Encontrar la mejor solución recursivamente.
        for(int i = 0; i < sol.size(); i++){
            ret = max(ret, sol[i]);
        }
        return ret;
    }

    // Función recursiva para encontrar la mejor solución.
    void contarRec(vector<Casa>& list){
        // Incluir la contribución del nodo raíz (el generador infinito).
        for(int i = energ; i <= maxEnerg; i++){
            sol[i] = 1;
        }

        // Resolver para cada hijo y añadir la respuesta a 'sol'.
        for(int i = 0; i < hijos.size(); i++){
            list[hijos[i]].contar(list);
            sol = combinar(sol, list[hijos[i]].sol);
        }
    }

    // Combina las mejores soluciones de 'actual' y 'sig'.
    vector<int> combinar(const vector<int>& actual, const vector<int>& sig){
        vector<int> res(actual.size(), 0);
        // Se busca la mejor combinación de soluciones.
        for(int i = 0; i < actual.size(); i++){
            for(int j = 0; j < sig.size(); j++){
                if(i + j >= actual.size()){
                    break; // Se sale del bucle si se excede el tamaño de 'actual' porque no se puede combinar.
                }
                res[i + j] = max(res[i + j], actual[i] + sig[j]);
            }
        }
        return res;
    }
};

int main(void){
    int numCasas; // Número de casas en la favela.
    cin >> numCasas;
    
    vector<Casa> list;
    list.resize(numCasas + 1, Casa(0, 0, 0)); // Se añade un nodo extra para el generador.
    vector<int> padres(numCasas + 1, 0);
    list[0] = Casa(0, 0, 9999); // El primer elemtento es el nodo generador.

    // Lectura de los datos de cada casa.
    for(int i = 1; i <= numCasas; i++){
        int p, myE, max;
        cin >> p >> myE >> max;
        padres[i] = p;
        list[i] = Casa(p, myE, max);
    }

    // Añadir enlaces a los hijos.
    for(int i = 1; i <= numCasas; i++){
        list[padres[i]].hijos.push_back(i);
    }

    // Sumar la solución de cada hijo que se conecta al nodo raíz y materializa el número máximo de casas que pueden ser iluminadas.
    int res = 0;
    for(int i = 0; i < list[0].hijos.size(); i++){
        res += list[list[0].hijos[i]].contar(list);
    }

    cout << res << endl; // Muestra el número máximo de casas que pueden ser iluminadas.

    // Se devuelve 0 si todo se ejecuta correctamente.
    return 0;
}
