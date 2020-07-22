# Implementación Cubo Rubik

## 1.  Introducción

El cubo de Rubik es un rompecabezas de combinación tridimensional inventado en 1974 por el escultor yprofesor de arquitectura húngaro Ernő Rubik. A pesar del concepto relativamente simple, el cubo tiene másde 43 Quintillones (43.252.003.274.489.856.000) diferentes combinaciones de aleatorización. Sin embargo, ladisposición legal del Cubo de Rubik se puede resolver en 20 movimientos o menos, con el uso de una variedadde algoritmos. La parte más importante de resolver un cubo de Rubik es entender cómo funciona. Al mirarun cubo de Rubik, hay seis lados, cada uno con nueve piezas. Los lados se pueden rotar de muchas maneras,pero independientemente de lo que se haga al cubo (a menos que se desarme), las piezas centrales no semueven entre sí. Por lo tanto, cuando se resuelve el cubo, las piezas centrales no pueden moverse.

## 2.  Implementación

Para generar el cubo mayor, primero generamos un conjunto de vértices iniciales de cada cubo en los ejes x , y y luego recién creamos los puntos iniciales en el eje z, de esta manera creamos los 27 vértices iniciales para luego crear los 27 cubos con estos vértices iniciales. Estos 27 nuevos cubos son almacenadas en un vector llamado Rubik que nos servirá para manipular en adelante, características como la rotación.

### 2.1 Descripción de los Gráficos

En este caso se está utilizando la librería GLFW y Glad para la parte gráfica a continuación describimos algunas características de nuestra implementación:

#### 2.1.1 Vértices

Para graficar los cubos, realizamos una clase llamada cubo, que recibe como parámetros únicamente los vértices iniciales, y partir de ello genera todos los otros puntos y vértices necesarios.

#### 2.1.2 Colores

En el caso de los colores, cada cubo puede tener independientemente sus propios colores, que se les asigna mediante texturas de colores, algo que en conjunto genera un cubo mayor con los mismos colores por lado. Además las caras internas de los cubos, están con color negro para diferenciarlas de las caras externas que si tienen un color y textura definido.

#### 2.1.3 Textura

En nuestro caso dividimos la imagen ÜCSPCG.jpg.en 6 distintas imágenes en la cual cada una tiene una letra. Luego en la implementación mapeamos en cada cara del cubo una fracción de cada letra, de tal manera que se pueda ver una letra por cara en el Rubik.

#### 2.1.4 Renderizado

Cada cubo por otro lado tiene una función de dibujo, con el que se renderiza para mostrar en el display

#### 2.1.4 Camara

Para el caso de la cámara se ha realizado algunas implementaciones para poder manipular esta, en la subsección de controles, especificamos cuales son las formas de manipular la cámara.

![Cubo1](https://github.com/TSffer/Computacion-grafica/blob/master/SOLVER%20UNIDO/IMG/Cubo1.png)

![Cubo2](https://github.com/TSffer/Computacion-grafica/blob/master/SOLVER%20UNIDO/IMG/Cubo2.png)

### 2.2 Funcionalidades del programa

En esta sección describimos las funcionalidades y la forma de interacción con nuestro cubo de rubik para manipularlo.

#### 2.2.1 Rotación de camadas

En nuestra implementación es posible la rotación por camadas en los ejes x, y, z. Para esto al momento de rotar los vértices, es necesario rotar tambien el vector Rubik que contiene los 27 cubos, en realidad es un update, para luego en caso de otras rotaciones no tener inconvenientes. Asi mismo es posible ver un efecto al momento de realizar el giro, un efecto visual de rotación lenta.

#### 2.2.1 Controles

En la tabla 1 mostramos las distintas funcionalidades para interactuar con el programa.

### 2.3 Problemas en la Implementación

Ciertamente fue muy difícil conseguir el cubo con textura, ya que tuvimos algunos problemas, sin embargo todo se soluciono, y el próximo problema y reto es juntar la implementación con el solver. Una ves resuelto el Solver, nuestro siguiente paso es realizar un cubo de Rubik formado a su vez por otros cubos de rubik, estos cubos menores tienen que desordenarse poco a poco, y ademas separarse del centro, y posteriormente ordenarse y mientras se ordenan deben volver a su posición inicial para formar un cubo mayor ordenado.


## 3.  Algoritmo de Thistlethwaite para resolver el Cubo Rubik

###  3.1 Notación de cubo de Rubik

Usamos letras para describir una rotación en el cubo, esta notación es común para cualquier algoritmoque resuelve el Cubo Rubik.

Una sola letra por sí sola se refiere a una rotación de la cara en sentido horario en 90 grados:

![Rotación_1](https://github.com/TSffer/Computacion-grafica/blob/master/SOLVER%20UNIDO/IMG/R1.png)

Una letra seguida de un apóstrofe significa girar esa cara en sentido antihorario 90 grados:

![Rotación_2](https://github.com/TSffer/Computacion-grafica/blob/master/SOLVER%20UNIDO/IMG/R2.png)


Una letra con el número 2 después de la letra significa un doble giro (180 grados):

![Rotación_3](https://github.com/TSffer/Computacion-grafica/blob/master/SOLVER%20UNIDO/IMG/R3.png)

###  3.2 Integración con el Solver

En nuestro caso el algoritmo utilizado para realizar el solver, toma como entradas un serie aleatoria de rotaciones, lo que se traduce en un un cubo de inicio desordenado aleatoriamente, a partir de este punto inicial, resuelve el cubo y nos muestra como salida otra serie de pasos de rotaciones para llegar a la solución. Aprovechando de esto, nosotros unimos ambos programas, es decir si queremos desordenar el cubo, generamos una serie aleatoria de giros, que a su ves nos servirán como datos de entrada a nuestro algoritmo solver, una ves realizado esto, si queremos ordenarlo, ejecutamos el algoritmo de solver lo que nos devuelve una serie de paso a seguir para solucionar, esto en nuestro aso se almacena en un txt que es leído por nuestro programa principal y simplemente luego se utiliza para resolver el cubo de Rubik. Tanto al momento de desordenar y ordenar el cubo se puede apreciar los efectos en las rotaciones.














