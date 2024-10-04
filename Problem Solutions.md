# Problem Solutions using C++

Este documento explica cómo se han resuelto los problemas utilizando C++.

---

## PROBLEMA "subway network"

**Descripción:**  
Este programa C++ debe calcular el número mínimo de líneas de metro necesarias para conectar todos los puntos importantes de una ciudad y que estén a una distancia máxima 'd' de alguna línea de metro. Todas las líneas de metro deben empezar desde las coordenadas (0,0) (la estación central) y continuar recto.

### Enfoque de Solución:
- Se ha definido una estructura `Coord` para guardar las coordenadas (x, y) de los puntos importantes (leídos del input).
- El subprograma `calcDistancia` calcula la distancia perpendicular de un punto a una línea que pasa por el origen con un ángulo calculado como la inclinación entre el origen y uno de los puntos importantes dado.
- La función principal `contarLineas` calcula cuántas líneas de metro se necesitan. Marca los puntos cubiertos y cuenta las líneas necesarias. Para cada punto no cubierto, se calcula el ángulo de la línea desde el origen hasta ese punto, se determinan los puntos dentro de la distancia 'd' y se selecciona la línea que cubre más puntos como la mejor línea, para solo quedarnos con las necesarias.

---

## PROBLEMA "car vet"

**Descripción:**  
El problema consta de un tablero de m x n con coches (que ocupan dos espacios, o en vertical o en horizontal), un espacio libre y una casilla que no se puede usar. El objetivo es mover una serie de coches para lograr trasladar el espacio en blanco hacia una casilla que se necesita exponer. Los coches solo pueden moverse en línea recta y no pueden pasar por casillas bloqueadas (si ya hay un coche ahí o es la casilla que no se puede usar) ni salirse de la cuadrícula. El resultado debe ser una secuencia ordenada con los IDs de los coches que deben moverse para lograr el objetivo.

### Enfoque de Solución:
- Primero se han inicializado un tablero extendido (para la cuadrícula) y una matriz de distancias para controlar las distancias desde el espacio vacío hasta cada casilla.
- Usando una cola para realizar una búsqueda en anchura (como con grafos) desde el espacio vacío, se han actualizado las distancias mínimas en su respectiva matriz.
- Después, se ha verificado si es posible llegar a la ubicación que se pide consultando la matriz de distancias. Si es posible, se reconstruye la secuencia de movimientos hacia atrás, desde la ubicación r x c hasta el espacio vacío del principio, utilizando un stack para ir guardando los coches que se han movido.
- Por último, se muestra la secuencia resultado o, si no es posible llegar a dicha casilla, se imprime "impossible".

---

## PROBLEMA "job postings"

**Descripción:**  
Este problema consiste en asignar estudiantes a ciertos trabajos de manera que se maximice la satisfacción total de los estudiantes. Cada uno de ellos tiene un orden de preferencia para los trabajos y se prioriza a los estudiantes que lleven más años en la universidad. Para ello se utiliza una matriz de satisfacción que asigna diferentes valores a las preferencias de los estudiantes según el año en el que estén. El objetivo es encontrar una forma óptima de asignar estudiantes, asegurando que todos obtengan uno de los trabajos de su lista con el menor coste.

### Enfoque de Solución:
- Primero, se construye un grafo donde cada estudiante y cada trabajo son nodos, y se crean aristas que conectan a cada estudiante con los trabajos que ha seleccionado. Cada arista tiene una capacidad de uno y un coste que depende de 1- el año del estudiante y 2- la preferencia del trabajo.
- Luego, se añade un nodo origen que se conecta a todos los estudiantes y un nodo destino que, por su parte, se conecta a todos los trabajos con la capacidad igual al número de posiciones disponibles para cada trabajo.
- Usando el algoritmo de máximo caudal con el mínimo coste, se encuentra la asignación de estudiantes a trabajos que minimiza el coste total, que también corresponde a maximizar la satisfacción total de los estudiantes.
- Por último, el resultado se obtiene restando el coste total de la suma de las máximas satisfacciones, que ya había sido calculada antes.

---

## PROBLEMA "juice"

**Descripción:**  
Este problema se basa en conectar un generador de energía a varias casas usando cables. Cada casa (como nodo) posee tres atributos: el nodo padre del que proviene, una demanda de energía específica y un cable que tiene una capacidad máxima específica de energía que puede transmitir. Se debe maximizar el número de casas que pueden recibir energía del generador sin exceder la capacidad de los cables de las casas conectadas. Como resultado, se debe mostrar cuántas casas pueden recibir energía según un input dado.

### Enfoque de Solución:
- Primero se han modelado las casas y sus conexiones como nodos de un árbol, donde el nodo raíz es el generador de energía (por lo que se ha añadido un elemento más a la lista de casas que se reciben como input). Se lee la entrada y se construyen los nodos y sus conexiones.
- Después, se utiliza la recursividad para calcular cuántas casas pueden recibir energía desde el generador sin exceder las capacidades de los cables que conectan las casas. Cada nodo calcula su mejor solución combinando las necesidades de cada casa y las capacidades de sus hijos.
- Por último, se suman los resultados de todos los nodos conectados al generador para obtener el número máximo de casas que pueden conectarse al generador.
