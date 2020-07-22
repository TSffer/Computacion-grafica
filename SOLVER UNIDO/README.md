# Implementación Cubo Rubik

## 1.  Introducción

El cubo de Rubik es un rompecabezas de combinación tridimensional inventado en 1974 por el escultor yprofesor de arquitectura húngaro Ernő Rubik. A pesar del concepto relativamente simple, el cubo tiene másde 43 Quintillones (43.252.003.274.489.856.000) diferentes combinaciones de aleatorización. Sin embargo, ladisposición legal del Cubo de Rubik se puede resolver en 20 movimientos o menos, con el uso de una variedadde algoritmos. La parte más importante de resolver un cubo de Rubik es entender cómo funciona. Al mirarun cubo de Rubik, hay seis lados, cada uno con nueve piezas. Los lados se pueden rotar de muchas maneras,pero independientemente de lo que se haga al cubo (a menos que se desarme), las piezas centrales no semueven entre sí. Por lo tanto, cuando se resuelve el cubo, las piezas centrales no pueden moverse.

## 2.  Implementación


## 3.  Algoritmo de Thistlethwaite para resolver el Cubo Rubik

###  3.1 Notación de cubo de Rubik

Usamos letras para describir una rotación en el cubo, esta notación es común para cualquier algoritmoque resuelve el Cubo Rubik.

Una sola letra por sí sola se refiere a una rotación de la cara en sentido horario en 90 grados:

![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)

Una letra seguida de un apóstrofe significa girar esa cara en sentido antihorario 90 grados:

![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)


Una letra con el número 2 después de la letra significa un doble giro (180 grados):

![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)

