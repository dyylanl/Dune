#ifndef DEFS_H
#define DEFS_H

// --------------------------- //
#define MAX_CLIENTS_QUEUED 10
// ------------
#ifndef __INSTANCE_ID__
#define __INSTANCE_ID__
typedef uint32_t InstanceId;
#endif  // __INSTANCE_ID__
// ------------------
#ifndef __ID__
#define __ID__
typedef uint32_t Id;
#endif  // __ID__
// --------------

//------- COMANDOS CLIENTE-SERVER--------
#define SELECT_UNIT_COMMAND 5
#define MOVE_UNIT_COMMAND 6
#define BUILD_BUILDING_COMMAND 7
#define CREATE_UNIT_COMMAND 8


// -------------- RESPUESTAS SERVIDOR - CLIENTE -------------------- //
#define INVALID_COMMAND 11

#endif //DEFS_H
