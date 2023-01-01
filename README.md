# TSPPDL Unicen

This Software solves Traveler Salesman Problem (TSP) with the variant Pickup and Delivery (PDL) and LIFO Loading (LF).

    Copyright (C) <2011  David Emmanuel Lopez, Javier Marsicano
    Copyright (C) <2022  David Emmanuel Lopez
    
    Contact: david.emmanuel.lopez@gmail.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

Este trabajo obtuvo el 4to puesto en el simposio EST del congreso JAIIO 41' (2012). Para mas información dirigirse a la [documentación](https://github.com/davidemmanuellopez/tsppdl-unicen/blob/main/doc/documento_final.pdf). 


Despues de 10 años, actualización a Qt5 e Igraph 0.9, con nuevo projecto CMake. Ahora igraph es un submodulo en git.

# Instrucciones de compilacion

Se debe tener qt5 dev instalado en el sistema.

* "git clone --recursive https://github.com/davidemmanuellopez/tsppdl-unicen && cd tsppdl-unicen"
* "mkdir build && cd build"
* "cmake .."
* "make"

# Windows

Para win x64, estan publicado el [binario](https://github.com/davidemmanuellopez/tsppdl-unicen/releases) con sus dependencias. Se debe descargar el archivo [datatest.zip](https://github.com/davidemmanuellopez/tsppdl-unicen/blob/main/datatest.zip) con los casos de prueba aparte. 
# Instrucciones de uso

Ir a File->Open, seleccionar subcarpeta datasets y elegir un archivo .tsp entre alguno de los datasets. Se recomienda de 25 o 51 nodos para comenzar.
En el bloque izquierdo se pueden elegir heurísticas de forma individual, y cantidad de iteraciones a aplicar, para fines didacticos.
El algoritmo VNS se aplica con el boton "Apply VNS", se puede seleccionar tamaño de la población (debido a que es un algoritmo genético) y cantidad de interaciones, población mas grande requiere mas recursos computacionales.

Por la salida estandar de consola se puede observar la cantidad de pasos del algoritmo VNS, el objetivo es 14. Una vez finalizado el proceso se muestra el costo de la solución nueva en la caja de texto "length after".

![Captura](/doc/screenshot.png "Captura de GUI TSPPDL Unicen")

