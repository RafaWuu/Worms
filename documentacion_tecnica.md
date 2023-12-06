# Worms - Documentación Técnica

Documentación técnica del trabajo práctico grupal de la materia Taller de Programación cuatrimestre 2023

## Introducción

En este documento se muestran a grandes rasgos los principales componentes de la arquitectura del programa, de la estructura de hilos utilizada y del protocolo utilizado para la comunicación entre el servidor y los clientes.

## Comunicación cliente - servidor

La comunicación entre cliente y servidor se da en dos grandes etapas diferenciadas:

*    Antes de crear la partida, el cliente está en el "lobby" y la comunicación con el servidor se dará de manera sincrónica. Esta etapa termina cuando el cliente crea exitosamente una partida, se une a una previamente creada o abandona la conexión.
*    Luego, y hasta que la partida termine o la conexión se cierre, cada cliente se comunicará de manera asincrónica con el server. Cada cliente tendrá un canal por el cual mandar comandos al juego y uno del cual recibir snapshots del estado de la partida, funcionando de manera independiente entre sí

### Protocolo base

El protocolo es de tipo binario. Los valores con más
de un byte se transforman a la endianness de la red
antes de ser enviados y deben ser reconvertidos al
momento de ser leídos.

En el caso de tener que enviar cadenas de texto, estas se envían codificadas
en ASCII precedidas por un entero sin signo de dos
bytes representando la cantidad de caracteres.

Los valores de punto flotante se envían codificados utilizando aritmética de punto fijo. Para esto, el módulo del valor a enviar se multiplica por 10000 y se envía como un entero sin signo de 4 bytes precedido de un entero sin signo de un 1 byte que será 0 o 1 dependiendo de si el número original era negativo o positivo respectivamente.

### Lobby

Una comunicación tipo entre los clientes y el servidor se daría de forma similar a la que se muestra en el siguiente diagrama de secuencias:

