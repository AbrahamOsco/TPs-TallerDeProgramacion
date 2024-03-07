# TP2-Threads Correciones
Para poder desarollar el tp se divideron las tareas en:
1. Input Parser e implementacion de ActionDTO, AnswerDTO
2. Client, Server y la **herencia del  protocolo** para un solo cliente.
3. Se agrega la logica multithreading inicial (Thread, AcceptorThread, ClientThread).
4. Implementacion de las queue y el monitor (**MapQueuesProtected**).
5. Se agrega la parte final de multithreading! (ReceiverThread, SenderThread)  

#### Input Parser e implementacion de ActionDTO, AnswerDTO
1. Para desacoplar la logica del parseo del cliente de la clase cliente se creo la entidad InputParser que se encarga del parseo y nos retorna una **AcionDTO** que lo usuaremos para definir que operacion haremos
2. ActionDTO, como AnswerDTO son objetos creados para poder encapsular la informacion y transmitirla mas facil, de esta manera la API publica del protocolo sera muy simple ya que envia/recibe objetos DTO.

#### Implementacion del Client, Server y Protocol para un solo cliente.
1. Se siguio con la implementacion de la Clase Client, el envio de ActionDTO y AnswerDTO, creando las firmas del protocolo para implementar lo que pide el enunciado.
2. Luego como se esta haciendo uso del patron DTO y para poder separar los metodos asociados a la clase cliente y servidor (Esto para evitar perderse en el codigo a medida que escala la aplicacion) se uso la herencia, donde los metodos que usa el cliente estan en **ClientProtocol** y los metodos que usa el servidor estan en **ServerProtocol**. Los metodos en comun que ambas clases comparten estan en la clase Madre Protocol.      
3. A continuacion se realiza la definicion de las firmas de la clase madre protocolo y para las hijas por ejemplo si en la clase Client se creo: **void enviarAccion(unaAccion)**, entonces el metodo asociado esta en ServerProtocol y es: **ActionDTO recibirAccion()**.
4. Se creo el Servidor que envia objetos AnswerDTO y recibe actionDTO (En el servidor se instancia ServerProtocol, y en la clase cliente se instancia el ClientProtocol), el modelado de la cantidad de jugadores se hizo con una simple variable.
5. Se testea que funcionara bien la aplicacion con un solo cliente.

 #### Se agrega la logica multithreading inicial (Thread, AcceptorThread, ClientThread).
1. Ahora Se crea la clase abstracta Thread (el metodo **run** es abstracto). Se crean las clases AcceptorThread y ClientThread que heredan de la clase Thread.
  1. El Thread main (principal) se queda bloqueada en la 'q' y lanza el AcceptorThread (que se bloquea en el metodo **accept** para aceptar clientes). El thread Aceptador agrega nuevos clientes, limpia los clientes que se desconectaron y **killea** a todos los clientes cuando el **thread Main** cierra el socket aceptador. 
  2. Se crea la clase ClientThread y los metodos basicos como kill, isDead, etc. Me detengo aca y decidi pasar a implementar el monitor, debido que cada SenderThread tendra una queue y se necesita pushear un mensaje a todo el conjunto de queue, podria tener una raise condition (por ej: Un cliente se conecta al momento que pusheo a todo el conjunto de queue y  este recibe un mensaje que no debio haber recibido, porque el mensaje se envio antes de que el se conectara).

#### Se define el monitor: MapQueuesProtected         
 1. Se encapsula la coleccion de Queue usando un map, siendo la clave el idThread (un size_t, esto para poder identificar de manera univoca cada thread es como la PK de una base de datos) y el valor la queue asociada (en este caso es una queue de **AnswerDTO** porque el servidor envia solo este tipo de objeto al protocolo), como todo monitor se tiene tambien el mutx y tambien un atributo **cantJugAct** que usaremos para representar la cantidad de jugadores actuales. 
 2. Se decido que las colas a usar seran Bloqueantes (para evitar consumir el 100% del CPU al tener busy-wait (bucle que verifca constantemente que se cumpla una condicion) y ademas sera unbounded queue esto para no preocuparme por si la cola se llena (se descarta el valor), ademas como se tiene otro hilo que hace pop (**SenderThread**) es poco probable que la queue se llene. 
 3. Se reconoce que **una** critical seccion es al momento de **pushear en la queue** asi que se usa el lock raii (unique_lock) junto al mutex para no hacer el **unlock a mano** y obtener beneficios RAII. Ademas al momento de agregar una nueva queue se manda una AnswerDTO a todas queues actuales (incluyendo la nueva) (para actualizar el estado de la partida- cantidad de jugadores).  
 4. Tambien se protege los metodos en que se agrega/elimina AnswerDTO a la queue, cuando se notifiica que un jugador se deconecto.
 5. Finalmente al momento de hacer pop tengo que tener cuidado ya que si hago un lock y luego el pop bloqueante este tomaria el lock y no lo soltario hasta hacer un pop, pero no se puede pushear porque se necesita el lock y el pop no lo suelta (por que al inicio no hay nada que popear) y por lo tanto ocurrio un **deadLock**.

#### Finalizando el multithreading : ReceiverThread y SenderThread
1. Finalmente desde el ClientThread en el metodo run, lanzamos los ReceiverThread y el SenderThread (y joineo primero el sender y luego el receiver). Se pasan los booleanos atomicos por referencia, el skt para que envien mensajes y el monitor **MapQueuesProtected**. Ambos thread tienen su propio protocolo (este tiene  guardado una referencia del socket). Si el ReceiverThread detecta que el clienta se desconecto tambien provocara el cierre en el SenderThread.
2. El ReceiverThread: se dedica a recibir ActionDTO (s) (del tipo **Chat**) y a pushear AnswerDTO a la queue.
3. El SenderThread: Popea su cola respectiva encapsulada en mapQueueProtect (la obtiene usando el **threadID**) obteniendo una AnswerDTO y delega su envio al protocolo.       
### Diagramas 
<hr>

#### Diagrama de networking:
<img src= "https://i.ibb.co/qg4WBDF/dc-Net-Working.png" alt="diagrama de networking actualizado">

#### Diagrama asociado al multithreading y el monitor.
<img src = https://i.ibb.co/99rvXG1/dc-Threads-Actualizado-GO.png >

#### Diagrama de secuencia donde se muestra desde el input del cliente hasta el envio del "mensaje" al protocolo:  
<img src= "https://i.ibb.co/bRvxRDh/ds-Cliente-ingresa-la-accion-chat-con-Holaa-se-encapsula-en-una-Action-DTO-y-es-enviado-al-protocolo.png" > 

#### Diagrama de secuencia donde se muestra la interaccion de los threads y el uso del monitor:  
<img src= "https://i.ibb.co/89s515d/ds-Thread-Parte2-Secuencia-de-mensajes-del-Client-Thread-con-los-Receiver-Thread-y-Thread-Sender-y-c.png"  >
