# Código

## Cliente

* Hay varias copias dando vuelta por todas las clases, y algunas clases están vacias. Falta lógica

### Gameloop
Le falta mucho cariño, copien su gameloop del server y mantengan el mismo frame rate.  
* Están haciendo un sleep de tiempo constante. Encapsular la lógica que tiene el server de manejo de tiempo y sleep variable 
en una clase y reutilizarlo acá

### Recv thread
* no uses números mágicos para ver el tipo de mensaje. ¿Qué significa que te llegue un `type == 2`??
* El stop debe hacer un shutdown del socket **después** de setear el boooleano a false, ya que el server
puede nunca mandarte un mensaje como para destrabar el recv del protocolo

### Send thread
* el método stop debería hacer un `close` de la blocking queue exactamente después de que se setea a false el booleano

### TextureManager
* Es un poco complejo la construcción de cada textura, esto lo podrían haber manejado por archivo de configuración. El texture manajer
lee ese archivo, donde habrá una clave id para acceder a la textura, su path al archivo, y la posición de la imagen de donde recortarla.
Cada objeto vista solo tendría el id para acceder a ese mapa y recibir una referencia, y nada mas.

* Están creando la textura **cada vez que llaman a draw**. Esto es muy costoso. Las texturas ya deberían estar previamente cargadas
una unica vez por imagen, tenerlas almacenadas en un mapa de clave un id (preferentemente un enumerativo para que sea mas rapido
acceder al mapa, un string implica una comparación de strings que es mas costoso) y de valor tendrá una instancia de Texture
que pasa por referencia.

### Animation
La clase no es utilizada

### Camera
Pareciera estar codeado el feature pero no se aprecia en el juego. El juego se ve que renderiza todo el mapa, y cuanto mas grande sea
la ventana, mas porción del mapa ves.

### Hud

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Client.cpp#L151-L152

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/ButtonRefinery.cpp#L12-L14

Se usan siempre estos numeros magicos para renderizar los botones. Y estos numeros se dibujan bien cuando la pantalla es de 1280 x 720, pero cuando se agranda o minimiza la pantalla, el hud queda mal ubicado. Esto se soluciona teniendo una posicion relativa al ancho y largo de la pantalla. Para este caso en particuar, se tiene que para una pantalla de 1280 x 720, renderizas en el punto (1115, 2800) con tamaño (65, 50). Con esto ultimo deducis que para un botoncito usas 65 / 1280 en x y 50 / 720 en y. Para ajustar el tamaño de tu botoncito al de tu pantalla entonces multiplicas por `renderer.GetOutputWidth()` y `renderer.GetOutputHeigth()` respectivamente. En cuanto a la posicion en la que comenzas a renderizar, haces exactamente lo mismo. Para ejemplificar, en su metodo draw del ButtonRefinery, tendrian que hacer una transformacion similar a la siguiente (por favor usen constantes)

```C++
#define INITIAL_WIDTH 1280.0
#define INITIAL_HEIGHT 720.0

void ButtonWidtrap::draw(SDL2pp::Renderer &renderer) {
    float diffx = INITIAL_WIDTH / renderer.GetOutputWidth();
    float diffy = INITIAL_HEIGHT / renderer.GetOutputHeight();
    int posx = m_position.GetX() / diffx;
    int posy = m_position.GetY() / diffy;

    int sizex = m_size.GetX() / diffx;
    int sizey = m_size.GetY() / diffy;
    SDL2pp::Point pos(posx, posy);
    SDL2pp::Point size(sizex, sizey);

    m_textureManager.draw(renderer, m_name, pos, size, SDL_FLIP_NONE);
}
```

### Estás procesando de a un evento por loop del gameloop

Acordate de procesar varios eventos por vuelta para evitar un lag en el cliente (no se aprecia
porque no se puede hacer mucho, pero cuando agregues mas eventos de cliente vas a notar que tarda
mucho en aplicarse alguna acción que hagas, y se va a deber mayoritariamente a esta parte) <-- Esto se va notar mucho cuando uses valgrind

Procesá N eventos por vuelta en el gameloop.

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Core/Engine.cpp#L14-L22

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Events/EventManager.cpp#L17-L31

La forma en la que reciben y manejan los eventos no escala para la cantidad de eventos que van a tener. Una vez que hacen el `SDL_PollEvent`, ya podrian manejarlo.  


https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Core/Engine.cpp#L24-L42

Lo mismo sucede para su metodo Update del Engine. Pareciera que ese `Object* unit` no representa al snapshot. Entonces, deberian vaciar o sacar muchos eventos de la cola. Si sacan solo uno por gameloop, solo van a poder renderizar a un solo unit por loop. Las lineas 32 - 41 parecieran pertencer mas al metodo `Events()` que al de `Update()`, puede ser? Por otro lado, estamos bastante seguros que nunca se libera la memoria de ese `Object*`. 

### Todas las funciones principales de los hilos tienen que estar encerradas en un try catch.

Algunos ejemplos: RecvThread, SendThread.

## Common

### El socket tiene un constructor por default
Para qué? respeten RAII, no instancien objetos sin inicializarlos.

### Cola Bloqueante y Cola Protegida

* Ambas copian en su push, en vez de pasar por referencia y luego mover al objeto. No se deberia dejar pushear a una cola que esta cerrada.
* No retornes NULL en tu template de cola bloqueante, si quisieras tener una cola de `std::BlockingQueue<Foo>` va a fallar la compilación ya 
que `NULL` no se puede castear a la clase `FOO` (salvo que hagan chanchadas como definir un constructor con un parametro entero que no sea
explicito). Si cerraron la cola (Y SI ESTÁ VACIA), lancen excepción. Que el destructor no haga pops para vaciarla, dejá que el worker procese todo
lo que puede hasta que no haya mas, y ahi lanzá