![](https://i.imgur.com/I6DLxqt.png)

El protocolo de comunicación desde el **cliente** es el siguiente (los números corresponden a enteros sin signo de un byte salvo que se indique lo contrario):

*    Creación de partida
    -    88 01 l escenario
    -    Siendo escenario el nombre del escenario como un vector de bytes y l un entero sin signo de dos bytes el tamaño del vector
*    Pedido de unirse a partida
    -    88 02 id
    -    Siendo el id de la partida un número sin signo de dos bytes
*    Pedido de listar partidas
    -    88 03
*    Pedido de listar escenarios
    -    88 04
    
El protocolo de comunicación de parte del **servidor** es el siguiente (los números corresponden a enteros sin signo de un byte salvo que se indique lo contrario):

*    Mensaje de error
    -    89 01 x
    -    Siendo x un codigo de error
*    Informar al cliente su id
    -    89 02 id
    -    Siendo el id del cliente un número sin signo de dos bytes
*    Confirmación de éxito al crear o unirse a partida
    -    89 03 id
    -    Siendo el id de la partida un número sin signo de dos bytes
*    Lista de partidas
    -    89 04 n {id l escenario players max_players status}
    -    Siendo n un número de dos bytes la cantidad de partidas a leer. Luego, n veces:
   	 +    id un número de dos bytes el id de la partida
   	 +    escenario el nombre del escenario como un vector de bytes y l un entero sin signo de dos bytes el tamaño del vector
   	 +    players un número de dos bytes la cantidad actual de jugadores
   	 +    max_players un número de dos bytes la cantidad máxima de jugadores
   	 +    status un número de un byte, 1 si la partida empezó y 0 si aun esta por iniciar
*    Lista de escenarios
    -    89 05 n {l escenario worms}
    -    Siendo n un número de dos bytes la cantidad de escenarios a leer. Luego, n veces:
   	 +    escenario el nombre del escenario como un vector de bytes y l un entero sin signo de dos bytes el tamaño del vector
   	 +    worms un número de dos bytes la cantidad de gusanos en el escenario
    

### Juego

En el juego, una comunicación tipo entre un cliente y el servidor se daría de forma similar a la que se muestra en el siguiente diagrama de secuencias:

![](https://i.imgur.com/VR6MJ1T.png)


Una comunicación tipo entre los clientes y el servidor se daría de forma similar a la que se muestra en el siguiente diagrama de secuencias:

![](https://i.imgur.com/I6DLxqt.png)

El protocolo de comunicación desde el **cliente** es el siguiente (los números corresponden a enteros sin signo de un byte salvo que se indique lo contrario):

*    Inicio de partida
    -    86 01

    
* Comando de movimiento
    -    86 02 worm_id x
    -    Siendo x igual a 1 para moverse a la izquierda, 2 para moverse a la derecha y 3 para frenar


* Comando de salto hacia adelante
    -    86 03 worm_id


* Comando de salto hacia atrás
    -    86 04 worm_id


* Comando de disparo
    -    86 05 worm_id


* Comando de apuntado
    -    86 06 worm_id 01 x y
    -    Representando x e y, floats codificados según se comentó previamente, las coordenadas de apuntado


* Comando de parar apuntado
    -    86 06 worm_id 02


* Comando de potenciar ataque
    -    86 07 worm_id 01


*    Comando de parar de potenciar ataque
    -    86 07 worm_id 02


*    Comando de cuenta atrás
    -    86 09 worm_id countdown


*    Comando de cambiar arma
    -    86 10 worm_id weapon_id
    
El protocolo de comunicación de parte del **servidor** es el siguiente (los números corresponden a enteros sin signo de un byte salvo que se indique lo contrario):

* Mensaje de error
  * 87 01 x
  * x el código del error


* Enviar escenario inicial
    -    88 02 height width n {entity_id entity_info}
    -    Siendo height y width, floats codificados según se comentó previamente, las dimensiones del escenario, n un número de 2 bytes la cantidad de entidades, entity_id el tipo de entidad y entity_info una serie de bytes variable para cada entidad según se especificara en secciones siguientes


* Enviar repartición de worms
    -    88 03 n {worm_id client_id}
    -    Siendo n un número de 2 bytes la cantidad de worms, worm_id un número de 2 bytes el id del worm y client_id un número de 2 bytes el id del cliente al que fue asignado


* Enviar snapshot
    -    88 04 worm_id time wind n {entity_id entity_info}
   	 +    Siendo worm_id el worm activo
   	 +    time y wind, floats codificados según se comentó previamente, el tiempo restando del turno y el viento respectivamente
   	 +    n un número de 2 bytes la cantidad de entidades, entity_id el tipo de entidad y entity_info una serie de bytes variable para cada entidad según se especificará en secciones siguientes


* Enviar fin del juego
    -    88 05 client_id
    -    Siendo client_id un número de 2 bytes el ganador del juego
    
#### Envío de escenario inicial

Al inicio de la partida se envían las siguientes entidades (los números corresponden a enteros sin signo de un byte salvo que se indique lo contrario):

* **Vigas**: entity_type x y height width angle
    - x, y, height, width, angle floats


* **Suelo**: entity_type x y height width angle
    - x, y, height, width, angle floats


* **Worm**: entity_type worm_id x y dir state health weapon
    - worm_id: 2 bytes
    - x, y, floats
    - dir es 1 si el worm está mirando hacia la derecha
    - weapon el id del arma inicial
    - state es un número de dos bytes representando el estado del gusano

El tipo de entidad puede tomar los siguientes valores:

	*    BEAM = 0x002,
	*    WORM = 0x004,
	*    GROUND = 0x80,

El estado del gusano se representa como una máscara de bits compuesta de la siguiente manera:

	*    NoState = 0x000,
	*    Alive = 0x001,
	*    Standing = 0x002,
	*    Walking = 0x004,
	*    Jumping = 0x008,
	*    Rolling = 0x010,
	*    Falling = 0x020,
	*    Firing = 0x040,
	*    Aiming = 0x080,
	*    Powering = 0x100,
	*    Active = 0x200,

Otras entidades pueden o no estar en la lista que se envía, y en caso de estarlo se enviará únicamente el par {entity_id, entity_type}, siendo responsabilidad del cliente leerlo correctamente para que no se altere el significado del flujo de bytes.

#### Envío de snapshots

Luego de cada tick del juego se envían las siguientes entidades (los números corresponden a enteros sin signo de un byte salvo que se indique lo contrario):

* **Proyectil**: entity_type proyectil_type x y angle
    - x, y, height, width, angle floats

    
* **Explosion**: entity_type explosion_type radius x y
    - x, y, radius floats


* **Provisión**: entity_type x y
    - x, y floats


* **Worm**: entity_type worm_id x y dir state health {weapon_info}
    - worm_id: 2 bytes
    - x, y, floats
    - dir es 1 si el worm está mirando hacia la derecha
    - weapon_info una serie de bytes dependiente del arma
    - state es un número de dos bytes representando el estado del gusano

Tanto el tipo de proyectil como el tipo de explosion corresponden al tipo de arma que las produjo. El valor que tome no es parte fija del código sino que puede ser modificado en los archivos de configuración.

El tipo de entidad puede tomar los siguientes valores:

	*    WORM = 0x004
	*    PROYECTIL = 0x0010
	*    PROVISION = 0x0020
	*    EXPLOSION = 0x0040

El estado del gusano se representa igual que al mandar el escenario inicial

La información del arma consiste, en el mismo orden en que se expresa, de:

    *    El tipo de arma
    *    Un número de 2 bytes en el caso de que la munición no sea infinita
    *    Un float representando el ángulo de mira en el caso de que tenga mira manual
    *    Dos floats x e y representando las coordenadas de apuntado en el caso de un ataque teledirigido
    *    Un número de un byte entre 0 y 255 representando la potencia en el caso de un arma con potencia variable
    *    Un float en el caso de que el arma tenga cuenta regresiva

Otras entidades pueden o no estar en la lista que se envia, y en caso de estarlo se enviara unicamente el par {entity_id, entity_type}, siendo responsabilidad del cliente leerlo correctamente para que no se altere el significado del flujo de bytes.

## Arquitectura

### Cliente

En el cliente, sin tener en cuenta los hilos utilizados por el programa de librerías de terceros, se tienen solo los hilos sender y receiver para la comunicación con el juego, los cuales interactúan entre sí a través del rendererer loop.

Se muestra en la siguiente figura un diagrama de la arquitectura del cliente:

![](https://i.imgur.com/NHmgLQI.png)

### Servidor

En el servidor, el thread main se encarga de lanzar a los
threads accepter y game_reaper, además de monitorear la
entrada estándar a la espera de la orden de cerrar el
servidor.

El thread accepter espera por nueva conexiones de
clientes, además de ser el encargado de limpiar a los
threads clientes cuando su conexión termina o el servidor
se cierra prematuramente

El thread game_reaper se comunica con los threads de
juegos a traves de una blocking queue donde las partidas
terminadas o sin jugadores se suscriben a la espera de ser
joineadas

En principio, cuando se establece una nueva conexión, se
crea un nuevo thread para la comunicación sincrónica con
el cliente. Además este tiene la responsabilidad de lanzar
el thread game cuando el cliente crea un nuevo juego

Cuando se crea el juego, se crea además un thread extra de
comunicación con el cliente que actuará como el sender. El
thread original se convertirá en el receiver, recibiendo
 los mensajes del cliente por socket y comunicandoselos al
juego mediante una blocking queue de comandos

El thread juego por cada tick procesara estos comandos,
simulara el gameworld y mandara una snapshot al thread
sender correspondiente a cada cliente utilizando una queue
de eventos.
