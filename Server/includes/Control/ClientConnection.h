//
// Created by gogpeep on 17/6/22.
//

#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H


#include <thread>
// ----------------------- //
#include "../defs.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/Protocol.h"

class ClientConnection {
    // id unico de la conexion asignado por el game cuando se une a el.
    InstanceId connection_id;
    // peer del cliente actual, asignado por el engine
    Socket peer;
    // cola compartida de conexiones finalizadas, una vez terminada la ejecucion del cliente este se pushea aca para ser
    // limpiado por el engine
    NonBlockingQueue<InstanceId*>& finished_connections;
    // mapa al q se conecto el cliente
    Id map;

    // control de sender/receiver. comparten el finished_thread entonces si ambos terminan
    // pueden llamarlo al mismo tiempo y producir una RC muy particular.
    std::mutex m;
    int finished_threads;

    std::thread sender;
    // cola bloqueante para enviar los mensajes en orden
    BlockingQueue<int*> snapshot;

    std::thread receiver;
    // cola no bloqueante para meter los comandos
    NonBlockingQueue<int*>& commands;

    void _sender();
    void _receiver();
    //void _recvCommand();
    // el sender y el receiver lo van a llamar cuando terminen de ejecutarse
    // si ya lo llamaron los dos entonces esta conexion se mete en finished_connections
    void _finishThread();

public:
    ClientConnection(InstanceId id,
                     Id map,
                     Socket& peer,
                     NonBlockingQueue<InstanceId*>& finished_connections,
                     NonBlockingQueue<int*>& commands);

    ClientConnection(const ClientConnection&) = delete;
    ClientConnection& operator=(const ClientConnection&) = delete;
    ClientConnection(ClientConnection&& other) = delete;
    ClientConnection& operator=(ClientConnection&& other) = delete;

    /*
     * El nuevo cliente comienza a enviar y recibir comandos (comandos tipo <int> segun protocolo)
     */
    void start();

    /*
     * Agrega un nuevo comando a la cola
     */
    void push(int command);

    /*
     * Deja de enviar y recibir comandos
     */
    void stop();

    /*
     * Join del hilo sender/receiver.
     */
    void join();

    ~ClientConnection();

};


#endif //CLIENTCONNECTION_H