* No está bueno lo que hacés en [el destructor de la blocking queue](https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Common/includes/BlockingQueue.h#L60). ¿Qué pasaría si instanciás una cola de `BlockingQueue<Foo>`? No asumas que podés crear la cola solo con punteros (u obligá que [siempre sean punteros](https://stackoverflow.com/questions/31769629/a-template-that-accepts-only-pointer-type-arguments))


### Protocolo

En lineas generales esta mal. Actualmente si el cliente envia un comando, el servidor no responde correctamente. Tener codigo simetrico facilita mucho a ver estos errores. Un ejemplo donde falla el programa es el siguiente. 

El servidor espera en su hilo recv:

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Server/src/Control/ClientConnection.cpp#L47-L52


Ya aca se ven un par de errores. `opcode` es del tipo `uint8_t`, entonces se esperaria que se reciban 1 bytes, no 2. Luego, `reinterpret_cast` **no** lo usen, usen el casteo de C con parentesis, o `static_cast` (en este ejemplo pueden crear directamente en el cliente un `opcode_cmd` de tipo uint16_t, lo hacen justo una linea antes del recv no se gasten en hacer casteos raros). Por ultimo, le estan pasando `opcode` en vez de pasar la direccion de memoria de opcode. Y otro comentario, por que usan el socket directamente. Que los mensajes pasen a traves de su PROTOCOLO. 

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Server/src/Control/ClientConnection.cpp#L68-L76

Los mismos errores suceden en su metodo `_receiveCommand`. Luego, en su Factory, una vez que identifican que tipo de comando es:

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Server/src/Control/Command/Command.cpp#L27-L32


reciben desde el protocolo con `recvResponse`:

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Common/src/Protocol.cpp#L92-L96

Noten que cada `recvResponse`, recibe exactamente 1 byte. 

Desde el cliente esta secuencia que deberia ser totalmente simetrica se ejecuta de la siguiente manera. Lo que sucede es lo siguiente:

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Thread/SendThread.cpp#L17-L22

Se manda el `actionType` a traves del Protocolo y luego se manda la `Position`. El `type` se manda en 1 byte y luego las Positions en dos mensajes de 2 (a diferencia de el recvResponse en el server que recibe 1) bytes a traves de sus metodos `sendPosition` del Protocolo. En muchisimos metodos del protocolo recuerden el endianness!!! 

Lo ideal es que para cada metodo de send, tengan su simetrico de recv en el protocolo. No esta de mas recordarles que se tienen que corresponder los bytes que se envian con los que se reciben. 

* En qué endianness puede estar el cliente? es siempre la misma endianness que puede tener el servidor? no asuman que en este tp corren cliente y servidor en la misma maquina, 
si mandan dos bytes para comandos, asegurensé que cualquier tipo de cliente puede recibirlos y procesarlos correctamente (esto sucede tanto en el [cliente](https://github.com/dyylanl/Dune/blob/Dune-v0.3/Common/src/Protocol.cpp#L49) como en el [server](https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Server/src/Control/ClientConnection.cpp#L48).

* No usen el socket directamente para enviar bytes, que la mensajería siempre pase por el protocolo primero, para que formatee todos los mensajes.

* No me gusta que el protocolo tenga logica de conexión del socket, pero bueno.

* Tienen muchos métodos similares, `recvHouse`, `recvCurrent`, `recvReq` en vez de un solo método genérico `recv(uint8_t &n)` y después que esos `recvX`, si los quieren tener para
mejorar la lectura de codigo, los tengan pero solo llamen a `recv(uint8_t&)`
    
* Piensen como escalaría su protocolo si el día de mañana deciden que no les entra la cantidad de request en 8 bytes, Cada uno de estos métodos lo tienen que cambiar para que maneje
2 bytes, acordarse de en cada uno manejar correctamente endianness, y mantener 5 funciones idénticas. Creen una y que el resto use esa genérica, o creen una sola y usen esa, encapsulen 
otras cosas en vez de encapsulár qué representa ese simple byte a recibir. Capaz a ustedes les interesa tener métodos que encapsulen varios llamados, como `recvBuilding`
```cpp
// Uso sobrecarga de métodos para no hacer métodos verbosos
void recv(Socket &skt, BuildingDTO &building) {
    // llama a protocol::recv(uint8_t&)
    this->recv(skt, building.id);
    // llama a protocol::recv(uint16_t&)
    this->recv(skt, building.life);
    // llama a protocolo::recv(std::string&)
    this->recv(skt, building.name);
}
```

Esta imple obliga a que BuildingDTO tenga un constructor por default y atributos publicos no constantes, == feito pero rapido. Otra forma sería que `BuildingDTO` sea una estructura
de atributos publicos **constantes** y un constructor RAII

```cpp
// No se puede sobrecargar operadores cuya unica variación sea el valor de retorno
BuildingDTO recv_building(Socket &skt) {
    uint8_t id;
    uint16_t life;
    std::string name;
    this->recv(skt, id);
    this->recv(skt, life); // internamente aplica el cambio de endianness
    this->recv(skt, name); // internamente implementa como debe recibirse un string por el socket

    return BuildingDTO(id, life, name);
}
```

No se compiquen, no usen bytes sueltos en su código, usen clases que les ayude a ustedes a tener un codigo limpio y facil de seguir.
## Server

### La clase de configuración, podria haber sido un singleton para no tener que estar pasandolá por parámetro en todos lados
* Es una de las pocas razones por la cual se recomendaría un patrón singleton. En este caso ganás claridad de codigo al no tener que estar pasando el `YAMLReader` por todos
lados (igual el nombre no me parece feliz, de dónde lee la configuración no le interesa al desarrollador, el día de mañana podés cambiar a usar JSON, y vas a tener
que cambiar la clase en todos lados. Si llamás a la clase `Config` y que internamente use un YAMLReader, o JSONReader, o lo que sea, te va a facilitar el refactor a 
posteriori).


### Si van a implementar una clase Thread, que esta immplemente el try catch para no olvidarse de hacerlo en cada main function que lancen

```cpp
Thread::start() {
    this->thread = std::thread(&Thread::safe_run, this);
}

void Thread::safe_run() {
    try {
        this->run(); // <- este es el método abstracto que todos los hijos implementan
    } catch(const ClosedSocketException &e) { // si el hilo ejecutaba comnunicación por un socket y lo cerraro (y se señalizó debidamente el cierre del hilo) entonce sno es un error
        if (! this->keep_running)
            fprintf(stderr, "%s\n", e.what());    
    } catch(const ClosedQueueException &e) { // si el hilo usaba una cola bloqueante y se cerró ordenadamente, no es un error
        if (! this->keep_running)
            fprintf(stderr, "%s\n", e.what());    
    } catch(const std::exception &e) {
        fprintf(stderr, "%s\n", e.what());
    } catch(...) {
        fprintf(stderr, "Unknown error in thread %s\n", this->name.c_str());
    }
}
```

* fprintf es un gris en cuanto a si es thread safe o no, los estandares no lo garantizan (salvo posix). Podrías usar un `ostringstream` y escribir a `std::cerr` que te garantiza atomicidad

```cpp
std::ostringstream oss;
oss << "[" << this->name << "] Unknown error" << std::endl;
std::cerr << oss.str();
```


### Game

En su clase Game tienen: listar, crearPartida y unirse
Y además tienen metodos que son especificos de un juego en particular o de como calcular el AStar. Son dos responsabilidad **MUY** distintas. 
Los Id que van creando crecen indefinidamente. Lo que deberia suceder es que haya un conjunto de ids para cada partida en particular. Y las partidas, en vez de identificarlas con un Id, identificarlas con el nombre de la partida. 

### Gameloop
Tienen comentado en Engine para el metodo `_processCommands` lo siguiente:

```
/*
 * 1° Popea un comando
 * 2° Ejecuta ese comando
 * 3° Pushea el resultado de ese comando en snapshot
 * 4° Vuelve a 1°
 */
```
El resultado del snapshot se deberia enviar solamente una vez por gameloop, para no saturar la red. Entonces, en primer lugar se popean y se ejecutan todos los comandos (o a lo sumo 20 o 30, como deseen implementarlo). Una vez que se ejecutan todos los comandos de ese gameloop, deberian tambien simular un delta de tiempo en el mundo del juego. A pesar de que nadie haya pusheado ningun comando, lo mas probable es que el juego se tenga que actualizar. Por ejemplo, si un edificio esta en construccion, en cada gameloop avanza un determinado tiempo su barrita de construccion. Por ultimo, se envia el snapshot. 


La estructura del GameLoop esta muy bien. Recuerden que ese `it` que le pasan a `_loop_iteration` es ese delta de tiempo del juego que tienen que simular (que avanzara construcciones, aumentara energia, quizas algun gusano ataque, etc.).

* Mas que un número de iteración ,deber ser un delta de tiempo transcurrido

### Estaría buenisimo encapsular la logica del chronometro en una clase para no mezclarlo con la logica del juego
Que se pueda hacer algo del estilo

```cpp
ConstantRateController rate_controller;
while (keep_running) {
    rate_controller.start();
    // devuelve 1/30 milisegundos, o el rate que hayan configurado. El modelo lo necesita para manejar eventos basados en tiempo, como lo puede ser entrenar una unidad
    _loopIteration(rate_controller.get_rate_loop()); 
    uint64_t sleep_time = rate_controller.finish(); // toma tiempo y hace la diferencia
    rate_controller.sleep_for(sleep_time); // podrían pasarle un parámetro extra
}
```

### El engine no debería tener lógica de procesar nuevas conexiones
Esto no es el argentum, no tenés una unica partida a la que le vas agregando jugadores en momentos randoms de la partida. Cuando se crea un engine debería arrancar con todos
los clientes de la partida (un engine == una partida), en el medio no se va a agregar nadie.

### Falta catchear excepciones en el hilo Engine


### [Clients login] Los clientes no se unen a una partida existente, se unen a una sala de espera hasta completar la sala y arrancar la partida. No podés unirte a una partida empezada

### No se entiende la logica detrás de la cola protegida finished_connections
Para qué lo necesitás? el engine solo borra un `InstanceId`(que es un alias de un entero, para qué allocan en el heap un entero?) y no hace nada mas. Si quieren handlear clientes que se vayan antes de tiempo durante la partida, usen una logica similar a la que tiene el aceptador. No inventen cosas alocadas.

### Para qué necesitas el atributo notifications en ClientConnection?
Pareciera no ser necesario en la clase.


### Map

Ojo con esto 

```C++
Terrain& Map::blockAt(int x, int y) {
    return reinterpret_cast<Terrain &>(this->terrrains.at(y * cols + x));
}
```

`terrains` es un `std::vector<std::vector<Terrain>>`.

En C++, polimorfismo va con punteros, sino van a tener object slicing. Deberia ser de `Terrain*`, o si quieren usar smart pointers. 

* Hay dos implementaciones distintas de `Map::canMove` ([aca](https://github.com/dyylanl/Dune/blob/Dune-v0.3/Server/src/Model/Map.cpp#L159-L161) y [acá](https://github.com/dyylanl/Dune/blob/Dune-v0.3/Server/src/Model/Map.cpp#L31-L33)). Estas implementaciones difieren apenas por un const, y dependiendo
como pasen los argumentos se llamará a una u otra. Fijensé en [este ejemplo](https://ideone.com/iJADYp) el comportamiento que están teniendo

### Polimorfismo, con punteros para evitar object Slicing.

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Server/src/Model/Attacker.cpp#L18-L20

Weapon es su clase padre. Deberia devolverse un puntero. 


## Editor

* Cuando se elimina una estructura, no se decrementa la cantidad de estructuras en el codigo. 
* El cargar esta mal implementado, no elimina las estructuras actuales, ni carga las que estan en el yaml. 
* Hay un slot mal conectado con la señal `on_button_const_ordos_clicked`
* Respetar mas el code style. No está bueno codear en spanglish
* `on_button_mute_clicked` debería manejar con un booleano si pausa o reproduce musica
```cpp
void MainWindow::on_button_mute_clicked()
{
    // un quickfix rapido para salir del paso, faltaría cambiarle el icono al boton
    static bool is_muted = false;

    if (is_muted) {
        this->music_player->play();
        is_muted = false;
    } else {
        this->music_player->pause();
        is_muted = true;
    }
}
```


# Documentación

Falta todo. Ver https://taller-de-programacion.github.io/documentacion-requerida


# UX/Jugabilidad

El juego no se pudo jugar, por lo que no pudimos chequear nada de UX ni jugabilidad


## Editor
* Si se agranda la pantalla, no se ajusta al tamaño de la pantalla. 
* En el mensaje de error de cantidad de jugadores - cantidad de construcciones, estaria bueno agregar cuantas construcciones y cuantos jugadores hay.  
* Una vez que se apaga la musica, no se puede volver a prender. 
* ¿Qué pasa si pones mas centros de construcciones que jugadores? es valido el mapa?
* No se maneja el caso de cancelar la selección de un archivo en el dialog del load (termina en excepcion por no poder
parsear el archivo yaml)

```cpp
terminate called after throwing an instance of '
YAML::BadFile
'
  what():  bad file: 
```

En aplicaciones de QT no es tan simple hacer un un manejo de errores, ya que todo el ecosistema QT trata de ser polite y devolverte defaults
(a la SQL), silenciando errores. Cuando metemos una librería de terceros como YAML-cpp que falla como dios manda, tenemos que hacer
unos hacks para evitar que nuestra aplicación termine mal. para esto, tienen que crearse una clase que herede de QApplication, y overridear
el método `notify`, donde ahí encapsularán los errores en un bloque try catch. Para un ejemplo de esto pueden verse esta clasesita que hice en 
[su momento cuando me topé con este problema](https://gitlab.com/fedemgp/trabajoprofesional/-/blob/master/src/view/application.cpp#L8-20)


* Si pongo 2 jugadores como cantidad de jugadores, puedo asignar centros de construccion para 3 jugadores (el de id 0, 1 y 2). Al salvar
el mapa salta un mensaje de error, que está bien, pero podría hacer el hack de aumentar a 3 jugadores y tener ids 0 1 y 2 para los jugadores,
cuando seguramente se quería 1 2 y 3.

* El filtro de archivos para cuando cargas un yaml está mal, filtra todo. Debería ser `"Yaml files (*.yml *.yaml)"`
* Cargar mapa no carga los centros de construcción y las especias
* El boton de especia debería estar dentro del grid layout


# Robustez / Valgrind

* NO hay manejo de errores adecuado. Es muy facil de terminarlos con un segmentation fault

Tanto el cliente como el server pierden memoria. 

## valgrind en el server
```
==38885== Thread 4:
==38885== Syscall param socketcall.recvfrom(buf) points to unaddressable byte(s)
==38885==    at 0x4C3B86E: __libc_recv (recv.c:28)
==38885==    by 0x4C3B86E: recv (recv.c:23)
==38885==    by 0x486C3AD: recv (socket2.h:38)
==38885==    by 0x486C3AD: Socket::recv(char*, unsigned long) const (Socket.cpp:210)
==38885==    by 0x124E8D: ClientConnection::_receiver() (ClientConnection.cpp:52)
==38885==    by 0x49A22C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x4BA8B42: start_thread (pthread_create.c:442)
==38885==    by 0x4C39BB3: clone (clone.S:100)
==38885==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==38885== 

terminate called without an active exception
==38885== 
==38885== Process terminating with default action of signal 6 (SIGABRT)
==38885==    at 0x4BAAA7C: __pthread_kill_implementation (pthread_kill.c:44)
==38885==    by 0x4BAAA7C: __pthread_kill_internal (pthread_kill.c:78)
==38885==    by 0x4BAAA7C: pthread_kill@@GLIBC_2.34 (pthread_kill.c:89)
==38885==    by 0x4B56475: raise (raise.c:26)
==38885==    by 0x4B3C7F2: abort (abort.c:79)
==38885==    by 0x4968BFD: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x497428B: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x49742F6: std::terminate() (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x12543A: std::thread::~thread() (std_thread.h:152)
==38885==    by 0x125008: ClientConnection::~ClientConnection() (ClientConnection.cpp:133)
==38885==    by 0x128BF1: std::__detail::_Hashtable_alloc<std::allocator<std::__detail::_Hash_node<std::pair<unsigned int const, ClientConnection>, false> > >::_M_deallocate_node(std::__detail::_Hash_node<std::pair<unsigned int const, ClientConnection>, false>*) (hashtable_policy.h:1894)
==38885==    by 0x128D5D: std::__detail::_Hashtable_alloc<std::allocator<std::__detail::_Hash_node<std::pair<unsigned int const, ClientConnection>, false> > >::_M_deallocate_nodes(std::__detail::_Hash_node<std::pair<unsigned int const, ClientConnection>, false>*) (hashtable_policy.h:1916)
==38885==    by 0x128D9B: std::_Hashtable<unsigned int, std::pair<unsigned int const, ClientConnection>, std::allocator<std::pair<unsigned int const, ClientConnection> >, std::__detail::_Select1st, std::equal_to<unsigned int>, std::hash<unsigned int>, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy, std::__detail::_Hashtable_traits<false, false, true> >::clear() (hashtable.h:2320)
==38885==    by 0x128DEC: std::_Hashtable<unsigned int, std::pair<unsigned int const, ClientConnection>, std::allocator<std::pair<unsigned int const, ClientConnection> >, std::__detail::_Select1st, std::equal_to<unsigned int>, std::hash<unsigned int>, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy, std::__detail::_Hashtable_traits<false, false, true> >::~_Hashtable() (hashtable.h:1532)
==38885== 


==38885== FILE DESCRIPTORS: 4 open (3 std) at exit.
==38885== Open AF_INET socket 4: 127.0.0.1:8082 <-> 127.0.0.1:53424
==38885==    at 0x4C3B60F: accept (accept.c:26)
==38885==    by 0x486C443: Socket::accept() const (Socket.cpp:169)
==38885==    by 0x124144: Accepter::_acceptClient(int) (Accepter.cpp:4)
==38885==    by 0x124219: Accepter::run() (Accepter.cpp:49)
==38885==    by 0x49A22C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x4BA8B42: start_thread (pthread_create.c:442)
==38885==    by 0x4C39BB3: clone (clone.S:100)
==38885== HEAP SUMMARY:
==38885==     in use at exit: 1,609,635 bytes in 27,939 blocks
==38885==   total heap usage: 31,996 allocs, 4,057 frees, 2,529,041 bytes allocated
==38885== 
==38885== Thread 1:
==38885== 8 bytes in 1 blocks are still reachable in loss record 1 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x134456: int* std::vector<int, std::allocator<int> >::_M_allocate_and_copy<__gnu_cxx::__normal_iterator<int const*, std::vector<int, std::allocator<int> > > >(unsigned long, __gnu_cxx::__normal_iterator<int const*, std::vector<int, std::allocator<int> > >, __gnu_cxx::__normal_iterator<int const*, std::vector<int, std::allocator<int> > >) (stl_vector.h:1511)
==38885==    by 0x132573: std::vector<int, std::allocator<int> >::operator=(std::vector<int, std::allocator<int> > const&) [clone .isra.0] (vector.tcc:226)
==38885==    by 0x132946: Game::put(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int, int) (Game.cpp:23)
==38885==    by 0x132CC5: Game::createGame(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (Game.cpp:44)
==38885==    by 0x126F55: ClientLogin::execute(unsigned short, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (ClientLogin.cpp:65)
==38885==    by 0x1271D3: ClientLogin::run() (ClientLogin.cpp:23)
==38885==    by 0x49A22C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x4BA8B42: start_thread (pthread_create.c:442)
==38885==    by 0x4C39BB3: clone (clone.S:100)


==38885== 64 bytes in 1 blocks are still reachable in loss record 91 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x12C384: std::_Deque_base<NewConnection*, std::allocator<NewConnection*> >::_M_initialize_map(unsigned long) (stl_deque.h:624)
==38885==    by 0x12C456: std::_Deque_base<NewConnection*, std::allocator<NewConnection*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x12BC31: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:7)
==38885==    by 0x115635: main (main.cpp:16)
==38885== 
==38885== 64 bytes in 1 blocks are still reachable in loss record 92 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x12B494: std::_Deque_base<unsigned int*, std::allocator<unsigned int*> >::_M_initialize_map(unsigned long) (stl_deque.h:624)
==38885==    by 0x12B566: std::_Deque_base<unsigned int*, std::allocator<unsigned int*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x12A3B0: Engine::Engine(Game&, ConfigurationReader&, NonBlockingQueue<NewConnection*>&) (Engine.cpp:64)
==38885==    by 0x12BC77: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:9)
==38885==    by 0x115635: main (main.cpp:16)
==38885== 
==38885== 64 bytes in 1 blocks are still reachable in loss record 93 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x125DF4: std::_Deque_base<Command*, std::allocator<Command*> >::_M_initialize_map(unsigned long) (stl_deque.h:624)
==38885==    by 0x125FB6: std::_Deque_base<Command*, std::allocator<Command*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x12A3D7: Engine::Engine(Game&, ConfigurationReader&, NonBlockingQueue<NewConnection*>&) (Engine.cpp:66)
==38885==    by 0x12BC77: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:9)
==38885==    by 0x115635: main (main.cpp:16)
==38885== 
==38885== 64 bytes in 1 blocks are still reachable in loss record 94 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x125DF4: std::_Deque_base<Command*, std::allocator<Command*> >::_M_initialize_map(unsigned long) (stl_deque.h:624)
==38885==    by 0x125FB6: std::_Deque_base<Command*, std::allocator<Command*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x12A3F7: Engine::Engine(Game&, ConfigurationReader&, NonBlockingQueue<NewConnection*>&) (Engine.cpp:67)
==38885==    by 0x12BC77: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:9)
==38885==    by 0x115635: main (main.cpp:16)
==38885== 
==38885== 64 bytes in 1 blocks are still reachable in loss record 95 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x125DF4: std::_Deque_base<Command*, std::allocator<Command*> >::_M_initialize_map(unsigned long) (stl_deque.h:624)
==38885==    by 0x125FB6: std::_Deque_base<Command*, std::allocator<Command*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x126005: BlockingQueue<Command*>::BlockingQueue() (BlockingQueue.h:18)
==38885==    by 0x124FB9: ClientConnection::ClientConnection(unsigned int, unsigned int, Socket&, NonBlockingQueue<unsigned int*>&, NonBlockingQueue<Command*>&) (ClientConnection.cpp:90)


==38885== 288 bytes in 1 blocks are possibly lost in loss record 142 of 199
==38885==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x40147D9: calloc (rtld-malloc.h:44)
==38885==    by 0x40147D9: allocate_dtv (dl-tls.c:375)
==38885==    by 0x40147D9: _dl_allocate_tls (dl-tls.c:634)
==38885==    by 0x4BA9834: allocate_stack (allocatestack.c:430)
==38885==    by 0x4BA9834: pthread_create@@GLIBC_2.34 (pthread_create.c:647)
==38885==    by 0x49A2398: std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)


==38885== 512 bytes in 1 blocks are still reachable in loss record 149 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x12A97C: std::_Deque_base<unsigned int*, std::allocator<unsigned int*> >::_M_create_nodes(unsigned int***, unsigned int***) [clone .isra.0] (stl_deque.h:662)
==38885==    by 0x12B4B5: std::_Deque_base<unsigned int*, std::allocator<unsigned int*> >::_M_initialize_map(unsigned long) (stl_deque.h:636)
==38885==    by 0x12B566: std::_Deque_base<unsigned int*, std::allocator<unsigned int*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x12A3B0: Engine::Engine(Game&, ConfigurationReader&, NonBlockingQueue<NewConnection*>&) (Engine.cpp:64)
==38885==    by 0x12BC77: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:9)
==38885==    by 0x115635: main (main.cpp:16)
==38885== 
==38885== 512 bytes in 1 blocks are still reachable in loss record 150 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x1252BC: std::_Deque_base<Command*, std::allocator<Command*> >::_M_create_nodes(Command***, Command***) [clone .isra.0] (stl_deque.h:662)
==38885==    by 0x125E15: std::_Deque_base<Command*, std::allocator<Command*> >::_M_initialize_map(unsigned long) (stl_deque.h:636)
==38885==    by 0x125FB6: std::_Deque_base<Command*, std::allocator<Command*> >::_Deque_base() (stl_deque.h:438)
==38885==    by 0x12A3D7: Engine::Engine(Game&, ConfigurationReader&, NonBlockingQueue<NewConnection*>&) (Engine.cpp:66)
==38885==    by 0x12BC77: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:9)
==38885==    by 0x115635: main (main.cpp:16)


==38885== 720 bytes in 1 blocks are still reachable in loss record 156 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x138EBF: std::vector<Terrain, std::allocator<Terrain> >* std::vector<std::vector<Terrain, std::allocator<Terrain> >, std::allocator<std::vector<Terrain, std::allocator<Terrain> > > >::_M_allocate_and_copy<__gnu_cxx::__normal_iterator<std::vector<Terrain, std::allocator<Terrain> > const*, std::vector<std::vector<Terrain, std::allocator<Terrain> >, std::allocator<std::vector<Terrain, std::allocator<Terrain> > > > > >(unsigned long, __gnu_cxx::__normal_iterator<std::vector<Terrain, std::allocator<Terrain> > const*, std::vector<std::vector<Terrain, std::allocator<Terrain> >, std::allocator<std::vector<Terrain, std::allocator<Terrain> > > > >, __gnu_cxx::__normal_iterator<std::vector<Terrain, std::allocator<Terrain> > const*, std::vector<std::vector<Terrain, std::allocator<Terrain> >, std::allocator<std::vector<Terrain, std::allocator<Terrain> > > > >) (stl_vector.h:1511)
==38885==    by 0x1366B3: std::vector<std::vector<Terrain, std::allocator<Terrain> >, std::allocator<std::vector<Terrain, std::allocator<Terrain> > > >::operator=(std::vector<std::vector<Terrain, std::allocator<Terrain> >, std::allocator<std::vector<Terrain, std::allocator<Terrain> > > > const&) [clone .isra.0] (vector.tcc:226)
==38885==    by 0x136890: Map::Map(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (Map.cpp:14)
==38885==    by 0x1322E8: Game::Game(int, ConfigurationReader) (Game.cpp:35)
==38885==    by 0x12BC09: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:6)
==38885==    by 0x115635: main (main.cpp:16)

==38885== 720 bytes in 1 blocks are still reachable in loss record 157 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x121177: std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_create_storage(unsigned long) (stl_vector.h:361)
==38885==    by 0x1212E3: std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_Vector_base(unsigned long, std::allocator<std::vector<char, std::allocator<char> > > const&) (stl_vector.h:305)
==38885==    by 0x123C50: std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::vector(unsigned long, std::vector<char, std::allocator<char> > const&, std::allocator<std::vector<char, std::allocator<char> > > const&) (stl_vector.h:524)
==38885==    by 0x12052F: MapReader::getMap() (MapReader.cpp:17)
==38885==    by 0x13689B: Map::Map(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (Map.cpp:15)
==38885==    by 0x1322E8: Game::Game(int, ConfigurationReader) (Game.cpp:35)
==38885==    by 0x12BC09: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:6)
==38885==    by 0x115635: main (main.cpp:16)


==38885== 900 bytes in 30 blocks are still reachable in loss record 160 of 199
==38885==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x121137: std::_Vector_base<char, std::allocator<char> >::_M_create_storage(unsigned long) (stl_vector.h:361)
==38885==    by 0x121283: std::_Vector_base<char, std::allocator<char> >::_Vector_base(unsigned long, std::allocator<char> const&) (stl_vector.h:305)
==38885==    by 0x123ABB: std::vector<char, std::allocator<char> >::vector(std::vector<char, std::allocator<char> > const&) (stl_vector.h:555)
==38885==    by 0x123B72: std::vector<char, std::allocator<char> >* std::__uninitialized_fill_n<false>::__uninit_fill_n<std::vector<char, std::allocator<char> >*, unsigned long, std::vector<char, std::allocator<char> > >(std::vector<char, std::allocator<char> >*, unsigned long, std::vector<char, std::allocator<char> > const&) (stl_uninitialized.h:237)
==38885==    by 0x123C0F: std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_fill_initialize(unsigned long, std::vector<char, std::allocator<char> > const&) (stl_vector.h:1596)
==38885==    by 0x123C5E: std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::vector(unsigned long, std::vector<char, std::allocator<char> > const&, std::allocator<std::vector<char, std::allocator<char> > > const&) (stl_vector.h:525)
==38885==    by 0x12052F: MapReader::getMap() (MapReader.cpp:17)
==38885==    by 0x13689B: Map::Map(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >) (Map.cpp:15)
==38885==    by 0x1322E8: Game::Game(int, ConfigurationReader) (Game.cpp:35)
==38885==    by 0x12BC09: Server::Server(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int) (Server.cpp:6)
==38885==    by 0x115635: main (main.cpp:16)

==38885== 1,024 bytes in 1 blocks are still reachable in loss record 162 of 199
==38885==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x4B92C23: _IO_file_doallocate (filedoalloc.c:101)
==38885==    by 0x4BA1D5F: _IO_doallocbuf (genops.c:347)
==38885==    by 0x4BA0D5B: _IO_file_underflow@@GLIBC_2.2.5 (fileops.c:485)
==38885==    by 0x4BA1E15: _IO_default_uflow (genops.c:362)
==38885==    by 0x4B9BB17: getc (getc.c:40)
==38885==    by 0x49D8700: __gnu_cxx::stdio_sync_filebuf<char, std::char_traits<char> >::underflow() (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x49E6805: std::istream::sentry::sentry(std::istream&, bool) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x498E1E6: std::basic_istream<char, std::char_traits<char> >& std::operator>><char, std::char_traits<char>, std::allocator<char> >(std::basic_istream<char, std::char_traits<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x12BB32: Server::run() (Server.cpp:22)
==38885==    by 0x11563D: main (main.cpp:17)
==38885== 
==38885== 1,024 bytes in 1 blocks are still reachable in loss record 163 of 199
==38885==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38885==    by 0x4B92C23: _IO_file_doallocate (filedoalloc.c:101)
==38885==    by 0x4BA1D5F: _IO_doallocbuf (genops.c:347)
==38885==    by 0x4BA0FDF: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:744)
==38885==    by 0x4B9F754: _IO_new_file_xsputn (fileops.c:1243)
==38885==    by 0x4B9F754: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1196)
==38885==    by 0x4B94056: fwrite (iofwrite.c:39)
==38885==    by 0x4A02B44: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x4A02E9A: std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x127193: ClientLogin::run() (ClientLogin.cpp:21)
==38885==    by 0x49A22C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38885==    by 0x4BA8B42: start_thread (pthread_create.c:442)
==38885==    by 0x4C39BB3: clone (clone.S:100)

```

## valgrind en el Cliente
```
==38743== Thread 2:
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x1209A5: RecvThread::run() (RecvThread.cpp:28)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E7894E: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869184: Protocol::recvType(Socket&, int&) (Protocol.cpp:244)
==38743==    by 0x1209F3: RecvThread::run() (RecvThread.cpp:29)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Use of uninitialised value of size 8
==38743==    at 0x5E7882B: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E78978: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869184: Protocol::recvType(Socket&, int&) (Protocol.cpp:244)
==38743==    by 0x1209F3: RecvThread::run() (RecvThread.cpp:29)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E7883D: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E78978: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869184: Protocol::recvType(Socket&, int&) (Protocol.cpp:244)
==38743==    by 0x1209F3: RecvThread::run() (RecvThread.cpp:29)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E789AE: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869184: Protocol::recvType(Socket&, int&) (Protocol.cpp:244)
==38743==    by 0x1209F3: RecvThread::run() (RecvThread.cpp:29)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
Se recibe objeto tipo: 1
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x1209FD: RecvThread::run() (RecvThread.cpp:30)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x120A43: RecvThread::run() (RecvThread.cpp:32)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Use of uninitialised value of size 8
==38743==    at 0x120A65: RecvThread::run() (RecvThread.cpp:32)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E7894E: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x486945A: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Use of uninitialised value of size 8
==38743==    at 0x5E7882B: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E78978: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x486945A: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E7883D: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E78978: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x486945A: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E789AE: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x486945A: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E7894E: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869475: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Use of uninitialised value of size 8
==38743==    at 0x5E7882B: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E78978: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869475: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E7883D: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E78978: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869475: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x5E789AE: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x5E870F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x4869475: Protocol::recvUnit(Socket&, int&, int&, bool&, int&, int&, int&, int&, int&, bool&) (Protocol.cpp:281)
==38743==    by 0x120C7F: RecvThread::run() (RecvThread.cpp:44)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
Se recibe: (30,30)
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x1209DE: RecvThread::run() (RecvThread.cpp:28)
==38743==    by 0x5E262C2: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==38743==    by 0x602AB42: start_thread (pthread_create.c:442)
==38743==    by 0x60BBBB3: clone (clone.S:100)
==38743== 
==38743== Thread 1:
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x48E534F: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.18.2)
==38743==    by 0x48E917A: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.18.2)
==38743==    by 0x125F72: SDL2pp::Renderer::Copy(SDL2pp::Texture&, sdl2pp_libcpp_optional::optional<SDL2pp::Rect> const&, sdl2pp_libcpp_optional::optional<SDL2pp::Rect> const&, double, sdl2pp_libcpp_optional::optional<SDL2pp::Point> const&, int) (Renderer.cc:99)
==38743==    by 0x11F2B2: TextureManager::drawFrame(SDL2pp::Renderer&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, SDL2pp::Point, SDL2pp::Point, SDL2pp::Point) (TextureManager.cpp:24)
==38743==    by 0x11ECCE: TrikeCL::draw(SDL2pp::Renderer&, TextureManager&) (TrikeCL.cpp:15)
==38743==    by 0x119D83: Engine::Render(SDL2pp::Renderer&) (Engine.cpp:38)
==38743==    by 0x117FEE: Client::launch() (Client.cpp:153)
==38743==    by 0x116852: main (main.cpp:31)
==38743== 
==38743== Conditional jump or move depends on uninitialised value(s)
==38743==    at 0x48E5372: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.18.2)
==38743==    by 0x48E917A: ??? (in /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.18.2)
==38743==    by 0x125F72: SDL2pp::Renderer::Copy(SDL2pp::Texture&, sdl2pp_libcpp_optional::optional<SDL2pp::Rect> const&, sdl2pp_libcpp_optional::optional<SDL2pp::Rect> const&, double, sdl2pp_libcpp_optional::optional<SDL2pp::Point> const&, int) (Renderer.cc:99)
==38743==    by 0x11F2B2: TextureManager::drawFrame(SDL2pp::Renderer&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, SDL2pp::Point, SDL2pp::Point, SDL2pp::Point) (TextureManager.cpp:24)
==38743==    by 0x11ECCE: TrikeCL::draw(SDL2pp::Renderer&, TextureManager&) (TrikeCL.cpp:15)
==38743==    by 0x119D83: Engine::Render(SDL2pp::Renderer&) (Engine.cpp:38)
==38743==    by 0x117FEE: Client::launch() (Client.cpp:153)
==38743==    by 0x116852: main (main.cpp:31)

```

Recomiendo corran valgrind desde algún ide que ya filtre un poco el ruido de librerías como yaml-cpp o sdl2. Probé correr su cliente con CLion y filtra
muchisimas cosas de ruido molesto. La salida es mas facil de ver que tirando valgrind desde consola (a pesar de que puse un archivo de supresión)
## Editor
* no se inicializa `cant_construcciones` en el constructor de Escenario. Podrian usar directamente el size de su vector de construcciones. 
* Si se intentan cambiar las filas y columnas desde el boton, muchas veces termina con seg fault. Esto se debe a un index out of bound en una instancia
de QVector
```
ASSERT failure in QVector<T>::operator[]: "index out of range"
```

* Crear un centro de construcción pegado al borde del mapa termina en un sigsegv
* Variables no inicializadas usadas en bloques condicionales

```
Conditional jump or move depends on uninitialised value(s)
  in MainWindow::on_actionSave_triggered() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:101
  1: MainWindow::on_actionSave_triggered() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:101
  2: MainWindow::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:176
  3: MainWindow::qt_metacall(QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:224
  4: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  5: QAction::triggered(bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  6: QAction::activate(QAction::ActionEvent) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  7: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  8: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  9: QWidget::event(QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  10: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  11: QApplication::notify(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  12: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  13: QApplicationPrivate::sendMouseEvent(QWidget*, QMouseEvent*, QWidget*, QWidget*, QWidget**, QPointer<QWidget>&, bool, bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  14: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  15: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  16: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  17: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  18: QGuiApplicationPrivate::processMouseEvent(QWindowSystemInterfacePrivate::MouseEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  19: QWindowSystemInterface::sendWindowSystemEvents(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  20: /usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5.15.3
  21: g_main_context_dispatch in /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  22: /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  23: g_main_context_iteration in /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  24: QEventDispatcherGlib::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  25: QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
Uninitialised value was created by a stack allocation  1: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3



Conditional jump or move depends on uninitialised value(s)
  in MainWindow::on_actionSave_triggered() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:107
  1: MainWindow::on_actionSave_triggered() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:107
  2: MainWindow::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:176
  3: MainWindow::qt_metacall(QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:224
  4: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  5: QAction::triggered(bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  6: QAction::activate(QAction::ActionEvent) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  7: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  8: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  9: QWidget::event(QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  10: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  11: QApplication::notify(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  12: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  13: QApplicationPrivate::sendMouseEvent(QWidget*, QMouseEvent*, QWidget*, QWidget*, QWidget**, QPointer<QWidget>&, bool, bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  14: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  15: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  16: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  17: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  18: QGuiApplicationPrivate::processMouseEvent(QWindowSystemInterfacePrivate::MouseEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  19: QWindowSystemInterface::sendWindowSystemEvents(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  20: /usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5.15.3
  21: g_main_context_dispatch in /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  22: /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  23: g_main_context_iteration in /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  24: QEventDispatcherGlib::processEvents(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  25: QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
Uninitialised value was created by a stack allocation  1: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3



Conditional jump or move depends on uninitialised value(s)
  in Escenario::guardar(QString) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:106
  1: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
  2: std::ostream& std::ostream::_M_insert<long>(long) in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
  3: YAML::Emitter& YAML::Emitter::WriteIntegralType<int>(int) in /usr/include/yaml-cpp/emitter.h:145
  4: YAML::operator<<(YAML::Emitter&, int) in /usr/include/yaml-cpp/emitter.h:237
  5: Escenario::guardar(QString) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:106
  6: MainWindow::on_actionSave_triggered() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:117
  7: MainWindow::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:176
  8: MainWindow::qt_metacall(QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:224
  9: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  10: QAction::triggered(bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  11: QAction::activate(QAction::ActionEvent) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  12: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  13: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  14: QWidget::event(QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  15: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  16: QApplication::notify(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  17: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  18: QApplicationPrivate::sendMouseEvent(QWidget*, QMouseEvent*, QWidget*, QWidget*, QWidget**, QPointer<QWidget>&, bool, bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  19: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  20: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  21: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  22: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  23: QGuiApplicationPrivate::processMouseEvent(QWindowSystemInterfacePrivate::MouseEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  24: QWindowSystemInterface::sendWindowSystemEvents(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  25: /usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5.15.3
Uninitialised value was created by a heap allocation  1: operator new(unsigned long) in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so
  2: MainWindow::MainWindow(QWidget*) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:10
  3: main in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/main.cpp:8



Conditional jump or move depends on uninitialised value(s)
  in Escenario::guardar(QString) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:107
  1: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
  2: std::ostream& std::ostream::_M_insert<long>(long) in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30
  3: Escenario::guardar(QString) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:107
  4: MainWindow::on_actionSave_triggered() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:117
  5: MainWindow::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:176
  6: MainWindow::qt_metacall(QMetaObject::Call, int, void**) in /home/fedemgp/Escritorio/tp-dune/grupo4/build-Editor-Desktop-Debug/editor_autogen/EWIEGA46WW/moc_mainwindow.cpp:224
  7: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  8: QAction::triggered(bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  9: QAction::activate(QAction::ActionEvent) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  10: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  11: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  12: QWidget::event(QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  13: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  14: QApplication::notify(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  15: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  16: QApplicationPrivate::sendMouseEvent(QWidget*, QMouseEvent*, QWidget*, QWidget*, QWidget**, QPointer<QWidget>&, bool, bool) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  17: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  18: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  19: QApplicationPrivate::notify_helper(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
  20: QCoreApplication::notifyInternal2(QObject*, QEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
  21: QGuiApplicationPrivate::processMouseEvent(QWindowSystemInterfacePrivate::MouseEvent*) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  22: QWindowSystemInterface::sendWindowSystemEvents(QFlags<QEventLoop::ProcessEventsFlag>) in /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
  23: /usr/lib/x86_64-linux-gnu/libQt5XcbQpa.so.5.15.3
  24: g_main_context_dispatch in /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
  25: /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0.7200.1
Uninitialised value was created by a heap allocation  1: operator new(unsigned long) in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so
  2: MainWindow::MainWindow(QWidget*) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:10
  3: main in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/main.cpp:8


Conditional jump or move depends on uninitialised value(s)
  in Escenario::eliminar_todas_estructuras() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:251
  1: Escenario::eliminar_todas_estructuras() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:251
  2: Escenario::~Escenario() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:284
  3: Escenario::~Escenario() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/escenario.cpp:285
  4: MainWindow::~MainWindow() in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:33
  5: main in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/main.cpp:11
Uninitialised value was created by a heap allocation  1: operator new(unsigned long) in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so
  2: MainWindow::MainWindow(QWidget*) in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/mainwindow.cpp:10
  3: main in /home/fedemgp/Escritorio/tp-dune/grupo4/Editor/main.cpp:8


```

### Como generar un archivo de supresión para poder correr valgrind en el cliente
teniendo este script de python
```python
#!/usr/bin/python3

# quick&dirty script para sacar los pids del log de valgrind
# para generar un file de supresiones

import sys
import re
import fileinput

try:
    if len(sys.argv) != 2:
        raise BaseException(f"Usage: {sys.argv[0]} <Filepath>")

    filename = sys.argv[1]
    for line in fileinput.input(filename, inplace = True):
       if not re.search('==[0-9]+==.*', line):
          print(line, end="")
except BaseException as e:
    print(f"Error: {e}")
    print("Input a valid valgrind log file")

```

corren una aplicación que saben que no leakea (el cliente de ustedes no sirve para esto). Pueden tomar el ejemplo de la clase
[sdlpp_events](https://github.com/Taller-de-Programacion/clases/blob/master/bibliotecas-gui/sdlpp/src/mainSdlEvents.cpp) (aunque deberían
agregarle manejo de sonidos y musica para el tp final, y poder suprimir todos los falsos positivos).  Corren este ejecutable con valgrind

```bash
valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --gen-suppressions=all --log-file=minimal.log ./sdlpp-events
```

una vez obtenido el archivo minimal.log, ejecutan el script de python que le quitará información no util. Una vez hecho eso tienen un archivo de supresión
para usarlo en su maquina (y solo ahí, este archivo variará en función de la maquina de cada uno). Ejecutan el cliente de la 
siguiente manera

```bash
valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --suppressions=minimal.log ./Client localhost 8080
```

## Server

Cuando hay un cliente conectado y se aprieta `q` en el servidor, leakean memoria y quedan hilos sin joinear. Esto es asi porque en el stop que reciben sus Engines solamente se pone el booleano del gameloop en false y se cierra las colas que no estan activas (su `finished_connections`), pero no se libera la memoria del objeto de ClientsConnected, que tiene a todos los hilos receptores y emisores, los cuales no son joineados. En su stop, o al final de su gameloop, ademas se deberian cerrar las colas de los hilos emisores y cerrar los sockets de los clientes para que puedan hacer el join y liberar la memoria alocada. 


## Client

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Client.cpp#L151-L153

No se libera la memoria de estos botones. 


En RecvThread recuerden que por como esta ahora se pisa el puntero del primer Objeto que se crea, y al menos de ese objeto se pierde memoria. 


# Performance

El server y editor tienen un consumo muy bueno!


El cliente es poco performante al cargar las texturas en cada uso. 

https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/Client/src/Graphics/TextureManager.cpp#L37-L69

Al tener una camara, deben renderizar solamente las partes que entran dentro de la misma y se veran en la pantalla. No tiene sentido renderizar todo. 


# Instalación (4/5)

Tanto el cliente como el servidor se pueden instalar correctamente. Muy bien! Seria ideal que si no se pasa un archivo de configuracion en el servidor, este sea elegido por defecto.
Falta la instalacion del editor. 

En su config.yaml tienen path absolutos: https://github.com/dyylanl/Dune/blob/69775a21d0d82860685d4e08fd9d26a7ffe0dab1/config.yaml#L3

Este debería ser un path relativo, y mas aún, cuando tengan múltiples mapas, será un directorio el cual contiene todos los mapas. 

* El instalador se parece extrañamente a uno de [cuatris anteriores](https://github.com/mauro7x/argentum/blob/master/installer.sh), que coincidencia no?
(no se roben autoria de otros, agradezcanlé al autor). Igual con lo que habian hecho en cmake les sobraba:

```bash
# El flag env=prod es para que internamente resuelva los paths a donde se deben copiar los binarios y assets
cmake -DENV=prod ..
make -j3
sudo make install
```

* Está muy bueno lo que hicieron en el cmake para no hardcodear los paths!

```cmake
ADD_DEFINITIONS(-DDATA_PATH="${PROJECT_SOURCE_DIR}/Client/")
```
Pero mi olfato me dice que no les va a funcionar al instalar el juego si borran la carpeta donde compilaron (ya que
esta variable siempre apunta a `${PROJECT_SOURCE_DIR}/Client/` sin importar si compilan para producción o desarrollo).
Podrían extenderlo un poco mas para cuando compilan para "desarrollo" o "producción", pasando una opción a cmake (con el flag `-D`)
y tener algo como esto

```cmake
option(DEV "Habilita compilación para desarrollo, seteando paths a los assets localmente" OFF)

# Cambiar esto a false cuando se haga el release
if (DEV)
        ADD_DEFINITIONS(-DDATA_PATH="${PROJECT_SOURCE_DIR}/Client/")
else()
        ADD_DEFINITIONS(-DDATA_PATH="/var/dune/")
endif()

```

Pueden compilar para producción modificando el valor de `DEV` a ON en el archivo de cmake, o llamando `cmake -DDEV=YES ..`

* Falta compilar el editor en el mismo cmake (add_subdirectory y agregar una directiva de instalación para el editor)

# Cliente - Servidor

## No soporta multiples partidas. 

## Login tiene un protocolo confuso. 

El cliente que crea una partida no deberia enviar la cantidad de jugadores requeridos en la partida, sino que deberia enviar el nombre de la partida y el mapa que va a usar. La cantidad de jugadores requeridos viene definido por el mapa (es la cantidad de centros de construccion). Quedaria algo asi:

1. El servidor envia los nombres de los mapas disponibles (sumado a la cantidad de jugadores requeridos de una partida con este mapa, quizas una vista previa del mapa para que el cliente la pueda renderizar en el lobby, etc.). 

2. El cliente elige crear una partida entre la lista de partidas que hay. 

## Server

Para un hilo ClientLogin (del lado del servidor) solo se puede elegir una opcion entre listar, unirse y crear y finaliza el hilo. Lo que va a suceder en general es que se pide listar al menos una vez antes de elegir la accion particular. Por lo tanto, deberia estar en un while su run de ClientLogin. 

Tienen un error conceptual en las etapas del juego. Se puede pensar que el juego tiene 3 etapas. La primera, donde los jugadores se unen a la partida. Una segunda, donde se juega. Y una ultima, donde se indica quien es el ganador. La segunda etapa es la que se corresponde con el game loop. No deberian mezclar las primeras dos. Si lo hacen, se va a poder seguir aceptando jugadores una vez que inicio la partida. 

Mas aun, una partida no deberia comenzar hasta que no se unan todos los jugadores requeridos. Una posible solucion seria que en vez de agregar las `new_connection` a una cola protegida, agregarlos a una cola bloqueante de la partida que se cierre ni bien llega el ultimo cliente. Entonces en el run de su hilo Engine, antes de entrar en el gameloop, tendrian un loop en el que popean de esta cola bloqueante de nuevas conexiones. Una vez que se unieron `required` jugadores, arrancan la segunda etapa. Es importante que cierren la cola o marquen de alguna manera que no se aceptan mas jugadores en la partida, porque si un cliente se quiere unir a una partida ya comenzada deberia recibir algun mensaje de error, y continuar en el Lobby. 


Otra opcion podria ser proteger la partida en si para que se puedan agregar los nuevos jugadores. La secuencia quedaria de la siguiente manera.
Desde ClientLogin se llama al `games.joinGame(gameName, socket, ...)`. Este games es su objeto de la clase Game, que seria lo que hicieron para el tp2. Game, tendra un `std::map<game_name, Engine>`, donde `Engine` son sus hilos que corren las partidas. Entonces `Engine`, en su primera etapa podria estar bloqueado (en una condition_variable por ejemplo) esperando a que se cumpla la condicion de partida llena (req/req). A su vez, `Engine` tendria un metodo protegido `add_player`, el cual agrega al jugador en la partida. Este metodo seria llamado desde el metodo `joinGame` de su objeto clase Game. Si no se puede agregar al jugador, podria lanzar una excepcion, o retornar un codigo de error, el cual se forwardearia hasta el ClientLogin, indicandole al cliente que el joinGame no fue exitoso, y por lo tanto se debe quedar en su etapa de Login. Si el codigo de error es exito, recien ahi entonces finaliza el login. 


## Cliente

Nunca se hace la conversion coordenadas del server (metros por ejemplo) a coordenadas del cliente (pixeles). Por ahora esta en 1 - 1. 


# Features
No se pudieron probar ninguno de los features listados abajo.

### Editor 
* Falta que se rendericen los edificios. 

## Terreno
## A*


### Distintos tipos de terreno hacen mover a la unidad a velocidades distintas
### Se puede construir unicamente en la roca
### infanteria es el unico qiue puede moverse sobre cimas
### Especia crece en la arena
### Cuanta mas especia, mas rojiso el suelo

## hay tres casas para seleccionar

## Juego configurable

## Unidades
### Cosechadora
#### cosecha especia
#### cada N segundos llega su tanque de especia y retorna a la refineria mas cercana
#### la descarga tarda M segundos
#### 1 especia == 1 unidad de oro
#### luego de depositar, retorna donde estaba cosechando. si no hay mas, se mueve al lugar mas cercano con especia (maximo 5 bloques distancia)
#### Sino, retorna a base
### Unidades

### Gusano de arena
#### Aparece random
#### se come victimas cercanas
#### No se pueden destruir
#### solo salen en la arena

## Armamento
### Cada una tiene un daño, animación frecuencia de disparo y bonifiación ante distintas unidades
### rifle de asalto
### lanza misiles
### cañon
### cañon 22mm
### onda de sonido
### cañon de plasma

## Infantería
### Cada infantería tiene edificio que lo genera, tiempo de centrenamiento, vida, velocidad, rango, armamento y costo
### Algunas unidades son exclusivas de algunas casas
### ligera
### fremen (atreides)
### infateria pesada
### sardaukar (solo harkonen)


## Vehiculo
### disponible para algunas casas
### todas tienen edificio, arma, rango, velocidad, tiempo de construcción, costo y vida
### trike (harkonnen y atreides)
### tanque sonico (atreides)
### raider (ordos)
### desviador (ordos)
### tanque
### devastador (harkonnen)
### cosechadora

## Energia
### todos los edificos y construir unidades requieren energia
### trampas de viento aumentan energia
### Si la cantidad de energia es < que lo cosumido por edificios => construye mas rapido, sino se va a ver muy perjudicado

## Edificios
### Solo se construyen sobre roca
### Unidades no pueden moverse a traves de edificios
### Edificios tienen que estar a 5 bloques de otro edificio
### edificios ocupan un espacio determinado
### Edificios crean unidades
#### Cuantos mas edificios, mas rapido el entrenamiento
### Edificios se pueden demoler
#### Retorna dinero (fraccion) y reduce consumo energia

### Refinería
#### tiene capacidad de 5000 especias
#### El excedente se pierde
#### construir mas edificios aumente la capacidad

### fabrica ligera
### fabrica pesada
### trampa de aire
### refinería
### silo
### cuartel
### palacio

### Centro construcción
#### si lo destruyen pierden la partida

## Jugabilidad
### Camara muestra porción del mapa
### utilizar colores para mostrar a que jugador pertenece la unidad
### se puede seleccionar una unidad o varias (arrastrando mouse)
### click derecho indica a donde moverse
### click derecho sobre unidad enemiga la ataca

## Sonidos
## Notificaciones ante eventos (construcción, ataque, etc)
## musica ambiental

## animaciones

## Interfaz de usuario
### informacion de la unidad/edificio seleccionado
### vista de distintos recursos

# Extras
No hay. 