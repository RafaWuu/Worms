# Worms - Manual de usuario
## Requerimientos de Software
El juego se tendría que poder correr en cualquier distribución de Linux que provea un compilador compatible con los estándares C17, C++17 y POSIX 2008.
## Instalación
* Clona el [Repositorio de Github](https://github.com/RafaWuu/Worms)
* Ejecuta el instalador installer.sh
````
sh installer.sh
````
Esto instalará:
* los binarios client y server en /usr/bin
* los assets y archivos de configuración en /etc/
## Configuración
Tanto el servidor como el cliente se pueden configurar mediante el archivo configuration.yaml. En el archivo se encuentran (entre otras cosas) las armas, donde uno podrá cambiar variables como la munición que posee, o el daño que inflige.
Los mapas de juego se encuentran en  scenarios.yaml; aquí uno puede crear nuevas mapas o modificar mapas existentes, agregando/eliminado gusanos y vigas.
##Ejecución 
*Para ejecutar un servidor:
````
./server <puerto>
````
para cerrar su ejecución se debe ingresar la letra q
* Para ejecutar  un cliente:
````
./client
````
Luego de iniciar el cliente se abrirá un diálogo para configurar la conexión
````
IP Port
````
Una vez conectado se abrirá la ventana del lobby donde puede ejecutar
* New Game: crea una partida
  * se mostrará un listado de escenarios disponibles (scenarios.yaml) 
  * al seleccionar el escenario deberá clickear en Start para iniciar
* Join Game: se une a una partida
  * se mostrará un listado de las partidas disponibles y sus IDs
  * al seleccionar el ID de la partida deberá esperar que el creador de esta la inicie
* Start: inicia la partida
## Juego

### Controles:
  - Movimiento
    - ->  <-  :  mueven y cambian la dirección (derecha, izquierda) del gusano 
    - a : salto hacia adelante 
    - s :  salto hacia atrás
  - Disparar
    - Mouse Botón Izquierdo [hold] :  apuntar, se puede cambiar el ángulo de mira moviendo el mouse
    - Mouse Botón Derecho :  según el arma:
     [hold] : se potencia el arma 
     [click] : se dispara el arma
    - 1, 2, 3, 4, 5 : cambiar cuenta regresiva de los proyectiles



