# Sockets TP1 - Correciones
## Nota: 10
Para poder desarollar el tp se decidio seguir la heuristica de dividir el tp en cuatro modulos:
  1. El juego (implemtancion de la logica del juego).
  2. El protocolo (Definicion de los metodos del protocolo con sus argumentos).
  3. El inputParse y la creacion de objetos mensajes (operacionDTO y respuestaDTO).
  4. Implementacion del cliente y el server.

### 1. El juego
Las clases que cree para poder implementar el juego y tienen un grado de importancia son: 
1. **ArchivoEscenario**: Clase que se encarga de encapsular  el recurso (archivo) escenario.txt de su apertura y cierre. Ademas se encarga del parseo del archivo para poder obtener los campos necesarios del escenario para inicializar otras clases.

2. **Juego**: Clase creada para poder tener acceso a las otras entidades como **Terreno**, **Gusano**, **ArchivoEscenario**. Es invocada y usada por la clase **Server** para delegarle toda la logica de juego y esta misma delega toda la logica del juego a **Terreno** y **Gusano**. De esta manera se logra minimizar el acoplamiento de la logica del juego con el Servidor (ya que el servidor no conoce la clase terreno, gusano, etc)

3. **Terreno**: Clase que encapsulara el tablero del juego compuesto por un vector de vectores de celda. Su comportamiento es el validar las posibles posiciones devueltas por el gusano y en caso de que se pueda mover, realizara el movimiento. Al finalzar este se aplicara la gravedad para que el gusano "caiga" al suelo.                

4. **Gusano**: Clase que modela al gusano. Se encargara de devolver todos los posiciones resultado del movimiento del gusano ya sea de "mover" , "jump para atras" , "jump para adelante", con el supuesto que se pueda mover libremente siempre. Luego **terreno** se encarga de validarlas y mover al gusano segun corresponda.
#### Diagrama de clases de la logica del juego.

<img src = "https://i.ibb.co/gd7MPT4/dc-Logic-Game.png">

### 2. El protocolo:
1. Una vez que se termino la logica del juego, se siguio con la implementacion de la **clase protocolo** arrancando con firma y luego su definicion de cada metodo
   1. Tratando de ser lo mas simetrico dado que si el protocolo tiene un metodo  **int enviarOperacion(...)** es muy probable que tenga un **int recibirOperacion()**.
   2. Ahora se definio que el protocolo tenga como atributo socket peer (socket resultado de hacer un accept (Lado servidor) - socket al aplicar un connect (cliente)) esto se lo transfiere por movimiento (std::move()) pasandole asi el ownership al protocolo para que haga los send/recv respectivos. Esta implementacion es mas flexibles a los futuros cambios.
       1. Por ejemplo Se podrian usar sockets UDP entonces bastaria pasarlo por movimiento en el constructor de protocolo.
       2. Se Desacopla el "setup del socket" del protocolo ( (En caso de socket TCP) el accept del lado del server  o el connect del lado de cliente) delegandole el "setup" a otra entidad.
   5. Tambien tiene como atributo el booleano para detectar en cualquier momento si se cerro o la conexion o no
   6. En caso de que no se reciba los bytes correspondientes se lanzara una excepcion **std::runtime_error** a excepcion del recibirOperacion si aca no recibimos ningun byte es porque el cliente cerro la conexion y tenemos que terminar el servidor.  

### 3. Input Parse y la creacion de objetos mensajes (OperacionDTO, respuestaDTO): 
  1. En este paso, necesitamos crear una clase para delegarle todo el trabajo de parsear el input del usuario y asi desacoplar el cliente de este parseo.
  2. Al tener un objeto cuyos atributos estan cargados con el input del usuario se tiene un metodo que retorna un objeto:
      1. *operacionDTO*: objeto mensaje que sera lo que enviara el cliente en lugar de enviar de a cachitos variables. La intencion de crear este objeto mensaje (uso del patron TDO) es hacer un
          send completo de todo el request, volviendo muy simple la api publica del Protocolo.  
  3. *RespuestDTO*: Nacio al visualizar que tenemos que enviar las posiciones del gusano (y un estado de respuesta en el caso de seleccionar la operacion del select) por esta razon se decidio
      enviar "el pack completo" encapsulado en este objeto mensaje. Manteniendo muy simple la api publica del protocolo.        
  4. Al terminar la creacion de los objetos mensajes DTO, se agrgo al protocolo los respectivos metodos como por ej: **Protocolo::enviarOperacionDTO(const OperacionDTO& operacionDto)** ,
     **OperacionDTO Protocolo::recibirOperacionDTO()**. de manera idem con **respuestaDTO**.
 
### 4.  Metodos de Server y Cliente:
1. Se implemento la **clase Server** que delegara toda la logica del juego a la clase **Juego** por esa razon tiene una instancia de este como atributo. Tambien tenemos el socket aceptador como atributo.
    1. En primer lugar se definieron los metodos del Server en el metodo **run**, aceptamos un nuevo cliente y le pasamos el ownership a una instancia de la clase protocolo.
    2. Luego obtenemos la operacion completa (*hacemos el recv completo*) retornada por el protocolo, preguntamos el tipo de operacion es, extraemos el dato que nos interesa y aplicamos la operacion.
    3. Para enviar la respuesta de la operacion se usa la **respuestaDTO** para de esta manera hacer *el send completo*.   
2. Luego se implemento la **clase Cliente** donde este tiene como atributo el skt cliente. En el metodo run luego de hacer el connect a este socket se le transfiere el ownership del socket al protocolo.
      1. Leemos una linea e instanciamos al inputParser para que lo parsee por nosotros. 
      2. luego le pedimos al inputParser que nos retorne la operacionDTO asociada al input parseado del usuario.
      3. Enviando la operacionDTO por el protocolo y segun el tipo de operacion, recibimos una respuesta donde es tratada en el cliente.  

#### Diagrama de clases de las entidades asociadas al envio/rec de mensajes y de red (Networking) : 
<img src= "https://i.ibb.co/SmM7JL5/dc-Logic-Net.png" >
Se eliminaron los const & y  & de los argumentos para simplificar el diagrama. Tambien no se incluyeron todos los metodos ni atributos de las clases mostradas para no saturar el diagrama.
   
### Diagrama de secuencias: 
  Diagrama de secuencia asociado a la logica del juego en particular al jump(salto) adelante del gusano:   
  <img src= "https://i.ibb.co/J35Ycx1/ds-Salto-Adelante-Gusano-Gusano-realizando-un-salto-hacia-adelante-con-exito.png"> 
  Diagrama de secuencia asociado a la obtencion del objeto operacionDTO resultado de la operacion select ingresada por el usuario. 
  <img src= "https://i.ibb.co/ZWymdXb/ds-Cliente-Selecciona-Escenario-Basic-Cliente-ingresa-Select-basic-y-esta-operacion-es-enviada-por-e.png" > 
