#ifndef DEFS_H
#define DEFS_H

// --------------------------- //
#define MAX_CLIENTS_QUEUED 10

// --------------------------- //
#define PRECIPICE_KEY 'P'
#define PLAYER_KEY 'C'

// -------------------------- //
#define PALACE "palace"
#define SILO "silo"

// -------------------------- //
#define HARKONNEN_HOUSE 1
#define ATREIDES_HOUSE 2
#define ORDOS_HOUSE 3
// -------------------------- //
#ifndef __INSTANCE_ID__
#define __INSTANCE_ID__
typedef uint32_t InstanceId;
#endif  // __INSTANCE_ID__

#ifndef __ID__
#define __ID__
typedef uint32_t Id;
#endif  // __ID__


// COMANDOS CLIENTE-SERVER
#define SELECT_UNIT_COMMAND 5
#define MOVE_UNIT_COMMAND 6
#define BUILD_BUILDING_COMMAND 7
#define CREATE_UNIT_COMMAND 8

#endif //DEFS_H
